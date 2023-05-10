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


//bool BulletObject::CheckToMap(Map& g_map, SDL_Renderer* screen)
//{
//    int x1 = 0;
//    int x2 = 0;
//    int y1 = 0;
//    int y2 = 0;
//
//
//    //Check Horizontal
//    int height_min = height_frame_ ;//SDLCommonFunction::GetMin(height_frame_, TILE_SIZE);
//
//    x1 = (x_pos_ + x_val_) / TILE_SIZE;
//    x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;
//
//    y1 = (y_pos_) / TILE_SIZE;
//    y2 = (y_pos_ + height_min - 1) / TILE_SIZE;
//
//    // Check x1, x2 with full width of map
//    // Check y1, y2 with full heigth of map
//    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
//    {
//        if (x_val_ > 0) // when object is moving by right  ===>
//        {
//            // Check current position of map. It is not blank_tile.
//            if ((g_map.tile[y1][x2] != BLANK_TILE && g_map.tile[y1][x2] != STATE_MONEY) || (g_map.tile[y2][x2] != BLANK_TILE && g_map.tile[y2][x2] != STATE_MONEY))
//            {
//               // Fixed post of object at current post of map.
//               // => Cannot moving when press button
////               x_pos_ = x2 * TILE_SIZE;
////               x_pos_ -= width_frame_ + 1;
////               x_val_ = 0;
////               input_type_.left_ = 1;
////               input_type_.right_ = 0;
////               LoadImg("img//threat_left.png", screen);
//                //Free();
//                return true;
//            }
//        }
//
//        else if (x_val_ < 0) // When moving by left    <====
//        {
//            if ((g_map.tile[y1][x1] != BLANK_TILE && g_map.tile[y1][x1] != STATE_MONEY) || (g_map.tile[y2][x1] != BLANK_TILE && g_map.tile[y2][x1] != STATE_MONEY))
//            {
//                //x_pos_ = (x1 + 1) * TILE_SIZE;
//                //x_val_ = 0;
// //               input_type_.right_ = 1;
////                input_type_.left_ = 0;
////                LoadImg("img//threat_right.png", screen);
//                //Free();
//                return true;
//            }
//        }
//
//    }
//    // Check vertical
//    int width_min = width_frame_ ;//SDLCommonFunc::GetMin(width_frame_, TILE_SIZE);
//
//    x1 = (x_pos_) / TILE_SIZE;
//    x2 = (x_pos_ + width_min) / TILE_SIZE;
//
//    y1 = (y_pos_ + x_val_) / TILE_SIZE;
//    y2 = (y_pos_ + y_val_ + height_frame_) / TILE_SIZE;
//
//    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
//    {
//        if (y_val_ > 0)
//        {
//            //Similar for vertical
//            if ((g_map.tile[y2][x1] != BLANK_TILE && g_map.tile[y2][x1] != STATE_MONEY) || (g_map.tile[y2][x2] != BLANK_TILE && g_map.tile[y2][x2] != STATE_MONEY))
//            {
////                y_pos_ = y2 * TILE_SIZE;
////                y_pos_ -= height_frame_;
////
////                y_val_ = 0;
////
////                on_ground_ = 1;
//                //Free();
//                return true;
//            }
//        }
//        else if (y_val_ < 0)
//        {
//            if ((g_map.tile[y1][x1] != BLANK_TILE && g_map.tile[y1][x1] != STATE_MONEY) || (g_map.tile[y1][x2] != BLANK_TILE && g_map.tile[y1][x2] != STATE_MONEY))
//            {
////                y_pos_ = (y1 + 1) * TILE_SIZE;
////
////                y_val_ = 0;
//                return true;
//            }
//        }
//    }
//}
//
//    //If there is not collision with map tile.
////    x_pos_ += x_val_;
////    y_pos_ += y_val_;
////
////    if (x_pos_ < 0)
////    {
////        x_pos_ = 0;
////    }
////    else if (x_pos_ + width_frame_ >= g_map.max_x_)
////    {
////        x_pos_ = g_map.max_x_ - width_frame_ - 1;
////    }
////
////    if (y_pos_ > g_map.max_y_)
////    {
////        think_time_ = 60;
////    }
//
