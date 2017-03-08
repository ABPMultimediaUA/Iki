#ifndef PLAYER_H
#define PLAYER_H

#include "GameEntity.h"
#include "Fachada/Camera.h"
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
        bool isPlayer(){return true;};

        void CogerMunicion();

    protected:

    private:
        Structs::TPosicion toMousePosition = {170,0,50};

};

#endif // PLAYER_H
