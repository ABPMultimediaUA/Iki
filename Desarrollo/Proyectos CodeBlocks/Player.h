#ifndef PLAYER_H
#define PLAYER_H

#include "GameEntity.h"
#include "Fachada/Camera.h"
#include <iostream>

class PathFinding;
class SparseGraph;
class Player_Ray;
class Map;

#define MOV_SPEED 10.0f;

class Player : public GameEntity
{
    public:
        Player();
        ~Player();
        void inicializar_player(Map* m);
        void moverBody(Structs::TPosicion vec);
        void update(Camera* camara);
        bool isPlayer(){return true;};

        void CogerMunicion();
        bool isPathObstructured(Structs::TPosicion destino);
        void MoverPlayer(Structs::TPosicion p1,Structs::TPosicion p2);

    protected:

    private:
        bool moverse = false;
        Structs::TPosicion toMousePosition;
        Structs::TPosicion toNextNodo;
        Structs::TPosicion toNextPosition;
        Structs::TPosicion mousePosition = {170,0,50};
        Structs::TPosicion quietoParado = {0,0,0};

        Player_Ray* rayo;
        b2RayCastInput input;
        b2RayCastOutput	output;
        float distancia,angulo,avMovement,deltaTime;
        ///PATHFINDING
        Map* Mapa;
        SparseGraph* grafo;
        PathFinding* path;
        std::list<int> listaNodos;
        std::list<int>::iterator it;

};

#endif // PLAYER_H
