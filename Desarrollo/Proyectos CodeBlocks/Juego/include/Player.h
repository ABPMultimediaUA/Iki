#ifndef PLAYER_H
#define PLAYER_H

#include "GameEntity.h"
#include "Fachada/Camera.h"
#include <iostream>

#define MOV_SPEED 10.0f;

class Player_Ray;

class Player : public GameEntity
{
    public:
        Player();
        ~Player();
        void inicializar_player();
        void moverBody(Structs::TPosicion vec);
        void update(Camera* camara);
        bool isPlayer(){return true;};

    protected:

    private:
        bool moverse = false;
        Structs::TPosicion toMousePosition = {170,0,50};

        Player_Ray* rayo;

};

#endif // PLAYER_H
