#ifndef PLAYER_H
#define PLAYER_H

#include "GameEntity.h"
#include "Trigger_Ruido.h"
#include "Fachada/Camera.h"
#include "Fachada/Animaciones.h"
#include <iostream>

class PathFinding;
class PathPlanner;
class SparseGraph;

#include "Player_Ray.h"

#define MOV_SPEED 10.0f;

class Player : public GameEntity{
    public:
        Player();
        ~Player();
        void inicializar_player(Map* m, int);
        void moverBody(Structs::TPosicion vec);
        void update(Camera* camara);
        bool isPlayer(){return true;};

        void CogerMunicion();
        void CogerVida();
        void CogerLlave();
        void UsarLlave();
        void NecesitoLlave();
        int  GetLlaves(){return llaves;}

        void UpdateRayo(Camera* camara);
        void UpdateAtaque();
        void UpdateMov(Camera* camara);

        void sonidosMovimiento();
        void MoverPlayer(Structs::TPosicion p1,Structs::TPosicion p2);
        bool HandleMessage(const Mensaje& msg){return true;}
        bool isPathObstructured(Structs::TPosicion destino);
        bool canWalkBetween(Structs::TPosicion,Structs::TPosicion);

        int getSpeed(){ return speed; }
        int getMunicion(){ return rayo->getBalas();}
        bool getMoving();
        void TriggerRuido();
        Trigger *getRuido(){return ruido;}

        bool imSeeingThisEnemy(Enemy*);
        void calcularMirarHacia(Structs::TPosicion);

        void calcularAngulo(Structs::TPosicion p1);

        void subirVelocidad();
        void comprobarVelocidad();

        bool isNivelFinished(){ return nivel_acabado; }
        bool wantReintentar() { return reintentar; }
        void setNivelFinished(bool holi){ nivel_acabado = holi; }

        bool mostrarMensajePalanca();
        void desmostrarMensajePalanca();

        void runAnimacion(int);
        void meshQuietoParado();

    protected:

    private:

        Structs::TPosicion toMousePosition;
        Structs::TPosicion toNextNodo;
        Structs::TPosicion toNextPosition;
        Structs::TPosicion mousePosition = {170,0,50};
        Structs::TPosicion quietoParado = {0,0,0};
        Structs::TPosicion mirarHacia = {0,0,0};

        MeshSceneNode* puntero;

        Animaciones *animacionAndar;
        Animaciones *animacionSigilo;
        std::vector <IAnimatedMeshSceneNode*> modelos;
        std::vector <IAnimatedMeshSceneNode*> modelosSigilo;

        Trigger_Ruido* ruido;
        bool isMoving, moverse, nivel_acabado, reintentar;
        int speed;
        float velocidad;
        int llaves = 0, j=0,h=0;

        Player_Ray* rayo;
        b2RayCastInput input;
        b2RayCastOutput	output;

        b2RayCastInput input2;
        b2RayCastOutput	output2;

        f32 tiempo_con_mas_speed;

        float distancia,angulo,avMovement,deltaTime,tiempoAnimacion,tiempoJuego,intervalo;
        ///PATHFINDING
        Map* Mapa;
        SparseGraph* grafo;
        PathFinding* path;
        std::list<int> listaNodos;
        std::list<int>::iterator it;

        ///PATHPLANNING
        PathPlanner* path2;
        std::list<PathEdge> listaEjes;
        std::list<PathEdge>::iterator it2;
};

#endif // PLAYER_H


