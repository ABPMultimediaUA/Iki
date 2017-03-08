#ifndef PLAYER_RAY_H
#define PLAYER_RAY_H

#include "Structs.h"

class MeshSceneNode;

class Player_Ray
{
    public:
        Player_Ray();
        ~Player_Ray();

        void lanzar_rayo(Structs::TPosicion);

        void cogerBalas(){ balas++;}
        int getBalas(){ return balas;}

    protected:

    private:
        MeshSceneNode* modelo;
        int balas;

        Structs::TPosicion vec_distancia;

        b2RayCastInput input;
        b2RayCastOutput	output;
};

#endif // PLAYER_RAY_H