#ifndef PLAYER_H
#define PLAYER_H

#include "GameEntity.h"
#include <iostream>

class Player : public GameEntity
{
    public:
        Player();
        virtual ~Player();
        void inicializar_player(ISceneManager*);

    protected:

    private:

};

#endif // PLAYER_H
