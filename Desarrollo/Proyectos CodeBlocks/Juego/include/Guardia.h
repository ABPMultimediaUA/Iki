#ifndef GUARDIA_H
#define GUARDIA_H

#include "Enemy.h"
#include "StateMachine/Patrullar.h"
#include "PatrolRoute.h"
#include "PatrolPoint.h"

class Guardia : public Enemy
{
    private:

    public:
        Guardia(int ID,PatrolRoute* rutita)
        {
            id=ID;
            //set up state machine
            G_stateMachine = new StateMachine<Enemy>(this);
            G_stateMachine->SetCurrentState(Patrullar::Instance());
            //G_stateMachine->SetGlobalState(Patrullar::Instance());
            ruta = rutita;
            posicion = rutita->getInicial()->getPunto();
            sospecha = 0.0;
            tiempoEnEstado = 0;
        }
        ~Guardia(){delete G_stateMachine;}
        StateMachine<Enemy>* GetFSM()const{return G_stateMachine;}
        void inicializar_enemigo(Map* m);
        bool HandleMessage(const Mensaje& msg){return G_stateMachine->HandleMessage(msg);};
        void investigar();


};

#endif // GUARDIA_H

