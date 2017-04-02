#ifndef GAME_H
#define GAME_H

class Scene;
class Menu;

class Game
{
    public:
        Game();
        ~Game();

        void start_game();

    protected:

    private:
        Scene* escena;
        Menu* menu;
};

#endif // GAME_H
