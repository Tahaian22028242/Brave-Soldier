#include "BulletObject.h"

BulletObject::BulletObject()
{
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
}

BulletObject::~BulletObject()
{

}


void BulletObject::HandleMove(const int& x_border, const int& y_border)
{

    if (bullet_dir_ == DIR_UP)
    {
        rect_.y -= y_val_;
        if (rect_.y < 0)
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_UP_RIGHT)
    {
        rect_.x += x_val_;
        if (rect_.x > x_border)
        {
            is_move_ = false;
        }

        rect_.y -= y_val_;
        if (rect_.y < 0)
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_UP_LEFT)
    {
        rect_.x -= x_val_;
        if (rect_.x < 0)
        {
            is_move_ = false;
        }

        rect_.y -= y_val_;
        if (rect_.y < 0)
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_RIGHT)
    {
        rect_.x += x_val_;
        if (rect_.x > x_border)
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_LEFT)
    {

        rect_.x -= x_val_;
        if (rect_.x < 0)
        {
            is_move_ = false;
        }
    }
}


bool BulletObject::CheckToMap(Map& g_map, SDL_Renderer* screen)
{

    int start_x = g_map.start_x_;
    int start_y = g_map.start_x_;

    int x = (rect_.x + x_val_ + start_x)/TILE_SIZE;
    int y = (rect_.y + start_y)/TILE_SIZE;

    if (x >= 0 && x < MAX_MAP_X && y >= 0 && y < MAX_MAP_Y)
    {
        int data = g_map.tile[y][x];
        if (data != BLANK_TILE)
        {
            if (bullet_dir_ == DIR_LEFT)
            {
                int x_pos = (x+1)*TILE_SIZE;
                rect_.x = x_pos - start_x;
            }
            else if (bullet_dir_ == DIR_RIGHT)
            {
                int x_pos = (x)*TILE_SIZE;
                rect_.x = x_pos - start_x;
            }
            is_move_ = false;
        }
    }
}
