#include "BaseObject.h"
#include "TextObject.h"


BaseObject::BaseObject()
{
    p_object_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

BaseObject::~BaseObject()
{
    Free();
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen)
{

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface != NULL)
    {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(screen, loadedSurface);
        if (newTexture != NULL)
        {
            //Get image dimensions
            rect_.w = loadedSurface->w;
            rect_.h = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    //Return success
    p_object_ = newTexture;
    return p_object_ != NULL;
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip /*=NULL*/)
{
    SDL_Rect renderQuad = {rect_.x, rect_.y, rect_.w, rect_.h};
    SDL_RenderCopy(des, p_object_, clip, &renderQuad);
}

void BaseObject::setColor(const Uint8& red, const Uint8& green, const Uint8& blue)
{
    SDL_SetTextureColorMod(p_object_, red, green, blue);
}

void BaseObject::setBlendMode(const SDL_BlendMode& blending)
{
    SDL_SetTextureBlendMode(p_object_, blending);
}

void BaseObject::setAlpha(const Uint8& alpha)
{
    SDL_SetTextureAlphaMod(p_object_, alpha);
}


void BaseObject::Free()
{
    if(p_object_ != NULL)
    {
        SDL_DestroyTexture(p_object_);
        p_object_ = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}


//int BaseObject::ShowMenu(SDL_Renderer* des, TTF_Font* font)
//{
//    bool ret = LoadImg("img//menu_background.png", g_screen);
//    //std::cout << ret;
//    //return ret;
//
//    if (ret == true)
////    {
//        return 1;
//
//    else return 0;
////    }
////    else
////    {
//        const int MenuItemNum = 2;
//        SDL_Rect pos_arr[MenuItemNum];
//        pos_arr[0].x = 200;
//        pos_arr[0].y = 400;
//
//        pos_arr[1].x = 200;
//        pos_arr[1].y = 450;
//
//        TextObject text_menu[MenuItemNum];
//
//        text_menu[0].SetText("CLICK TO START");
//        text_menu[0].setColor(TextObject::WHITE_TEXT);
//        text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);
//
//        text_menu[1].SetText("EXIT");
//        text_menu[1].setColor(TextObject::RED_TEXT);
//        text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);
//
//
//        bool selected[MenuItemNum] = {0, 0};
//        int xm = 0;
//        int ym = 0;
//        SDL_Event m_event;
//        while (true)
//        {
//            Render(des);
//            for (int i = 0; i < MenuItemNum; ++i)
//            {
//                text_menu[i].loadFromRenderedText(g_font_text, g_screen);
//            }
//
//            while (SDL_PollEvent(&m_event))
//            {
//                switch (m_event.type)
//                {
//                case SDL_QUIT:
//                    return 1;
//                case SDL_MOUSEMOTION:
//                {
//                    xm = m_event.motion.x;
//                    ym = m_event.motion.y;
//
//                    for (int i = 0; i < MenuItemNum; i++)
//                    {
//                        if (SDLCommonFunction::CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))
//                        {
//                            if (selected[i] == false)
//                            {
//                                selected[i] = 1;
//                                text_menu[i].setColor(TextObject::RED_TEXT);
//                            }
//                        }
//                        else
//                        {
//                            if (selected[i] == true)
//                            {
//                                selected[i] = 0;
//                                text_menu[i].setColor(TextObject::WHITE_TEXT);
//                            }
//                        }
//                    }
//                }
//                break;
//                case SDL_MOUSEBUTTONDOWN:
//                {
//                    xm = m_event.button.x;
//                    ym = m_event.button.y;
//
//                    for (int i = 0; i < MenuItemNum; i++)
//                    {
//                        if (SDLCommonFunction::CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))
//                        {
//                            return i;
//                        }
//                    }
//                }
//                break;
//                case SDL_KEYDOWN:
//                    if (m_event.key.keysym.sym == SDLK_ESCAPE)
//                    {
//                        return 1;
//                    }
//                default:
//                    break;
//                }
//            }
//
//            //SDL_Flip(des);
////        }
////
//    }
//}
