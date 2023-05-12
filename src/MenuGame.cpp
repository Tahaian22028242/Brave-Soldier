#include "MenuGame.h"

MenuGame::MenuGame()
{
    rect_.x = 0;
    rect_.y = 0;
}

MenuGame::~MenuGame()
{
    m_acType = AC_NONE;
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

void MenuGame::HandlePlayButton(SDL_Event event, SDL_Renderer* screen, bool &InMenuGame)
{
	if (IsChosen(event))
	{
        LoadButton("img//PlayButton2.png",screen);
	    if(event.type == SDL_MOUSEBUTTONDOWN)
		{
            InMenuGame = false;
            Mix_Chunk* beep_sound = Mix_LoadWAV(kSoundBeep);
            if (beep_sound != NULL)
                Mix_PlayChannel(-1, beep_sound, 0);
		}
    }
    else
    {
        LoadButton("img//PlayButton.png",screen);
    }
}

void MenuGame::HandleQuitButton(SDL_Event event, SDL_Renderer* screen, bool &quit, bool &InMenu)
{
    if (IsChosen(event))
	{
	    LoadButton("img//QuitButton2.png",screen);
	    if(event.type == SDL_MOUSEBUTTONDOWN)
		{
            quit = true;
            InMenu = false;
            Mix_Chunk* beep_sound = Mix_LoadWAV(kSoundBeep);
            if (beep_sound != NULL)
                Mix_PlayChannel(-1, beep_sound, 0);
		}
    }
    else
    {
        LoadButton("img//QuitButton.png",screen);
    }
}

void MenuGame::HandleQuitButtonAtGameOver(SDL_Event event, SDL_Renderer* screen, bool &quit, bool &InMenu)
{
    if (IsChosen(event))
	{
	    LoadButton("img//QuitButton2 - Copy.png",screen);
	    if(event.type == SDL_MOUSEBUTTONDOWN)
		{
            quit = true;
            InMenu = false;
            Mix_Chunk* beep_sound = Mix_LoadWAV(kSoundBeep);
            if (beep_sound != NULL)
                Mix_PlayChannel(-1, beep_sound, 0);
		}
    }
    else
    {
        LoadButton("img//QuitButton - Copy.png",screen);
    }
}

void MenuGame::HandleRetryButton(SDL_Event event, SDL_Renderer* screen, bool &quit)
{
    if (IsChosen(event))
	{
	    LoadButton("img//PlayAgainButton2.png",screen);
	    if(event.type==SDL_MOUSEBUTTONDOWN)
		{
		    quit = false;
            Mix_Chunk* beep_sound = Mix_LoadWAV(kSoundBeep);
            if (beep_sound != NULL)
                Mix_PlayChannel(-1, beep_sound, 0);

            m_acType = AC_REPLAY;
		}
	}
	else
    {
        LoadButton("img//PlayAgainButton.png",screen);
    }
}
