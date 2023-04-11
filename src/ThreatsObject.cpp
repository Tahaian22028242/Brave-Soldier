#include "ThreatsObject.h"



ThreatsObject::ThreatsObject()
{
    rect_.x = SCREEN_WIDTH;
    rect_.y = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    x_val_ = 0;
    y_val_ = 0;
    is_stop_bullet_ = false;

    x_pos_ = 0;
    y_pos_ = 0;
    on_ground_ = 0;
    think_time_ = 0;
    frame_ = 0;
    type_move_ = STATIC_TH;
    input_type_.left_ = 1;
}

ThreatsObject::~ThreatsObject()
{
    if (bullet_list_.size() > 0)
    {
        for (int i = 0; i < (int)bullet_list_.size(); i++)
        {
            BulletObject* p_bullet = bullet_list_.at(i);
            if (p_bullet != NULL)
            {
                //delete p_bullet;
                p_bullet = NULL;
            }
        }
        bullet_list_.clear();
    }
}

void ThreatsObject::InitThreats()
{
    x_pos_ = SCREEN_WIDTH - 400;
    y_pos_ = SCREEN_HEIGHT*0.5;
    x_val_ = 0;
    y_val_ = 0;

    if (x_pos_ > 256)
    {
        x_pos_ -= 256;
        animation_a_ -= 256;
        animation_b_ -= 256;
    }
    else x_pos_ = 0;

    y_pos_ = 0;
    think_time_ = 0;
    input_type_.left_ = 1;
}

SDL_Rect ThreatsObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = rect_.w/NUM_FRAME;
    rect.h = rect_.h;

    return rect;
}

bool ThreatsObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);

    if (ret == true)
    {
        width_frame_ = rect_.w/NUM_FRAME;
        height_frame_ = rect_.h;
    }

    return ret;
}


void ThreatsObject::set_clips()
{
    //Clip the sprites
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        frame_clip_[ 0 ].x = 0;
        frame_clip_[ 0 ].y = 0;
        frame_clip_[ 0 ].w = width_frame_;
        frame_clip_[ 0 ].h = height_frame_;

        frame_clip_[ 1 ].x = width_frame_;
        frame_clip_[ 1 ].y = 0;
        frame_clip_[ 1 ].w = width_frame_;
        frame_clip_[ 1 ].h = height_frame_;

        frame_clip_[ 2 ].x = width_frame_ * 2;
        frame_clip_[ 2 ].y = 0;
        frame_clip_[ 2 ].w = width_frame_;
        frame_clip_[ 2 ].h = height_frame_;

        frame_clip_[ 3 ].x = width_frame_ * 3;
        frame_clip_[ 3 ].y = 0;
        frame_clip_[ 3 ].w = width_frame_;
        frame_clip_[ 3 ].h = height_frame_;

        frame_clip_[ 4 ].x = width_frame_ * 4;
        frame_clip_[ 4 ].y = 0;
        frame_clip_[ 4 ].w = width_frame_;
        frame_clip_[ 4 ].h = height_frame_;

        frame_clip_[ 5 ].x = width_frame_ * 5;
        frame_clip_[ 5 ].y = 0;
        frame_clip_[ 5 ].w = width_frame_;
        frame_clip_[ 5 ].h = height_frame_;

        frame_clip_[ 6 ].x = width_frame_ * 6;
        frame_clip_[ 6 ].y = 0;
        frame_clip_[ 6 ].w = width_frame_;
        frame_clip_[ 6 ].h = height_frame_;

        frame_clip_[ 7 ].x = width_frame_ * 7;
        frame_clip_[ 7 ].y = 0;
        frame_clip_[ 7 ].w = width_frame_;
        frame_clip_[ 7 ].h = height_frame_;
    }
}


void ThreatsObject::SetAnimationPos(const int& pos_x_a, const int& pos_x_b)
{
    animation_a_ = pos_x_a;
    animation_b_ = pos_x_b;
}


void ThreatsObject::ImpMoveType(SDL_Renderer* screen)
{
    if (type_move_ == STATIC_TH)
    {
        ;//
    }
    else
    {
        if (on_ground_ == true)
        {
            if (x_pos_ > animation_b_)
            {
                input_type_.left_ = 1;
                input_type_.right_ = 0;
                LoadImg("img//threat_left.png", screen);
            }
            else if (x_pos_ < animation_a_)
            {
                input_type_.right_ = 1;
                input_type_.left_ = 0;
                LoadImg("img//threat_right.png", screen);
            }
        }
        else
        {
            if (input_type_.left_ == 1)
            {
                LoadImg("img//threat_left.png", screen);
            }
        }
    }
}


void ThreatsObject::DoThreats(Map& g_map, SDL_Renderer* screen)//Threats move
{
    if (think_time_ == 0)
    {
        x_val_ = 0;
        y_val_ += THREAT_GRAVITY_SPEED;

        if (y_val_ >= MAX_FALL_SPEED)
        {
            y_val_ = MAX_FALL_SPEED;
        }

        if (input_type_.left_ == 1)
        {
            x_val_ -= THREAT_SPEED;
        }

        else if (input_type_.right_ == 1)
        {
            x_val_ += THREAT_SPEED;
        }

//        if (input_type_.jump_ == 1)
//        {
//            if (on_ground_ == 1)
//            {
//                y_val_ = -THREAT_HIGHT_VAL;
//            }
//
//            input_type_.jump_ = 0;
//        }

        CheckToMap(g_map, screen);

    }

    else if (think_time_ > 0)
    {
        think_time_--;

        if (think_time_ == 0)
        {
            InitThreats();
        }
    }
}


void ThreatsObject::CheckToMap(Map& g_map, SDL_Renderer* screen)
{
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;

    on_ground_ = 0;

    //Check Horizontal
    int height_min = height_frame_ ;//SDLCommonFunction::GetMin(height_frame_, TILE_SIZE);

    x1 = (x_pos_ + x_val_) / TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

    y1 = (y_pos_) / TILE_SIZE;
    y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

    // Check x1, x2 with full width of map
    // Check y1, y2 with full heigth of map
    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (x_val_ > 0) // when object is moving by right  ===>
        {
            // Check current position of map. It is not blank_tile.
            if ((g_map.tile[y1][x2] != BLANK_TILE && g_map.tile[y1][x2] != STATE_MONEY) || (g_map.tile[y2][x2] != BLANK_TILE && g_map.tile[y2][x2] != STATE_MONEY))
            {
               // Fixed post of object at current post of map.
               // => Cannot moving when press button
                x_pos_ = x2 * TILE_SIZE;
                x_pos_ -= width_frame_ + 1;
                x_val_ -= THREAT_SPEED;
                input_type_.left_ = 1;
                input_type_.right_ = 0;
                LoadImg("img//threat_left.png", screen);
            }
        }

        else if (x_val_ < 0) // When moving by left    <====
        {
            if ((g_map.tile[y1][x1] != BLANK_TILE && g_map.tile[y1][x1] != STATE_MONEY) || (g_map.tile[y2][x1] != BLANK_TILE && g_map.tile[y2][x1] != STATE_MONEY))
            {
                x_pos_ = (x1 + 1) * TILE_SIZE;
                x_val_ += THREAT_SPEED;
                input_type_.right_ = 1;
                input_type_.left_ = 0;
                LoadImg("img//threat_right.png", screen);
            }
        }

    }
    // Check vertical
    int width_min = width_frame_ ;//SDLCommonFunc::GetMin(width_frame_, TILE_SIZE);

    x1 = (x_pos_) / TILE_SIZE;
    x2 = (x_pos_ + width_min) / TILE_SIZE;

    y1 = (y_pos_ + x_val_) / TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (y_val_ > 0)
        {
            //Similar for vertical
            if ((g_map.tile[y2][x1] != BLANK_TILE && g_map.tile[y2][x1] != STATE_MONEY) || (g_map.tile[y2][x2] != BLANK_TILE && g_map.tile[y2][x2] != STATE_MONEY))
            {
                y_pos_ = y2 * TILE_SIZE;
                y_pos_ -= height_frame_;

                y_val_ = 0;

                on_ground_ = 1;
            }
        }
        else if (y_val_ < 0)
        {
            if ((g_map.tile[y1][x1] != BLANK_TILE && g_map.tile[y1][x1] != STATE_MONEY) || (g_map.tile[y1][x2] != BLANK_TILE && g_map.tile[y1][x2] != STATE_MONEY))
            {
                y_pos_ = (y1 + 1) * TILE_SIZE;

                y_val_ = 0;
            }
        }
    }

    //If there is not collision with map tile.
    x_pos_ += x_val_;
    y_pos_ += y_val_;

    if (x_pos_ < 0)
    {
        x_pos_ = 0;
    }
    else if (x_pos_ + width_frame_ >= g_map.max_x_)
    {
        x_pos_ = g_map.max_x_ - width_frame_ - 1;
    }

    if (y_pos_ > g_map.max_y_)
    {
        think_time_ = 60;
    }
}

void ThreatsObject::Show(SDL_Renderer* des)
{
    if (think_time_ == 0)
    {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;
        frame_++;
        if( frame_ >= 8 )
        {
            frame_ = 0;
        }

        SDL_Rect* currentClip = &frame_clip_[frame_];
        SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};
        if (currentClip != NULL)
        {
            renderQuad.w = currentClip->w;
            renderQuad.h = currentClip->h;
        }

        SDL_RenderCopy(des, p_object_, currentClip, &renderQuad );
    }
}

void ThreatsObject::InitBulletForBigThreats(BulletObject* p_bullet,  SDL_Renderer* screen)
{
    if (p_bullet != NULL)
    {
        bool ret = p_bullet->LoadImg("img//bullet_threat.png", screen);
        if (ret)
        {
            p_bullet->set_is_move(true);
            p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
            //p_bullet->set_bullet_type(BulletObject::SPHERE);
            p_bullet->SetRect(rect_.x + 20, rect_.y + 10);
            p_bullet->set_x_val(15);//bullet speed
            bullet_list_.push_back(p_bullet);
        }
    }
}

void ThreatsObject::InitBulletForSmallThreats(BulletObject* p_bullet,  SDL_Renderer* screen)
{
    if (p_bullet != NULL)
    {
        bool ret = p_bullet->LoadImg("img//player_bullet1.png", screen);
        if (ret)
        {
            p_bullet->set_is_move(true);
            p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
            //p_bullet->set_bullet_type(BulletObject::SPHERE);
            p_bullet->SetRect(rect_.x + 5, rect_.y + 20);
            p_bullet->set_x_val(15);//bullet speed
            bullet_list_.push_back(p_bullet);
        }
    }
}


void ThreatsObject::MakeBulletForBigThreats(SDL_Renderer* screen, const int& x_limit, const int& y_limit)
{
    if (is_alive_)
    {
        for (int i = 0; i < (int)bullet_list_.size(); i++)
        {
            BulletObject* p_bullet = bullet_list_.at(i);
            if (p_bullet != NULL)
            {
                if (is_stop_bullet_ == false)
                {
                    if (p_bullet->get_is_move())
                    {
                        int bullet_distance = rect_.x + width_frame_ - p_bullet->GetRect().x;
                        if ( bullet_distance > 0 && bullet_distance < BULLET_OBJECT_DISTANCE)
                        {
                            p_bullet->HandleMove(x_limit, y_limit);
                            p_bullet->Render(screen);

                        }
                        else
                        {
                            p_bullet->set_is_move(false);
                        }
                    }
                    else
                    {
                        p_bullet->set_is_move(true);
                        p_bullet->SetRect(this->rect_.x + 5, this->rect_.y + 10);
                    }
                }
            }
        }
    }
}

void ThreatsObject::MakeBulletForSmallThreats(SDL_Renderer* screen, const int& x_limit, const int& y_limit)
{
    if (is_alive_)
    {
        for (int i = 0; i < (int)bullet_list_.size(); i++)
        {
            BulletObject* p_bullet = bullet_list_.at(i);
            if (p_bullet != NULL)
            {
                if (is_stop_bullet_ == false)
                {
                    if (p_bullet->get_is_move())
                    {
                        int bullet_distance = rect_.x + width_frame_ - p_bullet->GetRect().x;
                        if ( bullet_distance > 0 && bullet_distance < BULLET_OBJECT_DISTANCE)
                        {
                            p_bullet->HandleMove(x_limit, y_limit);
                            p_bullet->Render(screen);

                        }
                        else
                        {
                            p_bullet->set_is_move(false);
                        }
                    }
                    else
                    {
                        p_bullet->set_is_move(true);
                        p_bullet->SetRect(this->rect_.x, this->rect_.y + 20);
                    }
                }
            }
        }
    }
}

void ThreatsObject::RemoveBullet(const int& idx)
{
    if (bullet_list_.size() > 0 && idx < (int)bullet_list_.size())
    {
        BulletObject* th_bullet = bullet_list_.at(idx);
        bullet_list_.erase(bullet_list_.begin() + idx);

        if (th_bullet)
        {
            //delete th_bullet;
            th_bullet = NULL;
        }
    }
}

void ThreatsObject::ResetBullet(BulletObject* p_bullet, bool is_big_threat)
{
    if (is_big_threat)
    {
        p_bullet->SetRect(rect_.x + 5, rect_.y + 10);
        p_bullet->set_x_val(15);
    }
    else
    {
        p_bullet->SetRect(rect_.x, rect_.y + 20);
        p_bullet->set_x_val(15);
    }
}

void ThreatsObject::Reset(const int x_border, const int y_border)
{
    is_stop_bullet_ = false;
    x_pos_ = SCREEN_WIDTH - 100;
    y_pos_ = SCREEN_HEIGHT*0.5;
    for (int i = 0; i < bullet_list_.size(); i++)
    {
        BulletObject* p_bullet = bullet_list_.at(i);
        if (p_bullet != NULL)
        {
            ResetBullet(p_bullet, is_big_threat);
        }
    }
}

