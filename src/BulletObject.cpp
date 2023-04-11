#include "BulletObject.h"

BulletObject::BulletObject()
{
    x_val_ = 0;
    y_val_ = 0;
    move_type_ = LINE_TYPE;
//    rect_.x = SCREEN_WIDTH;
//    rect_.y = 0;
//    width_frame_ = 0;
//    height_frame_ = 0;
//
//    x_pos_ = 0;
//    y_pos_ = 0;
//    on_ground_ = 0;
//    think_time_ = 0;
//    frame_ = 0;
}

BulletObject::~BulletObject()
{

}

BulletObject* BulletObject::Clone()
{
    BulletObject* p_object_clone = new BulletObject();
    p_object_clone->bullet_dir_ = this->bullet_dir_;
    p_object_clone->is_move_ = this->is_move_;
    p_object_clone->move_type_ = this->move_type_;
    p_object_clone->x_val_ = this->x_val_;
    p_object_clone->y_val_ = this->y_val_;

    return p_object_clone;
}

void BulletObject::HandleMove(const int& x_border, const int& y_border, bool is_player)
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
        if (move_type_ == LINE_TYPE)
        {
            rect_.x += x_val_;
            if (rect_.x > x_border)
            {
                is_move_ = false;
            }
        }
        else if (move_type_ == SIN_TYPE)
        {
            rect_.x += x_val_;
            rect_.y += 50*cos(rect_.x);

            if (rect_.x > x_border)
            {
                is_move_ = false;
            }
        }
    }
    else if (bullet_dir_ == DIR_LEFT)
    {
        if (move_type_ == LINE_TYPE)
        {
            rect_.x -= x_val_;
            if (rect_.x < 0)
            {
                is_move_ = false;
            }
        }
        else if (move_type_ == SIN_TYPE)
        {
            rect_.x -= x_val_;
            rect_.y -= 50*cos(rect_.x);

            if (rect_.x < 0)
            {
                is_move_ = false;
            }
        }
    }
}


void BulletObject::HandleMoveRightToLeft(const int& origin_x)
{
    if (move_type_ == LINE_TYPE)
    {
        rect_.x -= x_val_;
    }
    else if (move_type_ == SIN_TYPE)
    {
        rect_.x -= x_val_;
        if (rect_.x < SCREEN_WIDTH*0.5)
        {
            rect_.y -= 100*cos(rect_.x);
        }
    }

    int distance_bullet = origin_x - rect_.x;
    if (distance_bullet > BULLET_OBJECT_DISTANCE)
    {
        is_move_ = false;
    }
}

void BulletObject::HandleInputAction(SDL_Event events)
{

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
