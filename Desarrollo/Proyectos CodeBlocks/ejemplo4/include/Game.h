#ifndef GAME_H
#define GAME_H


class Game
{
    public:
        Game();
        virtual ~Game();

        //Update & Render
        int update();
        void render();

    protected:

    private:
};

#endif // GAME_H
