#ifndef DRON_H
#define DRON_H

#include "Enemy.h"
#include "StateMachine/StateMachine.h"
#include "StateMachine/Patrullar.h"
#include "PatrolRoute.h"
#include "PatrolPoint.h"

class Dron : public Enemy
{
    private:
        StateMachine<Enemy>* G_stateMachine;
        State<Enemy>* actualState;
        State<Enemy>* oldState;
        State<Enemy>* globalState;

    public:
        Dron(PatrolRoute* rutita)
        {
            //set up state machine
            G_stateMachine = new StateMachine<Enemy>(this);
            G_stateMachine->SetCurrentState(Patrullar::Instance());
           // G_stateMachine->SetGlobalState(Patrullar::Instance());
            ruta = rutita;
            posicion = rutita->getInicial()->getPunto();
            sospecha = 0.0;
            tiempoEnEstado = 0;
        }
        ~Dron(){delete G_stateMachine;}
        void update();
        StateMachine<Enemy>* GetFSM()const{return G_stateMachine;}
        void inicializar_enemigo(Map* m);


};

#endif // DRON_H
