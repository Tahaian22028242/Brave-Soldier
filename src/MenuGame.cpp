#include "MenuGame.h"

MenuGame::MenuGame()
{
    rect_.x = 0;
    rect_.y = 0;
}

MenuGame::~MenuGame()
{

}

bool MenuGame::LoadButton(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);
    return ret;
}

bool MenuGame::IsChosen(SDL_Event event)
{
	if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool chosen = true;
		if (x < rect_.x)
		{
			chosen = false;
		}
		else if (x > rect_.x + rect_.w)
		{
			chosen = false;
		}
		else if (y < rect_.y)
		{
			chosen = false;
		}
		else if (y > rect_.y + rect_.h)
		{
			chosen = false;
		}
		return chosen;
	}
}

void MenuGame::HandlePlayButton(SDL_Event event, SDL_Renderer* screen, bool &InMenuGame, TTF_Font* font)
{
    SDL_Rect pos_arr_start;
    pos_arr_start.x = 200;
    pos_arr_start.y = 400;

    TextObject text_start;

    text_start.SetText("CLICK TO START");
    text_start.setColor(TextObject::WHITE_TEXT);
    text_start.SetRect(pos_arr_start.x, pos_arr_start.y);

    int i = 0;
    while (i % 5 == 0) {
        text_start.loadFromRenderedText(font, screen);
        i++;
        if (i = 1000) i = 0;
    }

	if (IsChosen(event))
	{
	    text_start.setColor(TextObject::RED_TEXT);
	    text_start.loadFromRenderedText(font, screen);
	    if(event.type == SDL_MOUSEBUTTONDOWN)
		{
            InMenuGame = false;
		}
    }
    else
    {
        text_start.setColor(TextObject::WHITE_TEXT);
	    int i = 0;
        while (i % 5 == 0) {
            text_start.loadFromRenderedText(font, screen);
            i++;
            if (i = 1000) i = 0;
        }
    }
}

void MenuGame::HandleQuitButton(SDL_Event event, SDL_Renderer* screen, bool &quit, TTF_Font* font)
{
    SDL_Rect pos_arr_quit;
    pos_arr_quit.x = 200;
    pos_arr_quit.y = 450;

    TextObject text_quit;
    text_quit.SetText("EXIT");
    text_quit.setColor(TextObject::WHITE_TEXT);
    text_quit.SetRect(pos_arr_quit.x, pos_arr_quit.y);

    if (IsChosen(event))
	{
	    text_quit.setColor(TextObject::RED_TEXT);
	    text_quit.loadFromRenderedText(font, screen);
	    if(event.type == SDL_MOUSEBUTTONDOWN)
		{
            quit = !quit;
		}
    }
    else
    {
        text_quit.setColor(TextObject::WHITE_TEXT);
        text_quit.loadFromRenderedText(font, screen);
    }
}

//void MenuGame::HandleRetryButton(SDL_Event event, SDL_Renderer* screen, bool& quit, vector<ThreatObject*> threats_list, MainObject &p_object, vector<BulletObject*> &bullet_list, bool &quit)
//{
//    if (IsInside(event))
//	{
//	    LoadButton("img//retry2.png",screen);
//	    if(event.type==SDL_MOUSEBUTTONDOWN)
//		{
//		    quit = false;
//		}
//	}
//	else
//    {
//        LoadButton("retry.png",screen);
//    }
//}
