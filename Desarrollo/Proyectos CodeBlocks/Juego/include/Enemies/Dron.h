#ifndef DRON_H
#define DRON_H

#include "Enemy.h"
#include "StateMachine/Patrullar.h"
#include "StateMachine/Percibir.h"
#include "PatrolRoute.h"
#include "PatrolPoint.h"

class Dron : public Enemy
{
    private:

    public:
        Dron(int ID,PatrolRoute* rutita)
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
        ~Dron();
        StateMachine<Enemy>* GetFSM()const{return G_stateMachine;}
        void inicializar_enemigo(Map* m);
        bool HandleMessage(const Mensaje& msg){return G_stateMachine->HandleMessage(msg);};
        bool isDron(){return true;}


};

#endif // DRON_H
