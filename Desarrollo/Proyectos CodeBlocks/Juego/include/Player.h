#ifndef PLAYER_H
#define PLAYER_H

#include "GameEntity.h"
#include "Camera.h"
#include <iostream>

#define MOV_SPEED 10.0f;

class Player : public GameEntity
{
    public:
        Player();
        ~Player();
        void inicializar_player();
        void moverBody(Structs::TPosicion vec);
        void update(Camera* camara, Structs::TPosicion mousePosition);

    protected:

    private:
        Structs::TPosicion toMousePosition = {0,0,0};

};

#endif // PLAYER_H
