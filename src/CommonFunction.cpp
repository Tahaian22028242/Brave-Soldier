#include "CommonFunction.h"
//#include "TextObject.h"
//#include "BaseObject.h"

bool SDLCommonFunction::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    int left_a = object1.x;
    int right_a = object1.x + object1.w;
    int top_a = object1.y;
    int bottom_a = object1.y + object1.h;

    int left_b = object2.x;
    int right_b = object2.x + object2.w;
    int top_b = object2.y;
    int bottom_b = object2.y + object2.h;

    if (right_a >= left_b && right_b >= left_a && bottom_a >= top_b && bottom_b >= top_a)
    {
        return true;
    }
    return false;
}

bool SDLCommonFunction::CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
  if (x >= rect.x && x <= rect.x + rect.w &&
      y >= rect.y && y <= rect.y + rect.h)
  {
    return true;
  }
  return false;
}

int SDLCommonFunction::MakeRandValue(const int& div_val /*400*/)
{
    int rand_y = rand()%div_val;
    if (rand_y > SCREEN_HEIGHT - 200)
    {
        rand_y = SCREEN_HEIGHT*0.3;
    }
    return rand_y;
}

