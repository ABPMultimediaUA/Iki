#ifndef GUARDIA_H
#define GUARDIA_H

#include "Enemy.h"
#include "StateMachine/StateMachine.h"
#include "StateMachine/Patrullar.h"
#include "PatrolRoute.h"
#include "PatrolPoint.h"

class Guardia : public Enemy
{
    private:
        StateMachine<Enemy>* G_stateMachine;
        State<Enemy>* actualState;
        State<Enemy>* oldState;
        State<Enemy>* globalState;

    public:
        Guardia(PatrolRoute* rutita)
        {
            //set up state machine
            G_stateMachine = new StateMachine<Enemy>(this);
            G_stateMachine->SetCurrentState(Patrullar::Instance());
            G_stateMachine->SetGlobalState(Patrullar::Instance());
            ruta = rutita;
            posicion = rutita->getInicial()->getPunto();
            estado = 0;
            sospecha = 0.0;
        }
        ~Guardia(){delete G_stateMachine;}
        void update()
        {
            G_stateMachine->Update();
        }
        StateMachine<Enemy>* GetFSM()const{return G_stateMachine;}
        void inicializar_enemigo();


};

#endif // GUARDIA_H

