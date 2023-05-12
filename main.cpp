#include "CommonFunction.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "TextObject.h"
#include "PlayerPower.h"
#include "Geometric.h"
#include "BossObject.h"
#include "MenuGame.h"
#include <iostream>
#define USE_AUDIO

BaseObject g_background;
BaseObject g_menu;
BaseObject g_over;

TTF_Font* g_font_text = NULL;

void FreeThreats(std::vector<ThreatsObject*>& list1, std::vector<ThreatsObject*>& list2);

bool InitData()
{

    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
    {
        std::cout << "Init Error!";
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    //Create window
    g_window = SDL_CreateWindow("Brave Soldier",
                                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == NULL)
    {
        std::cout << "Window Error!";
        return false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (g_screen == NULL)
        {
            std::cout << "Screen Error!";
            return false;
        }
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
            {
                std::cout << "Img Error!";
                return false;
            }

        }

        if (TTF_Init() == -1)
        {
            std::cout << "Font Error!";
            return false;
        }

        g_font_text = TTF_OpenFont("font//dlxfont.ttf", 15);
        if (g_font_text == NULL)
        {
            std::cout << "Open Font Error!";
            return false;
        }

    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout << "Can't load sound!";
        return false;
    }

    g_background_music = Mix_LoadWAV(g_name_background_music);
    g_menu_music = Mix_LoadWAV(g_name_menu_music);
    g_game_over_music = Mix_LoadWAV(g_name_game_over_music);
    g_sound_bullet_main = Mix_LoadWAV(g_name_audio_bullet_main);
    g_sound_bullet_threats = Mix_LoadWAV(g_name_audio_bullet_threats);
    g_sound_explosion = Mix_LoadWAV(g_name_audio_exp);
    g_sound_explosion_dead = Mix_LoadWAV(g_name_audio_exp_dead);

    if (g_sound_bullet_main == NULL || g_sound_bullet_threats == NULL || g_sound_explosion == NULL || g_sound_explosion_dead == NULL )
    {
        std::cout << "Sound Error!";
        return false;
    }

    return true;
}


void close()
{
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    g_background.Free();
    g_menu.Free();
    g_over.Free();
    Mix_FreeChunk(g_background_music);
    Mix_FreeChunk(g_menu_music);
    Mix_FreeChunk(g_game_over_music);
    Mix_FreeChunk(g_sound_bullet_main);
    Mix_FreeChunk(g_sound_bullet_threats);
    Mix_FreeChunk(g_sound_explosion);
    Mix_FreeChunk(g_sound_explosion_dead);
    g_background_music = NULL;
    g_menu_music = NULL;
    g_game_over_music = NULL;
    g_sound_bullet_main = NULL;
    g_sound_bullet_threats = NULL;
    g_sound_explosion = NULL;
    g_sound_explosion_dead = NULL;
    IMG_Quit();
    SDL_Quit();
    Mix_Quit();
}


bool LoadBackground()
{
    bool ret = g_background.LoadImg(g_name_background, g_screen);
    if (ret == false)
    {
        std::cout << "Can't load bkg!";
        return false;
    }
    return true;
}


std::vector<ThreatsObject*> MakeDynamicThreatList()
{
    std::vector<ThreatsObject*> list_dynamic_threats;
    ThreatsObject* threat_objs = new ThreatsObject[NUM_DYNAMIC_THREAT];
    for (int i = 0; i < NUM_DYNAMIC_THREAT; i++)
    {
        ThreatsObject* threat_obj = (threat_objs + i);
        if (threat_obj != NULL)
        {
            threat_obj->LoadImg(g_name_dynamic_threat_left, g_screen);
            threat_obj->set_clips();
            threat_obj->InitThreats();
            threat_obj->set_xpos(500 + i*DYNAMIC_THREAT_FREQUENCY);
            threat_obj->set_ypos(200);
            threat_obj->set_type_move(ThreatsObject::MOVE_IN_SPACE_TH);
            //Set moving range for threats
            int pos1 = threat_obj->get_x_pos() - 100;
            int pos2 = threat_obj->get_x_pos() + 100;
            threat_obj->SetAnimationPos(pos1, pos2);

            BulletObject* p_bullet = new BulletObject();
            threat_obj->InitBulletForSmallThreats(p_bullet, g_screen);
            threat_obj->set_is_alive(true);
            list_dynamic_threats.push_back(threat_obj);
        }
    }
    return list_dynamic_threats;
}

std::vector<ThreatsObject*> MakeStaticThreatList()
{
    std::vector<ThreatsObject*> list_static_threats;
    ThreatsObject* threat_objs2 = new ThreatsObject[NUM_STATIC_THREAT];
    for (int i = 0; i < NUM_STATIC_THREAT; i++)
    {
        ThreatsObject* threat_obj2 = (threat_objs2 + i);
        if (threat_obj2 != NULL)
        {
            threat_obj2->LoadImg(g_name_static_threat, g_screen);
            threat_obj2->set_clips();
            threat_obj2->InitThreats();
            threat_obj2->set_input_left(0);
            threat_obj2->set_xpos(700 + i*STATIC_THREAT_FREQUENCY);
            threat_obj2->set_ypos(250);
            threat_obj2->set_type_move(ThreatsObject::STATIC_TH);

            BulletObject* p_bullet = new BulletObject();
            threat_obj2->InitBulletForBigThreats(p_bullet, g_screen);
            threat_obj2->set_is_alive(true);
            list_static_threats.push_back(threat_obj2);
        }
    }
    return list_static_threats;
}


int main(int argc, char* argv[])
{
    ImpTimer fps;
    //Start up SDL and create window
    if (InitData() == false)
    {
        std::cout << "Data Error!";
        return -1;
    }
    if (LoadBackground() == false)
    {
        std::cout << "Background Error!";
        return -1;
    }

    GameMap game_map;
    game_map.LoadMap(g_name_map);
    game_map.LoadMapTiles(g_screen);

replay_label:
    MainObject p_player;
    p_player.LoadImg(g_name_main_right, g_screen);
    p_player.set_clips();

    PlayerPower player_power;
    player_power.Init(g_screen);

    PlayerMoney player_money;
    player_money.Init(g_screen);
    player_money.SetPos(SCREEN_WIDTH*0.5 - 300, 8);

    std::vector<ThreatsObject*> threats_list1 = MakeDynamicThreatList();
    std::vector<ThreatsObject*> threats_list2 = MakeStaticThreatList();

    //Init Boss Object
    BossObject bossObject;
    bool ret = bossObject.LoadImg(g_name_boss, g_screen);
    bossObject.set_clips();
    if (!ret) return -1;
    int xPosBoss = MAX_MAP_X*TILE_SIZE - SCREEN_WIDTH*0.6;
    bossObject.set_xpos(xPosBoss);
    bossObject.set_ypos(10);

    //Explosion Object
    ExplosionObject exp_threats;
    bool Tret = exp_threats.LoadImg(g_name_exp, g_screen);
    exp_threats.set_clips();
    if (!Tret) return -1;

    ExplosionObject exp_main;
    bool Mret = exp_main.LoadImg(g_name_exp, g_screen);
    exp_main.set_clips();
    if (!Mret) return 0;

    TextObject time_game;
    time_game.setColor(TextObject::WHITE_TEXT);

    TextObject mark_game;
    mark_game.setColor(TextObject::WHITE_TEXT);

    TextObject money_count;
    money_count.setColor(TextObject::WHITE_TEXT);

    int num_die = 0;
    unsigned int mark_value = 0;

    MenuGame StartButton;
    MenuGame ExitButton;
    MenuGame ExitButton2;
    MenuGame ReplayButton;

    g_menu.LoadImg(g_name_menu, g_screen);
    g_over.LoadImg(g_name_over, g_screen);

    bool in_menu = true;
    bool end_game = false;
    bool quit = false;

    while (in_menu)
    {
        fps.start();
        if (!Mix_Playing(1))
        {
            Mix_PlayChannel(1, g_menu_music, -1);
        }
        while (SDL_PollEvent(&g_event) != 0)
        {
            if(g_event.type == SDL_QUIT)
            {
                in_menu = false;
                quit = true;
            }
            StartButton.HandlePlayButton(g_event, g_screen, in_menu);
            ExitButton.HandleQuitButton(g_event, g_screen, quit, in_menu);
        }

        StartButton.SetRect(300, 300);
        ExitButton.SetRect(575, 300);

        g_menu.Render(g_screen);
        StartButton.Render(g_screen);
        ExitButton.Render(g_screen);
        SDL_RenderPresent(g_screen);

    }

    while (!quit)
    {
        fps.start();
        Mix_HaltChannel(1);
        if (!Mix_Playing(2))
        {
            Mix_PlayChannel(2, g_background_music ,-1);
        }
        if (!end_game)
        {
            Mix_HaltChannel(3);
            while (SDL_PollEvent(&g_event) != 0)
            {
                //User requests quit
                if(g_event.type == SDL_QUIT)
                {
                    quit = true;
                }

                p_player.HandleInputAction(g_event, g_screen, g_sound_bullet_main);
            }

            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            SDL_RenderClear(g_screen);

            g_background.Render(g_screen, NULL);

            Map ga_map = game_map.GetMap();

            p_player.SpawnBullet(g_screen, g_sound_bullet_main);
            p_player.HandleBullet(g_screen);
            p_player.SetMapXY(ga_map.start_x_, ga_map.start_y_);
            p_player.DoPlayer(ga_map);
            p_player.Show(g_screen);


            game_map.SetMap(ga_map);
            game_map.DrawMap(g_screen);

            //Draw Geometric
            GeometricFormat rectange_size(0, 0, SCREEN_WIDTH, 40);
            ColorData color_data(36, 36, 36);
            Geometric::RenderRectange(rectange_size, color_data, g_screen);

            GeometricFormat outline_size(1, 1, SCREEN_WIDTH - 1, 38);
            ColorData color_data1(255, 255, 255);
            Geometric::RenderOutline(outline_size, color_data1, g_screen);

            player_power.Show(g_screen);
            player_money.Show(g_screen);


            SDL_Rect rect_player = p_player.GetRectFrame();


            //Show threats
            for (int i = 0; i < (int)threats_list1.size(); i++)
            {
                ThreatsObject* obj_threat1 = threats_list1.at(i);
                if (obj_threat1 != NULL)
                {
                    obj_threat1->SetMapXY(ga_map.start_x_, ga_map.start_y_);
                    obj_threat1->DoThreats(ga_map, g_screen);
                    obj_threat1->MakeBulletForSmallThreats(ga_map, g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                    obj_threat1->Show(g_screen);

                    //COLLISION THREAT BULLET -> MAIN OBJECT
                    bool is_col1 = false;
                    std::vector<BulletObject*> th_bullet_list1 = obj_threat1->get_bullet_list();
                    for (int am = 0; am < (int)th_bullet_list1.size(); am++)
                    {
                        BulletObject* th_bullet1 = th_bullet_list1.at(am);
                        if (th_bullet1 != NULL && th_bullet1->get_is_move() == true)
                        {
                            is_col1 = SDLCommonFunction::CheckCollision(th_bullet1->GetRect(), rect_player);
                            if (is_col1 == true)
                            {
                                th_bullet1->set_is_move(false);
                                Mix_PlayChannel(-1, g_sound_explosion, 0);
                                break;
                            }
                        }
                    }
                    //COLLISION THREAT OBJECT -> MAIN OBJECT
                    SDL_Rect rect_threat1 = obj_threat1->GetRectFrame();
                    bool is_col2 = SDLCommonFunction::CheckCollision(rect_player, rect_threat1);
                    if (is_col2 || is_col1)
                    {
                        int width_exp_frame = exp_main.get_frame_height();
                        int height_exp_frame = exp_main.get_frame_width();
                        for (int ex = 0; ex < NUM_FRAME_EXP; ex++)
                        {
                            int x_pos = (p_player.GetRect().x + p_player.get_frame_width()*0.5) - width_exp_frame*0.5;
                            int y_pos = (p_player.GetRect().y + p_player.get_frame_height()*0.5) - height_exp_frame*0.5;

                            exp_main.set_frame(ex);
                            exp_main.SetRect(x_pos, y_pos);
                            exp_main.Show(g_screen);
                        }
                        num_die++;
                        Mix_PlayChannel(-1, g_sound_explosion, 0);
                        //Re-render main object after collision
                        p_player.SetRect(0, 0);
                        p_player.set_comeback_time(COMEBACK_TIME);
                        SDL_Delay(DELAY_TIME_FOR_COLLISION);
                        player_power.Decrease();
                        player_power.Render(g_screen);
                        continue;
                    }
                }
            }


            for (int i = 0; i < (int)threats_list2.size(); i++)
            {
                ThreatsObject* obj_threat2 = threats_list2.at(i);
                if (obj_threat2 != NULL)
                {
                    obj_threat2->SetMapXY(ga_map.start_x_, ga_map.start_y_);
                    obj_threat2->ImpMoveType(g_screen);
                    obj_threat2->DoThreats(ga_map, g_screen);
                    obj_threat2->MakeBulletForBigThreats(ga_map, g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                    obj_threat2->Show(g_screen);

                    //COLLISION THREAT BULLET -> MAIN OBJECT
                    bool is_col1 = false;
                    std::vector<BulletObject*> th_bullet_list2 = obj_threat2->get_bullet_list();
                    for (int am = 0; am < (int)th_bullet_list2.size(); am++)
                    {
                        BulletObject* th_bullet2 = th_bullet_list2.at(am);
                        if (th_bullet2 != NULL && th_bullet2->get_is_move() == true)
                        {
                            is_col1 = SDLCommonFunction::CheckCollision(th_bullet2->GetRect(), rect_player);
                            if (is_col1 == true)
                            {
                                th_bullet2->set_is_move(false);
                                Mix_PlayChannel(-1, g_sound_explosion, 0);
                                break;
                            }
                        }
                    }

                    //COLLISION THREAT OBJECT -> MAIN OBJECT
                    SDL_Rect rect_threat2 = obj_threat2->GetRectFrame();
                    bool is_col2 = SDLCommonFunction::CheckCollision(rect_player, rect_threat2);
                    if (is_col2 || is_col1)
                    {
                        int height_exp_frame = exp_main.get_frame_height();
                        int width_exp_frame = exp_main.get_frame_width();
                        for (int ex = 0; ex < NUM_FRAME_EXP; ex++)
                        {
                            int x_pos = (p_player.GetRect().x + p_player.get_frame_width()*0.5) - width_exp_frame*0.5;
                            int y_pos = (p_player.GetRect().y + p_player.get_frame_height()*0.5) - height_exp_frame*0.5;
                            exp_main.set_frame(ex);
                            exp_main.SetRect(x_pos, y_pos);
                            exp_main.Show(g_screen);
                        }
                        num_die++;
                        p_player.SetRect(0, 0);
                        p_player.set_comeback_time(COMEBACK_TIME);
                        SDL_Delay(DELAY_TIME_FOR_COLLISION);
                        player_power.Decrease();
                        player_power.Render(g_screen);
                        continue;

                        Mix_PlayChannel(-1, g_sound_explosion, 0);
                    }
                }
            }

            //COLLISION BOSS BULLET -> MAIN OBJECT
            bool is_col_boss_bullet = false;
            if (bossObject.CheckBossDie() == false)
            {
                std::vector<BulletObject*> boss_bullet_list = bossObject.get_bullet_list();
                for (int am = 0; am < (int)boss_bullet_list.size(); am++)
                {
                BulletObject* boss_bullet = boss_bullet_list.at(am);
                if (boss_bullet != NULL && boss_bullet->get_is_move() == true)
                {
                    is_col_boss_bullet = SDLCommonFunction::CheckCollision(boss_bullet->GetRect(), rect_player);
                    if (is_col_boss_bullet == true)
                    {
                        boss_bullet->set_is_move(false);
                        Mix_PlayChannel(-1, g_sound_explosion, 0);
                        break;
                    }
                }
                }
            }

            //COLLISION BOSS OBJECT -> MAIN OBJECT
            bool is_col_boss = false;
            if ( bossObject.CheckBossDie() == false)
            {
                SDLCommonFunction::CheckCollision(rect_player, bossObject.GetRectFrame());
            }

            if (is_col_boss || is_col_boss_bullet)
            {
                int width_exp_frame = exp_main.get_frame_height();
                int height_exp_frame = exp_main.get_frame_width();
                for (int ex = 0; ex < NUM_FRAME_EXP; ex++)
                {
                    int x_pos = (p_player.GetRect().x + p_player.get_frame_width()*0.5) - width_exp_frame*0.5;
                    int y_pos = (p_player.GetRect().y + p_player.get_frame_height()*0.5) - height_exp_frame*0.5;

                    exp_main.set_frame(ex);
                    exp_main.SetRect(x_pos, y_pos);
                    exp_main.Show(g_screen);
                    //SDL_RenderPresent(g_screen);
                }

                num_die++;
                Mix_PlayChannel(-1, g_sound_explosion, 0);
                //Re-render main object after collision
                p_player.SetRect(0, 0);
                p_player.set_comeback_time(COMEBACK_TIME);
                SDL_Delay(DELAY_TIME_FOR_COLLISION);
                player_power.Decrease();
                player_power.Render(g_screen);
                continue;
            }
            //Die condition
            if (num_die > 3)
            {
                Mix_PlayChannel(-1, g_sound_explosion_dead, 0);
                end_game = true;
            }


            //COLLISION THREAT -> Main Bullet
            std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();

            int frame_exp_width = exp_threats.get_frame_width();
            int frame_exp_height = exp_threats.get_frame_width();

            // kiem tra tung vien dan cua main voi moi threat
            for (int am = 0; am < (int)bullet_arr.size(); ++am)
            {
                BulletObject* p_bullet = bullet_arr.at(am);
                if (p_bullet != NULL && p_bullet->get_is_move() == true)
                {

                    for (int i = 0; i < (int)threats_list1.size(); i++)
                    {
                        ThreatsObject* obj_threat1 = threats_list1.at(i);

                        SDL_Rect threat_rect = obj_threat1->GetRectFrame();

                        bool is_col = SDLCommonFunction::CheckCollision(p_bullet->GetRect(), threat_rect);
                        if (is_col)
                        {
                            mark_value++;
                            for (int ex = 0; ex < NUM_FRAME_EXP; ex++)
                            {
                                //set exp pos
                                int x_pos = p_bullet->GetRect().x - frame_exp_width*0.5;
                                int y_pos = p_bullet->GetRect().y - frame_exp_height*0.5;

                                exp_threats.set_frame(ex);
                                exp_threats.SetRect(x_pos, y_pos);
                                exp_threats.Show(g_screen);
                            }

                            p_bullet->set_is_move(false);
                            obj_threat1->Free();
                            threats_list1.erase(threats_list1.begin() + i);
                            Mix_PlayChannel(-1, g_sound_explosion, 0);
                            break;
                        }
                    }

                    for (int i = 0; i < (int)threats_list2.size(); i++)
                    {
                        ThreatsObject* obj_threat2 = threats_list2.at(i);

                        SDL_Rect threat_rect = obj_threat2->GetRectFrame();

                        bool is_col = SDLCommonFunction::CheckCollision(p_bullet->GetRect(), threat_rect);
                        if (is_col)
                        {
                            mark_value++;
                            for (int ex = 0; ex < NUM_FRAME_EXP; ex++)
                            {
                                //set exp pos
                                int x_pos = p_bullet->GetRect().x - frame_exp_width*0.5;
                                int y_pos = p_bullet->GetRect().y - frame_exp_height*0.5;

                                exp_threats.set_frame(ex);
                                exp_threats.SetRect(x_pos, y_pos);
                                exp_threats.Show(g_screen);
                            }

                            p_bullet->set_is_move(false);
                            obj_threat2->Free();
                            threats_list2.erase(threats_list2.begin() + i);
                            Mix_PlayChannel(-1, g_sound_explosion, 0);
                            break;
                        }
                        // vien dan het vai tro, ko check voi cac con quai khac nua
                    }


                    //COLLISION BOSS -> Main Bullet
                    bool bb = bossObject.CheckBossDie();
                     if (p_bullet->get_is_move() == true && bossObject.CheckBossDie() == false) // neu vien dan da va cham voi quai trc do roi thi thoi
                    {
                        bool is_col_bullet_boss = SDLCommonFunction::CheckCollision(p_bullet->GetRect(), bossObject.GetRectFrame());
                        if (is_col_bullet_boss)
                        {
                            bossObject.PlusBulletDie();
                            for (int ex = 0; ex < NUM_FRAME_EXP; ex++)
                            {
                                //set exp pos
                                int x_pos = p_bullet->GetRect().x - frame_exp_width*0.5;
                                int y_pos = p_bullet->GetRect().y - frame_exp_height*0.5;
                                exp_threats.set_frame(ex);
                                exp_threats.SetRect(x_pos, y_pos);
                                exp_threats.Show(g_screen);
                            }
                            p_bullet->set_is_move(false);
                        }

                        bool bDie = bossObject.CheckBulletDie();
                        if (bDie)
                        {
                            bossObject.ResetBulletDie();
                            Mix_PlayChannel(-1, g_sound_explosion, 0);
                        }
                    }
                }
            }
            //Show time for game
            std::string str_time = "Time: ";
            Uint32 time_val = SDL_GetTicks() / 1000;
            Uint32 val_time = 300 - time_val;
            std::string str_val = std::to_string(val_time);
            if (val_time <= 0)
            {
                Mix_Chunk* two_beep_chunk = Mix_LoadWAV(g_name_sound_increase);
                if (two_beep_chunk != NULL)
                    Mix_PlayChannel(-1, two_beep_chunk, 0 );
                end_game = true;
            }
            else
            {
                str_time += str_val;
                time_game.SetText(str_time);
                time_game.loadFromRenderedText(g_font_text, g_screen);
                time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 15);
            }
            //Show mark value to screen
            std::string val_str_mark = std::to_string(mark_value);
            std::string strMark("KILL: ");
            strMark += val_str_mark;
            mark_game.SetText(strMark);
            mark_game.loadFromRenderedText(g_font_text, g_screen);
            mark_game.RenderText(g_screen, SCREEN_WIDTH*0.5 - 50, 15);

            int money_val = p_player.GetMoneyCount();
            std::string money_count_str = std::to_string(money_val);

            money_count.SetText(money_count_str);
            money_count.loadFromRenderedText(g_font_text, g_screen);
            money_count.RenderText(g_screen, SCREEN_WIDTH*0.5 - 250, 15);

            //Process Boss
            int val = MAX_MAP_X*TILE_SIZE - (ga_map.start_x_ + p_player.GetRect().x);
            if (val <= SCREEN_WIDTH)
            {
                bossObject.SetMapXY(ga_map.start_x_, ga_map.start_y_);
                bossObject.DoBoss(ga_map);
                bossObject.MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                bossObject.Show(g_screen);
            }

            //Set fps time, adjust smoothness.
            int real_imp_time = fps.get_ticks();//base on the CPU of the laptop
            int time_for_one_frame = 1000/FRAMES_PER_SECOND;
            if (real_imp_time < time_for_one_frame)
            {
                SDL_Delay(time_for_one_frame - real_imp_time);
            }

            //Update screen
            SDL_RenderPresent(g_screen);
        }

        else
        {
            Mix_HaltChannel(2);
            if (!Mix_Playing(3))
            {
                Mix_PlayChannel(3, g_game_over_music, -1);
            }

            while (SDL_PollEvent(&g_event) != 0)
            {
                if(g_event.type == SDL_QUIT)
                {
                    quit = true;
                }
                ExitButton2.HandleQuitButtonAtGameOver(g_event, g_screen, quit, in_menu);
                ReplayButton.HandleRetryButton(g_event, g_screen, end_game);
            }

            ExitButton2.SetRect(470, 525);
            ReplayButton.SetRect(350, 450);

            g_over.Render(g_screen);
            ReplayButton.Render(g_screen);
            ExitButton2.Render(g_screen);

            if (ReplayButton.GetType() == MenuGame::ActionType::AC_REPLAY)
            {
                ReplayButton.SetType(MenuGame::AC_NONE);
                end_game = false;

                p_player.Free();
                bossObject.Free();
                FreeThreats(threats_list1, threats_list2);
                goto replay_label;
            }
            //Update screen
            SDL_RenderPresent(g_screen);
        }
    }

    p_player.Free();
    bossObject.Free();
    FreeThreats(threats_list1, threats_list2);
    close();
    return 0;
}

void FreeThreats(std::vector<ThreatsObject*>& list1, std::vector<ThreatsObject*>& list2)
{
    for (int i = 0; i < (int)list1.size(); ++i)
    {
        ThreatsObject* p_threat = list1.at(i);
        if (p_threat)
        {
            p_threat->Free();
            p_threat = NULL;
        }
    }
    list1.clear();

    for (int i = 0; i < (int)list2.size(); i++)
    {
        ThreatsObject* p_threat = list2.at(i);
        p_threat->Free();
        p_threat = NULL;
    }
    list2.clear();
}
