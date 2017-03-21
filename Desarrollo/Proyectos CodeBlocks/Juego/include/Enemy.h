#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "GameEntity.h"
#include "StateMachine.h"

#include "PatrolRoute.h"
#include "PatrolPoint.h"
#include "Path/PathEdge.h"


class PathPlanner;


class Enemy : public GameEntity
{

    private:
        static int m_iNextValidID;


    public:
        Enemy(){}
        ~Enemy(){}
        ///VIRTUALS
        virtual void inicializar_enemigo(Map* m)=0;
        virtual void update();
        virtual StateMachine<Enemy>* GetFSM()const=0;
        virtual bool HandleMessage(const Mensaje& msg)=0;
        ///GETTERS
        int getTipo(){return tipo;}
        PatrolPoint* getPPatrulla(){return pRuta; }
        PatrolRoute* getPatrulla() {return ruta;  }
        f32 getTiempo() { return tiempoEnEstado;}
        float getDistanciaPlayer(){ return distanciaPlayer;}
        Structs::TPosicion getPosicionProta(){return posicionProta;}
        Structs::TPosicion getPosicionInteres(){return posicionInteres;}
        Enemy* getGuardiaMasCercano(){return (Enemy*)EntityMgr->getEntityByID(4);}
        //Enemy* getGuardiaMasCercano(){return EntityMgr->getGuardiaCerca(posicion);}
        ///SETTERS
        void SetID(int val);
        void setPosition();
        Structs::TPosicion setPosicionInteres(Structs::TPosicion p){ posicionInteres = p;}
        ///ESTADOS
        void patrullar();
        void vigilar();
        ///METODOS
        void init(Map* m);
        void resetTime() { tiempoEnEstado = 0;}
        void crearBody();
        void crearPath(Structs::TPosicion destino);
        bool isPathObstructured(Structs::TPosicion destino);
        bool canWalkBetween(Structs::TPosicion desde, Structs::TPosicion hasta);


    protected:

        int tipo,direccion,estadoVigilando;
        PatrolRoute* ruta;
        PatrolPoint* pRuta;
        float sospecha,angulo,avMovement,deltaTime,distanciaPlayer;
        Structs::TPosicion posinit,posaux;
        Map* Mapa;
        f32 tiempoEnEstado;
        StateMachine<Enemy>* G_stateMachine;
        Structs::TPosicion posicionProta;
        Structs::TPosicion posicionInteres;
        State<Enemy>* actualState;
        State<Enemy>* oldState;
        State<Enemy>* globalState;
        b2RayCastInput input;
        b2RayCastOutput	output;

        ///PATHPLANNING
        SparseGraph* grafo;
        PathPlanner* path;
        std::list<PathEdge> listaEjes;
        std::list<PathEdge>::iterator it;
        Structs::TPosicion toProtaPosition;
        Structs::TPosicion toNextNodo;
        Structs::TPosicion toNextPosition;
        Structs::TPosicion quietoParado = {0,0,0};



};

#endif // ENEMIGO_H

