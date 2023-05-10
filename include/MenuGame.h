#ifndef MENUGAME_H
#define MENUGAME_H
#include "BaseObject.h"
#include "TextObject.h"

class MenuGame : public TextObject
{
    public:
        MenuGame();
        ~MenuGame();
        bool LoadButton(std::string path,SDL_Renderer* screen);
        bool IsChosen(SDL_Event event);
        void HandlePlayButton(SDL_Event event, SDL_Renderer* screen, bool &InMenu, TTF_Font *font);
        void HandleQuitButton(SDL_Event event, SDL_Renderer* screen, bool &QuitMenu, TTF_Font *font);
        void HandleRetryButton(SDL_Event event, SDL_Renderer* screen,
                          vector<Enemy*>&Enemy_List,Player &spaceship,
                          vector<Bullet*> &Bullet_List, bool &quit);



};

#endif // MENUGAME_H
