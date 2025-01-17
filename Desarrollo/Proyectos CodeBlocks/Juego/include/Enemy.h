#ifndef ENEMY_H
#define ENEMY_H

#include "GameEntity.h"
#include "Enemies/StateMachine/StateMachine.h"

#include "PatrolRoute.h"
#include "PatrolPoint.h"
#include "Enemies/Path/PathEdge.h"
#include "SensorMemory.h"

class PathPlanner;

class Enemy : public GameEntity
{

    private:


    public:
        Enemy(){}
        virtual ~Enemy(){};
        ///VIRTUALS
        virtual void inicializar_enemigo(Map* m)=0;
        virtual void update();
        virtual StateMachine<Enemy>* GetFSM()const=0;
        virtual bool HandleMessage(const Mensaje& msg)=0;
        virtual bool isEnemy(){return true;}
        virtual bool isGuardia(){return false;}
        virtual bool isMedico(){return false;}
        virtual bool isDron(){return false;}
        ///GETTERS
        int getTipo(){return tipo;}
        float getSospecha(){return sospecha;}
        PatrolPoint* getPPatrulla(){return pRuta; }
        PatrolRoute* getPatrulla() {return ruta;  }
        f32 getTiempo() { return tiempoEnEstado;}
        float getDistanciaPlayer(){ return distanciaPlayer;}
        float FieldOfView(){return fieldOfView;}
        Structs::TPosicion getPosicionProta(){return posicionProta;}
        Structs::TPosicion getPosicionInteres(){return posicionInteres;}
        Structs::TPosicion getMirandoHacia(){return mirandoHacia;}
        //Enemy* getGuardiaMasCercano(){return (Enemy*)EntityMgr->getEntityByID(4);}
        Enemy* getGuardiaMasCercano(){return (Enemy*)EntityMgr->getGuardiaCerca(posicion);}
        float getTimePlayerHasBeenOutOfView();
        float getTimeSinceLastSensed();
        float getAngulo(){return angulo;}
        int getEstadoEntity(GameEntity* entity){return memory->getEstadoEntity(entity);}
        ///SETTERS
        void setPosition();
        Structs::TPosicion setPosicionInteres(Structs::TPosicion p){ posicionInteres = p;}
        void setPPatrulla(PatrolPoint* p){pRuta=p;}
        ///ESTADOS
        void patrullar();
        void vigilar();
        void escanear();
        void escuchar();
        void muerto();
        void volverALaPatrulla();
        void investigar();
        ///METODOS
        void actualizarMemoriaVision(GameEntity*);
        void actualizarMemoriaOido(GameEntity*);
        void init(Map* m);
        void resetTime() { tiempoEnEstado = 0;}
        void restarSospecha(float s){sospecha-=s;}
        void resetSospecha() {sospecha=0; questionMark->setVisible(false);}
        void crearBody();
        void crearPath(Structs::TPosicion destino);
        bool isPathObstructured(Structs::TPosicion destino);
        bool isEnemySeeing(Structs::TPosicion destino);
        bool canWalkBetween(Structs::TPosicion desde, Structs::TPosicion hasta);
        void moverBody(Structs::TPosicion vec);
        void MoverEnemigo(Structs::TPosicion p);
        void andarPath(float velocidad,Structs::TPosicion posFinal);
        void cambiarColor(Structs::TColor c);
        void calcularAngulo(Structs::TPosicion p1);
        void girarVista(float giro,int posV);
        void quitarVida();
        bool hayGuardias();
        bool colisionPuertas(Structs::TPosicion destino);
        void borrarMemoria();
        void activeHoloScan(bool b){holoScan->setVisible(b);}
        void activeAtaque(bool b){modeloAtaque->setVisible(b);}
        void scanTimerToZero(){scanAngle=0;scanT=0;}
        void matar();
        void subirSospecha(float);
        void showExcMark(bool);
        void subirSospechaValorConcreto(float);

    protected:

        MeshSceneNode* holoScan;
        MeshSceneNode* excMark;
        MeshSceneNode* questionMark;
        MeshSceneNode* modeloAtaque;
        int tipo,direccion,posVigilando, bateria;
        PatrolRoute* ruta;
        PatrolPoint* pRuta;
        float sospecha,angulo,avMovement,deltaTime,distanciaPlayer;
        Structs::TPosicion posinit,posaux;
        Map* Mapa;
        f32 tiempoEnEstado, time_since_hitted, scanT, sTime, bateriaT;
        StateMachine<Enemy>* G_stateMachine;
        Structs::TPosicion mirandoHacia;
        Structs::TPosicion vectorProta;
        Structs::TPosicion posicionProta;
        Structs::TPosicion posicionInteres;
        Structs::TPosicion posBody;
        float scanAngle;
        State<Enemy>* actualState;
        State<Enemy>* oldState;
        State<Enemy>* globalState;
        b2RayCastInput input;
        b2RayCastOutput	output;
        b2RayCastOutput	output2;
        const float DegToRad = PI/180;
        bool guessing = false;
        float fieldOfView;

        ///PATHPLANNING
        SparseGraph* grafo;
        //PathPlanner<Enemy>* path;
        PathPlanner* path;
        std::list<PathEdge> listaEjes;
        std::list<PathEdge>::iterator it;
        Structs::TPosicion toProtaPosition;
        Structs::TPosicion toNextNodo;
        Structs::TPosicion toNextPosition;
        Structs::TPosicion toPosicionFinal;
        Structs::TPosicion quietoParado = {0,0,0};

        ///SENSORMEMORY
        SensorMemory* memory;


};

#endif // ENEMIGO_H

