#ifndef PLAYER_H
#define PLAYER_H

#include "GameEntity.h"
#include "Trigger_Ruido.h"
#include "Fachada/Camera.h"
#include <iostream>


class PathFinding;
class SparseGraph;

#define MOV_SPEED 10.0f;

class Player_Ray;

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
        void CogerLlave(){llaves++;}
        void UsarLlave(){llaves--;}
        int  GetLlaves(){return llaves;}


        void MoverPlayer(Structs::TPosicion p1,Structs::TPosicion p2);
        bool HandleMessage(const Mensaje& msg){return true;}
        bool isPathObstructured(Structs::TPosicion destino);

        bool getMoving();
        void TriggerRuido();
        Trigger *getRuido(){return ruido;}

    protected:

    private:
        Structs::TPosicion toMousePosition;
        Structs::TPosicion toNextNodo;
        Structs::TPosicion toNextPosition;
        Structs::TPosicion mousePosition = {170,0,50};
        Structs::TPosicion quietoParado = {0,0,0};

        Trigger_Ruido* ruido;
        bool isMoving;
        int llaves = 0;

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
