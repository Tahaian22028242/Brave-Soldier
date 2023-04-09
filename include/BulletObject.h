#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "BaseObject.h"
#include <math.h>

class BulletObject : public BaseObject
{
public:
    BulletObject();
    ~BulletObject();


    enum BulletDir
    {
        DIR_RIGHT = 20,
        DIR_LEFT = 21,
        DIR_UP = 22,
        DIR_UP_LEFT = 23,
        DIR_UP_RIGHT = 24,
        DIR_DOWN_LEFT = 25,
        DIR_DOWN_RIGHT = 26,
    };

    enum BulletType
    {
        NONE,
        LASER,
        SPHERE
    };

    enum MoveType
    {
        LINE_TYPE = 10,
        SIN_TYPE = 11
    };

    void HandleInputAction(SDL_Event events);
    void HandleMove(const int& x_border, const int& y_border, bool is_player = true);

    void set_x_val(const int& x_val)
    {
        x_val_ = x_val;
    }
    void set_y_val(const int& y_val)
    {
        y_val_ = y_val;
    }

    int get_x_val() const
    {
        return x_val_;
    }
    int get_y_val() const
    {
        return y_val_;
    }
    void set_is_move(const bool& is_move)
    {
        is_move_ = is_move;
    }
    bool get_is_move()const
    {
        return is_move_;
    }
    void set_bullet_dir(const int& dir_type)
    {
        bullet_dir_ = dir_type;
    }
    void HandleMoveRightToLeft(const int& origin_x);
    void set_move_type(const int& moveType)
    {
        move_type_ = moveType;
    }
    BulletObject* Clone();
//    bool CheckToMap(Map& g_map, SDL_Renderer* screen);

private:
    //int x_val_;
    //int y_val_;
    bool is_move_;
    int bullet_dir_;
    int move_type_;
    int map_x_;
    int map_y_;
    float x_val_;
    float y_val_;
    bool is_alive_;
    bool is_stop_bullet_;
    float x_pos_;
    float y_pos_;
    int on_ground_;
    int think_time_;
    Input input_type_;
//    SDL_Rect frame_clip_[NUM_FRAME];
    int width_frame_;
    int height_frame_;
    int frame_;
    int animation_a_;
    int animation_b_;
    int type_move_;
//    std::vector<BulletObject*> bullet_list_
};

#endif
