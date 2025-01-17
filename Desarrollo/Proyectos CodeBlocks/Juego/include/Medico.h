#ifndef MEDICO_H
#define MEDICO_H

#include "Enemy.h"
#include "StateMachine/Patrullar.h"
#include "PatrolRoute.h"
#include "PatrolPoint.h"

class Medico : public Enemy
{
    private:
        Enemy* protegido;
        Structs::TPosicion toProtegido;

    public:
        Medico(int ID,PatrolRoute* rutita)
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
        ~Medico(){delete G_stateMachine;}
        void pedirAyuda();
        void proteger();
        StateMachine<Enemy>* GetFSM()const{return G_stateMachine;}
        void inicializar_enemigo(Map* m);
        bool HandleMessage(const Mensaje& msg){return G_stateMachine->HandleMessage(msg);}
        void setProtegido(Enemy* e){protegido=e;}


};

#endif // MEDICO_H
