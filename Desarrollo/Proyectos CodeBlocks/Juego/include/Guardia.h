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
        StateMachine<Guardia>* G_stateMachine;
        State<Guardia>* actualState;
        State<Guardia>* oldState;
        State<Guardia>* globalState;

    public:
        Guardia(PatrolRoute* rutita)
        {
            //set up state machine
            G_stateMachine = new StateMachine<Guardia>(this);
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
        StateMachine<Guardia>* GetFSM()const{return G_stateMachine;}
        void inicializar_guardia(Structs::TPosicion);


};

#endif // GUARDIA_H

