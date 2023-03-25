#ifndef Ammo_OBJECT_H_
#define Ammo_OBJECT_H_
#include "BaseObject.h"

#define WIDTH_LASER 35
#define HEIGHT_LASER 5

#define WIDTH_SPHERE 10
#define HEIGHT_SPHERE 10

class AmmoObject : public BaseObject
{
public:
  enum AmmoType
  {
    NONE = 0,
    LASER = 1,
    SPHERE = 2
  };

  AmmoObject();
  ~AmmoObject();
  void HandleInputAction(SDL_Event events);
  void HandleMove(const int& x_border, const int& y_border);

  int get_type() const {return Ammo_type_;}
  void set_type(const int& type) {Ammo_type_ = type;}

  bool get_is_move() const {return is_move_;}
  void set_is_move(bool is_move) {is_move_ = is_move;}
  void SetWidthHeight(const int& widht, const int& height) {rect_.w = widht; rect_.h = height;};
private:
  int x_val_;
  int y_val_;
  bool is_move_;
  int Ammo_type_;
};


#endif
