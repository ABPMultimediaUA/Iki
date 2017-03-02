#ifndef GUARDIA_H
#define GUARDIA_H

#include <Enemy.h>
#include "StateMachine/StateMachine.h"
#include "StateMachine/Patrullar.h"

class Guardia : public Enemy
{
    private:
        StateMachine<Guardia>* G_stateMachine;
        State<Guardia>* actualState;
        State<Guardia>* oldState;
        State<Guardia>* globalState;

    public:
        Guardia()
        {
            //set up state machine
            G_stateMachine = new StateMachine<Guardia>(this);
            G_stateMachine->SetCurrentState(Patrullar::Instance());
            G_stateMachine->SetGlobalState(Patrullar::Instance());
        }
        ~Guardia(){delete G_stateMachine;}
        void Update()
        {
            G_stateMachine->Update();
        }
        StateMachine<Guardia>* GetFSM()const{return G_stateMachine;}
        void inicializar_guardia(Structs::TPosicion);


};

#endif // GUARDIA_H

