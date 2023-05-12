#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_

#include "CommonFunction.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define NUM_DYNAMIC_THREAT 40
#define NUM_STATIC_THREAT 20

#define WIDTH_THREAT 44
#define HEIGHT_THREAT 50

#define THREAT_GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define THREAT_SPEED 2

#define NUM_FRAME 8

#define DYNAMIC_THREAT_FREQUENCY 500
#define STATIC_THREAT_FREQUENCY 1200

class ThreatsObject : public BaseObject
{
public:
    ThreatsObject();
    ~ThreatsObject();
    void HandleMove(const int x_boder, const int y_border);

    void set_x_val(int xp)
    {
        x_val_ = xp;
    }
    void set_y_val(int yp)
    {
        y_val_ = yp;
    }

    void set_xpos(const int& xps)
    {
        x_pos_ = xps;
    }
    void set_ypos(const int& yps)
    {
        y_pos_ = yps;
    }
    int get_x_pos()
    {
        return x_pos_;
    }
    int get_y_pos()
    {
        return y_pos_;
    }
    bool get_is_alive()
    {
        return is_alive_;
    }
    void set_is_alive(bool is_alive)
    {
        is_alive_ = is_alive;
    }

    void InitBulletForBigThreats(BulletObject* p_bullet, SDL_Renderer* screen);
    void InitBulletForSmallThreats(BulletObject* p_bullet,  SDL_Renderer* screen);
    void MakeBulletForBigThreats(Map& g_map, SDL_Renderer* des, const int& x_limit, const int& y_limit);
    void MakeBulletForSmallThreats(Map& g_map, SDL_Renderer* des, const int& x_limit, const int& y_limit);

    void Reset(const int x_border, const int y_border, bool is_big_threat);

    std::vector<BulletObject*> get_bullet_list() const
    {
        return bullet_list_;
    }
    void set_bullet_list(const std::vector<BulletObject*>& am_list)
    {
        bullet_list_ = am_list;
    }

    void SetMapXY(const int map_x, const int map_y)
    {
        map_x_ = map_x, map_y_ = map_y;
    }
    void RemoveBullet(const int& idx);
    void ResetBullet(BulletObject* p_bullet, bool is_big_threat);
    void CheckToMap(Map& g_map, SDL_Renderer* screen);
    void DoThreats(Map& g_map, SDL_Renderer* screen);
    void ImpMoveType(SDL_Renderer* screen);
    void InitThreats();
    void SetAnimationPos(const int& pos_x_a, const int& pos_x_b);
    void Show(SDL_Renderer* des);
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void set_clips();
    void set_type_move(const int& tm)
    {
        type_move_ = tm;
    }
    void set_input_left(const int& ipleft)
    {
        input_type_.left_ = ipleft;
    }
    int get_width_frame() const
    {
        return width_frame_;
    }
    int get_height_frame() const
    {
        return height_frame_;
    }
    SDL_Rect GetRectFrame();

    enum TypeMove
    {
        STATIC_TH = 0,
        MOVE_IN_SPACE_TH = 1,
    };

private:
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
    SDL_Rect frame_clip_[NUM_FRAME];
    int width_frame_;
    int height_frame_;
    int frame_;
    int animation_a_;
    int animation_b_;
    int type_move_;
    std::vector<BulletObject*> bullet_list_;
    bool is_big_threat;
};

#endif //THREATS_OBJECT_H_
