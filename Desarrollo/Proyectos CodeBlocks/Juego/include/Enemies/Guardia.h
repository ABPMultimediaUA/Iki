#ifndef GUARDIA_H
#define GUARDIA_H

#include "Enemy.h"
#include "StateMachine/Patrullar.h"
#include "StateMachine/Vigilar.h"
#include "StateMachine/Percibir.h"
#include "PatrolRoute.h"
#include "PatrolPoint.h"

class MeshSceneNode;

class Guardia : public Enemy
{
    private:
        bool ataquePreparado,solounaveh,atacando,solounpath,sonidoataque;
        float anguloAtaque, distanciaAtaque;
        b2Body *bodyAtaque;
        Structs::TPosicion vectorAtaque;
        Structs::TMedida medidaAtaque     = {10,0.5,0.5};
        Structs::TPosicion posicionAtaque = {0,0,0};
        //Structs::TColor colorAtaque       = {0,255,140,0};
        b2RayCastInput input2;
        b2RayCastOutput	output2;

    public:
        Guardia(int ID,PatrolRoute* rutita)
        {
            id=ID;
            //set up state machine
            G_stateMachine = new StateMachine<Enemy>(this);
            G_stateMachine->SetCurrentState(Patrullar::Instance());
            G_stateMachine->SetGlobalState(Percibir::Instance());
            ruta = rutita;
            posicion = rutita->getInicial()->getPunto();
            sospecha = 0.0;
            tiempoEnEstado = 0;
        }
        ~Guardia();
        StateMachine<Enemy>* GetFSM()const{return G_stateMachine;}
        void inicializar_enemigo(Map* m);
        bool HandleMessage(const Mensaje& msg){return G_stateMachine->HandleMessage(msg);}
        void perseguir();
        void ataque();
        void cargarAtaque();
        void ejecutarAtaque();
        void buscarProta();
        bool getAtacando(){return atacando;}
        bool isGuardia(){return true;}
        void setModeloVisible(bool b){modeloAtaque->setVisible(b);}


};

#endif // GUARDIA_H

