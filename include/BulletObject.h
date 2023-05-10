#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "BaseObject.h"

#define BULLET_OBJECT_DISTANCE 300
#define BULLET_SPEED 10

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
        DIR_DOWN = 27,
    };

    enum BulletType
    {
        NONE,
        LASER,
        SPHERE
    };

    void HandleMove(const int& x_border, const int& y_border);

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
    void set_bullet_dir(const unsigned int& dir_type)
    {
        bullet_dir_ = dir_type;
    }
    unsigned int get_bullet_dir() const
    {
        return bullet_dir_;
    }
//    bool CheckToMap(Map& g_map, SDL_Renderer* screen);

private:
    int x_val_;
    int y_val_;
    bool is_move_;
    unsigned int bullet_dir_;
};

#endif
