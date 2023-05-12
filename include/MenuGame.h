#ifndef MENUGAME_H
#define MENUGAME_H
#include "BaseObject.h"


class MenuGame : public BaseObject
{
    public:
        MenuGame();
        ~MenuGame();

        enum ActionType
        {
            AC_NONE = 0,
            AC_REPLAY = 1,
        };

        bool LoadButton(std::string path,SDL_Renderer* screen);
        bool IsChosen(SDL_Event event);
        void HandlePlayButton(SDL_Event event, SDL_Renderer* screen, bool &InMenuGame);
        void HandleQuitButton(SDL_Event event, SDL_Renderer* screen, bool &quit, bool &InMenu);
        void HandleQuitButtonAtGameOver(SDL_Event event, SDL_Renderer* screen, bool &quit, bool &InMenu);
        void HandleRetryButton(SDL_Event event, SDL_Renderer* screen, bool &quit);
        void SetType(int type) {m_acType = type;}
        int GetType() {return m_acType;}
    private:
        int m_acType;

};

#endif // MENUGAME_H
