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
#include <iostream>
#define USE_AUDIO
BaseObject g_background;
TTF_Font* g_font_text = NULL;


bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0) return false;


    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    //Create window
    g_window = SDL_CreateWindow("Brave Soldier",
                                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }

        if (TTF_Init() == -1)
        {
            success = false;
        }


        g_font_text = TTF_OpenFont("font//dlxfont.ttf", 15);
        if (g_font_text == NULL)
        {
            return false;
        }
    }

    return success;

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == 0)
    {
        return false;
    }

    g_sound_bullet[0] = Mix_LoadWAV("Gun+357+Magnum.wav");
    g_sound_bullet[1] = Mix_LoadWAV("Gun+357+Magnum.wav");
    g_sound_explosion = Mix_LoadWAV("Explosion+1.wav");
    g_sound_ex_main = Mix_LoadWAV("Explosion+1.wav");

    if (g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL || g_sound_explosion == NULL)
    {
        return false;
    }

}

void close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}

bool LoadBackground()
{
    bool ret = g_background.LoadImg("img//p.png", g_screen);
    if (ret == false)
    {
        return false;
    }

    return true;
}

std::vector<ThreatsObject*> MakeThreatList1()
{

    std::vector<ThreatsObject*> list_threats1;

    ThreatsObject* threat_objs = new ThreatsObject[NUM_THREAT_1];

    for (int i = 0; i < NUM_THREAT_1; i++)
    {
        ThreatsObject* threat_obj = (threat_objs + i);
        if (threat_obj != NULL)
        {
            threat_obj->LoadImg("img//threat_left.png", g_screen);
            threat_obj->set_clips();
            threat_obj->InitThreats();
            threat_obj->set_xpos(500 + i*500);
            threat_obj->set_ypos(200);
            threat_obj->set_type_move(ThreatsObject::MOVE_IN_SPACE_TH);

            //Set moving range for threats
            int pos1 = threat_obj->get_x_pos() - 100;
            int pos2 = threat_obj->get_x_pos() + 100;

            threat_obj->SetAnimationPos(pos1, pos2);

            BulletObject* p_bullet = new BulletObject();
            threat_obj->InitBulletForSmallThreats(p_bullet, g_screen);
            threat_obj->set_is_alive(true);
            list_threats1.push_back(threat_obj);
        }
    }

    return list_threats1;
}

std::vector<ThreatsObject*> MakeThreatList2()
{
    std::vector<ThreatsObject*> list_threats2;

    ThreatsObject* threat_objs2 = new ThreatsObject[NUM_THREAT_2];
    for (int i = 0; i < NUM_THREAT_2; i++)
    {
        ThreatsObject* threat_obj2 = (threat_objs2 + i);
        if (threat_obj2 != NULL)
        {
            threat_obj2->LoadImg("img//threat_level.png", g_screen);
            threat_obj2->set_clips();
            threat_obj2->InitThreats();
            threat_obj2->set_input_left(0);
            threat_obj2->set_xpos(700 + i*1200);
            threat_obj2->set_ypos(250);

            threat_obj2->set_type_move(ThreatsObject::STATIC_TH);

            BulletObject* p_bullet = new BulletObject();
            threat_obj2->InitBulletForBigThreats(p_bullet, g_screen);
            threat_obj2->set_is_alive(true);
            list_threats2.push_back(threat_obj2);
        }
    }


    return list_threats2;
}


int main(int argc, char* argv[])
{
    ImpTimer fps;
    //Start up SDL and create window
    if (InitData() == false)
    {
        return -1;
    }


    if(!LoadBackground())
    {
        return -1;
    }

    GameMap game_map;
    game_map.LoadMap("map//map01.dat");
    game_map.LoadMapTiles(g_screen);


    MainObject p_player;
    p_player.LoadImg(g_name_main_right, g_screen);
    p_player.set_clips();


    PlayerPower player_power;
    player_power.Init(g_screen);


    PlayerMoney player_money;
    player_money.Init(g_screen);
    player_money.SetPos(SCREEN_WIDTH*0.5 - 300, 8);


    std::vector<ThreatsObject*> threats_list1 = MakeThreatList1();
    std::vector<ThreatsObject*> threats_list2 = MakeThreatList2();


    //Init Boss Object
    BossObject bossObject;
    bossObject.LoadImg("img//boss_object.png", g_screen);
    bossObject.set_clips();
    int xPosBoss = MAX_MAP_X*TILE_SIZE - SCREEN_WIDTH*0.6;
    bossObject.set_xpos(xPosBoss);
    bossObject.set_ypos(10);

    //Explosion Object
    ExplosionObject exp_threats;
    ExplosionObject exp_main;

    bool ret = exp_threats.LoadImg("img//exp3.png", g_screen);
    exp_threats.set_clips();
    if (!ret) return -1;


    ret = exp_main.LoadImg("img//exp3.png", g_screen);
    exp_main.set_clips();
    if (!ret) return 0;


    TextObject time_game;
    time_game.setColor(TextObject::WHITE_TEXT);

    TextObject mark_game;
    mark_game.setColor(TextObject::WHITE_TEXT);

    TextObject money_count;
    money_count.setColor(TextObject::WHITE_TEXT);

    int num_die = 0;
    unsigned int mark_value = 0;

    bool quit = false;
    while(!quit)
    {
        fps.start();
        while( SDL_PollEvent(&g_event) != 0 )
        {
            //User requests quit
            if(g_event.type == SDL_QUIT)
            {
                quit = true;
            }

            p_player.HandleInputAction(g_event, g_screen, g_sound_bullet);
        }

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);

        Map ga_map = game_map.GetMap();

        //p_player.SpawnBullet(g_screen);
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

        //std::vector<ThreatsObject*> threats_list = MakeThreatList();
        //Show threats

        SDL_Rect rect_player = p_player.GetRectFrame();

        for (int i = 0; i < (int)threats_list1.size(); i++)
        {
            ThreatsObject* obj_threat1 = threats_list1.at(i);
            if (obj_threat1 != NULL)
            {
                obj_threat1->SetMapXY(ga_map.start_x_, ga_map.start_y_);
                obj_threat1->ImpMoveType(g_screen);
                obj_threat1->DoThreats(ga_map, g_screen);
                obj_threat1->MakeBulletForSmallThreats(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                obj_threat1->Show(g_screen);


                //COLLISION THREAT BULLET -> MAIN OBJECT
                bool is_col1 = false;
                std::vector<BulletObject*> th_bullet_list1 = obj_threat1->get_bullet_list();
                for (int am = 0; am < (int)th_bullet_list1.size(); am++)
                {
                    BulletObject* th_bullet1 = th_bullet_list1.at(am);
                    if (th_bullet1 != NULL)
                    {
                        is_col1 = SDLCommonFunction::CheckCollision(th_bullet1->GetRect(), rect_player);
                        if (is_col1 == true)
                        {
                            obj_threat1->RemoveBullet(am);
                            break;
                        }
                    }
                }

                //COLLISION THREAT OBJECT -> MAIN OBJECT
                SDL_Rect rect_threat1 = obj_threat1->GetRectFrame();
                bool is_col2 = SDLCommonFunction::CheckCollision(rect_player, rect_threat1);
                if (is_col2 || is_col1)
                {
                    //obj_threat->Reset(SCREEN_WIDTH, SCREEN_HEIGHT);
                    //walk_object.set_is_move(true);
                    int width_exp_frame = exp_main.get_frame_height();
                    int heiht_exp_height = exp_main.get_frame_width();
                    for (int ex = 0; ex < NUM_FRAME_EXP; ex++)
                    {
                        int x_pos = (p_player.GetRect().x + p_player.get_frame_width()*0.5) - width_exp_frame*0.5;
                        int y_pos = (p_player.GetRect().y + p_player.get_frame_height()*0.5) - heiht_exp_height*0.5;

                        exp_main.set_frame(ex);
                        exp_main.SetRect(x_pos, y_pos);
                        exp_main.Show(g_screen);
                        //SDL_RenderPresent(g_screen);
                    }
                    num_die++;
                }

                Mix_PlayChannel(-1, g_sound_ex_main, 0);
            }

            //Die condition
//            if (num_die <= 3)
//            {
//                p_player.SetRect(0, 0);
//                p_player.set_think_time(60);
//                SDL_Delay(1000);
//                player_power.Decrease();
//                player_power.Render(g_screen);
//                continue;
//            }
//            else
//            {
//                if(MessageBox(NULL, "YOU DIED!", "GAME OVER", MB_OK | MB_ICONSTOP) == IDOK)
//                {
//                    obj_threat1->Free();
//                    close();
//                    SDL_Quit();
//                    return 0;
//                }
//            }
        }


        for (int i = 0; i < (int)threats_list2.size(); i++)
        {
            ThreatsObject* obj_threat2 = threats_list2.at(i);
            if (obj_threat2 != NULL)
            {
                obj_threat2->SetMapXY(ga_map.start_x_, ga_map.start_y_);
                obj_threat2->ImpMoveType(g_screen);
                obj_threat2->DoThreats(ga_map, g_screen);
                obj_threat2->MakeBulletForBigThreats(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                obj_threat2->Show(g_screen);


                //COLLISION THREAT BULLET -> MAIN OBJECT
                bool is_col1 = false;
                std::vector<BulletObject*> th_bullet_list2 = obj_threat2->get_bullet_list();
                for (int am = 0; am < (int)th_bullet_list2.size(); am++)
                {
                    BulletObject* th_bullet2 = th_bullet_list2.at(am);
                    if (th_bullet2 != NULL)
                    {
                        is_col1 = SDLCommonFunction::CheckCollision(th_bullet2->GetRect(), rect_player);
                        if (is_col1 == true)
                        {
                            obj_threat2->RemoveBullet(am);
                            break;
                        }
                    }
                }

                //COLLISION THREAT OBJECT -> MAIN OBJECT
                SDL_Rect rect_threat2 = obj_threat2->GetRectFrame();
                bool is_col2 = SDLCommonFunction::CheckCollision(rect_player, rect_threat2);
                if (is_col2 || is_col1)
                {
                    //obj_threat->Reset(SCREEN_WIDTH, SCREEN_HEIGHT);
                    //walk_object.set_is_move(true);
                    int width_exp_frame = exp_main.get_frame_height();
                    int heiht_exp_height = exp_main.get_frame_width();
                    for (int ex = 0; ex < NUM_FRAME_EXP; ex++)
                    {
                        int x_pos = (p_player.GetRect().x + p_player.get_frame_width()*0.5) - width_exp_frame*0.5;
                        int y_pos = (p_player.GetRect().y + p_player.get_frame_height()*0.5) - heiht_exp_height*0.5;

                        exp_main.set_frame(ex);
                        exp_main.SetRect(x_pos, y_pos);
                        exp_main.Show(g_screen);
                        //SDL_RenderPresent(g_screen);
                    }
                    num_die++;
                }

                Mix_PlayChannel(-1, g_sound_ex_main, 0);
            }
//            if (num_die <= 3)
//            {
//                p_player.SetRect(0, 0);
//                p_player.set_think_time(60);
//                SDL_Delay(1000);
//                player_power.Decrease();
//                player_power.Render(g_screen);
//                continue;
//            }
//            else
//            {
//                if(MessageBox(NULL, "YOU DIED!", "GAME OVER", MB_OK | MB_ICONSTOP) == IDOK)
//                {
//                    //obj_threat2->Free();
//                    close();
//                    SDL_Quit();
//                    return 0;
//                }
//            }


        }
            //Die condition
//            if (num_die <= 3)
//            {
//                p_player.SetRect(0, 0);
//                p_player.set_think_time(60);
//                SDL_Delay(1000);
//                player_power.Decrease();
//                player_power.Render(g_screen);
//                continue;
//            }
//            else
//            {
//                if(MessageBox(NULL, "YOU DIED!", "GAME OVER", MB_OK | MB_ICONSTOP) == IDOK)
//                {
//                    //obj_threat2->Free();
//                    close();
//                    SDL_Quit();
//                    return 0;
//                }
//            }
//

        //COLLISION BOSS BULLET -> MAIN OBJECT
        bool is_col_boss_bullet = false;
        std::vector<BulletObject*> boss_bullet_list = bossObject.get_bullet_list();
        for (int am = 0; am < (int)boss_bullet_list.size(); am++)
        {
            BulletObject* boss_bullet = boss_bullet_list.at(am);
            if (boss_bullet != NULL)
            {
                is_col_boss_bullet = SDLCommonFunction::CheckCollision(boss_bullet->GetRect(), rect_player);
                if (is_col_boss_bullet == true)
                {
                    bossObject.RemoveBullet(am);
                    break;
                }
            }
        }
        //COLLISION BOSS OBJECT -> MAIN OBJECT
        bool is_col_boss = SDLCommonFunction::CheckCollision(rect_player, bossObject.GetRectFrame());
        if (is_col_boss || is_col_boss_bullet)
        {
            //obj_threat->Reset(SCREEN_WIDTH, SCREEN_HEIGHT);
            //walk_object.set_is_move(true);
            int width_exp_frame = exp_main.get_frame_height();
            int heiht_exp_height = exp_main.get_frame_width();
            for (int ex = 0; ex < NUM_FRAME_EXP; ex++)
            {
                int x_pos = (p_player.GetRect().x + p_player.get_frame_width()*0.5) - width_exp_frame*0.5;
                int y_pos = (p_player.GetRect().y + p_player.get_frame_height()*0.5) - heiht_exp_height*0.5;

                exp_main.set_frame(ex);
                exp_main.SetRect(x_pos, y_pos);
                exp_main.Show(g_screen);
                //SDL_RenderPresent(g_screen);
            }
            num_die++;
            Mix_PlayChannel(-1, g_sound_ex_main, 0);
        }


        //COLLISION THREAT -> Main Bullet
        std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
        int frame_exp_width = exp_threats.get_frame_width();
        int frame_exp_height = exp_threats.get_frame_width();

        for (int am = 0; am < (int)bullet_arr.size(); am++)
        {
            BulletObject* p_bullet = bullet_arr.at(am);
            if (p_bullet != NULL)
            {
                //p_bullet->CheckToMap(ga_map, g_screen);
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
//
//                        obj_threat->Reset(SCREEN_WIDTH, SCREEN_HEIGHT);
                        p_player.RemoveBullet(am);
//
//                        //if (obj_threat->set_type_move() == ThreatsObject::MOVING_CONTINOUS)
//                        //{
//                        //    obj_threat->Reset();
//                        //}
//                        //else
//                        //{
                        obj_threat1->Free();
                        threats_list1.erase(threats_list1.begin() + i);
//                                //}
                        Mix_PlayChannel(-1, g_sound_explosion, 0);
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
//
//                        obj_threat->Reset(SCREEN_WIDTH, SCREEN_HEIGHT);
                        p_player.RemoveBullet(am);
//
//                        //if (obj_threat->set_type_move() == ThreatsObject::MOVING_CONTINOUS)
//                        //{
//                        //    obj_threat->Reset();
//                        //}
//                        //else
//                        //{
                        obj_threat2->Free();
                        threats_list2.erase(threats_list2.begin() + i);
//                                //}
//                        Mix_PlayChannel(-1, g_sound_explosion, 0);
                    }
                }
                //COLLISION BOSS -> Main Bullet
                bool is_col_bullet_boss = SDLCommonFunction::CheckCollision(p_bullet->GetRect(), bossObject.GetRectFrame());
                int num_bullet_to_boss = 0;
                if (is_col_bullet_boss)
                {
                    num_bullet_to_boss++;
                    for (int ex = 0; ex < NUM_FRAME_EXP; ex++)
                    {
                        //set exp pos
                        int x_pos = p_bullet->GetRect().x - frame_exp_width*0.5;
                        int y_pos = p_bullet->GetRect().y - frame_exp_height*0.5;

                        exp_threats.set_frame(ex);
                        exp_threats.SetRect(x_pos, y_pos);
                        exp_threats.Show(g_screen);
                    }
//
//                        obj_threat->Reset(SCREEN_WIDTH, SCREEN_HEIGHT);
                    p_player.RemoveBullet(am);
//
//                        //if (obj_threat->set_type_move() == ThreatsObject::MOVING_CONTINOUS)
//                        //{
//                        //    obj_threat->Reset();
//                        //}
//                        //else
//                        //{
                    if (num_bullet_to_boss == 10) bossObject.Free();
//                    bossObject = NULL;
//                        threats_list1.erase(threats_list1.begin() + i);
//                                //}
                    Mix_PlayChannel(-1, g_sound_explosion, 0);
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
            if (MessageBox(NULL, "Time limit exceeded!", "GAME OVER", MB_OK | MB_ICONSTOP) == IDOK)
            {
                quit = true;
                break;
            }
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
    //std::cout << num_die;




    for (int i = 0; i < (int)threats_list1.size(); i++)
    {
        ThreatsObject* p_threat = threats_list1.at(i);
        p_threat->Free();
        p_threat = NULL;
    }

    threats_list1.clear();

    for (int i = 0; i < (int)threats_list2.size(); i++)
    {
        ThreatsObject* p_threat = threats_list2.at(i);
        p_threat->Free();
        p_threat = NULL;
    }

    threats_list2.clear();

    bossObject.clear();

    close();

    return 0;
}

