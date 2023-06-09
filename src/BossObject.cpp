#include "BossObject.h"


BossObject::BossObject()
{
    rect_.x = SCREEN_WIDTH;
    rect_.y = 0;
    frame_ = 0;
    x_val_ = 0.0;
    y_val_ = 0.0;
    x_pos_ = 0;
    y_pos_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    think_time_ = 0;
    map_x_ = 0;
    map_y_ = 0;
    num_bullet_die_ = 0;
    m_die = false;
}

BossObject::~BossObject()
{

}

SDL_Rect BossObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = rect_.w/FRAME_NUM_32;
    rect.h = rect_.h;

    return rect;
}

bool BossObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);

    if (ret == true)
    {
        width_frame_ = rect_.w/FRAME_NUM_32;
        height_frame_ = rect_.h;
    }

    return ret;
}

void BossObject::set_clips()
{
    //Clip the spriteshe
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        for (int i = 0; i < FRAME_NUM_32; ++i)
        {
            frame_clip_[i].x = width_frame_*i;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
}


void BossObject::Show(SDL_Renderer* des)
{
    if (m_die == true)
        return;

    if (think_time_ == 0)
    {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;
        frame_++;
        if( frame_ >= 32 )
        {
            frame_ = 0;
        }

        SDL_Rect* currentClip = &frame_clip_[frame_];
        SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};
        SDL_RenderCopy(des, p_object_, currentClip, &renderQuad );
    }
}

void BossObject::DoBoss(Map& g_map)
{
    if (m_die == true)
        return;

    if (think_time_ == 0)
    {
        x_val_ = 0;
        y_val_ += BOSS_GRAVITY_SPEED;

        if (y_val_ >= MAX_FALL_SPEED)
        {
            y_val_ = MAX_FALL_SPEED;
        }

        if (input_type_.left_ == 1)
        {
            x_val_ -= BOSS_SPEED;
        }

        else if (input_type_.right_ == 1)
        {
            x_val_ += BOSS_SPEED;
        }

        if (input_type_.jump_ == 1)
        {
            if (on_ground_ == 1)
            {
                y_val_ = -BOSS_HIGHT_VAL;
            }

            input_type_.jump_ = 0;
        }

        CheckToMap(g_map);

    }

    if (think_time_ > 0)
    {
        think_time_--;

        if (think_time_ == 0)
        {
            InitBoss();
        }
    }
}

void BossObject::InitBoss()
{
    x_val_ = 0;
    y_val_ = 0;

    if (x_pos_ > 256)
    {
        x_pos_ -= 256;
    }
    else
        x_pos_ = 0;
    y_pos_ = 0;
    think_time_ = 0;
    input_type_.left_ = 1;
}


void BossObject::CheckToMap(Map& g_map)
{
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;

    on_ground_ = 0;

    //Check Horizontal
    int height_min =   height_frame_ ;//SDLCommonFunction::GetMin(height_frame_, TILE_SIZE);

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
            if ((g_map.tile[y1][x2] != BLANK_TILE) || (g_map.tile[y2][x2] != BLANK_TILE))
            {
                // Fixed post of object at current post of map.
                // => Cannot moving when press button
                x_pos_ = x2 * TILE_SIZE;
                x_pos_ -= width_frame_ + 1;
                x_val_ = 0; // cannot moving
            }
        }
        else if (x_val_ < 0) // When moving by left    <====
        {
            if ((g_map.tile[y1][x1] != BLANK_TILE) || (g_map.tile[y2][x1] != BLANK_TILE))
            {
                x_pos_ = (x1 + 1) * TILE_SIZE;
                x_val_ = 0;
            }
        }
    }


    // Check vertical
    int width_min = width_frame_;// SDLCommonFunction::GetMin(width_frame_, TILE_SIZE);

    x1 = (x_pos_) / TILE_SIZE;
    x2 = (x_pos_ + width_min) / TILE_SIZE;

    y1 = (y_pos_ + y_val_) / TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (y_val_ > 0)
        {
            //Similar for vertical
            if ((g_map.tile[y2][x1] != BLANK_TILE) || (g_map.tile[y2][x2] != BLANK_TILE))
            {
                y_pos_ = y2 * TILE_SIZE;
                y_pos_ -= height_frame_;

                y_val_ = 0;

                on_ground_ = 1;
            }
        }
        else if (y_val_ < 0)
        {
            if ((g_map.tile[y1][x1] != BLANK_TILE) || (g_map.tile[y1][x2] != BLANK_TILE))
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

void BossObject::InitBullet(SDL_Renderer* screen)
{
    BulletObject* p_bullet = new BulletObject();
    bool ret = p_bullet->LoadImg(g_name_boss_bullet, screen);
    if (ret)
    {
        p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
        p_bullet->set_is_move(true);
        p_bullet->SetRect(rect_.x - 50, rect_.y + height_frame_ - 30);
        p_bullet->set_x_val(15);
        bullet_list_.push_back(p_bullet);
    }
}


void BossObject::MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit)
{
    if (m_die == true)
        return;

    if (frame_ == 18)
    {
        InitBullet(des);
    }

    for (int i = 0; i < (int)bullet_list_.size(); i++)
    {
        BulletObject* p_bullet = bullet_list_.at(i);
        if (p_bullet != NULL)
        {
            if (p_bullet->get_is_move())
            {
                p_bullet->HandleMove(x_limit, y_limit);
                p_bullet->Render(des);
            }
            else
            {
                p_bullet->Free();
                bullet_list_.erase(bullet_list_.begin() + i);
            }
        }
    }
}

void BossObject::RemoveBullet(const int& idx)
{
    if (bullet_list_.size() > 0 && idx < (int)bullet_list_.size())
    {
        BulletObject* b_bullet = bullet_list_.at(idx);
        bullet_list_.erase(bullet_list_.begin() + idx);

        if (b_bullet)
        {
            b_bullet = NULL;
        }
    }
}

bool BossObject::CheckBulletDie()
{
    if (num_bullet_die_ >= BOSS_HEALTH)
    {
        m_die = true;
        return true;
    }

    return false;
}
