#ifndef MEDICO_H
#define MEDICO_H

#include "Enemy.h"
#include "StateMachine/StateMachine.h"
#include "StateMachine/Patrullar.h"
#include "PatrolRoute.h"
#include "PatrolPoint.h"

class Medico : public Enemy
{
    private:
        StateMachine<Enemy>* G_stateMachine;
        State<Enemy>* actualState;
        State<Enemy>* oldState;
        State<Enemy>* globalState;

    public:
        Medico(PatrolRoute* rutita)
        {
            //set up state machine
            G_stateMachine = new StateMachine<Enemy>(this);
            G_stateMachine->SetCurrentState(Patrullar::Instance());
            //G_stateMachine->SetGlobalState(Patrullar::Instance());
            ruta = rutita;
            posicion = rutita->getInicial()->getPunto();
            sospecha = 0.0;
            tiempoEnEstado = 0;
        }
        ~Medico(){delete G_stateMachine;}
        void update();
        StateMachine<Enemy>* GetFSM()const{return G_stateMachine;}
        void inicializar_enemigo();


};

#endif // MEDICO_H
