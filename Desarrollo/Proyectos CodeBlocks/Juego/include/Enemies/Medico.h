#ifndef MEDICO_H
#define MEDICO_H

#include "Enemy.h"
#include "StateMachine/Patrullar.h"
#include "StateMachine/Percibir.h"
#include "PatrolRoute.h"
#include "PatrolPoint.h"

class Medico : public Enemy
{
    private:
        Enemy* protegido;
        Structs::TPosicion toProtegido;
        Structs::TPosicion posHuida = {50,0,120};

    public:
        Medico(int ID,PatrolRoute* rutita)
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
        ~Medico();
        void pedirAyuda();
        void proteger();
        void huir();
        void curar();
        StateMachine<Enemy>* GetFSM()const{return G_stateMachine;}
        void inicializar_enemigo(Map* m);
        bool HandleMessage(const Mensaje& msg){return G_stateMachine->HandleMessage(msg);}
        void setProtegido(Enemy* e){protegido=e;}
        void setPosHuida(Structs::TPosicion p){posHuida=p;}
        Structs::TPosicion getPosHuida(){return posHuida;}
        bool isMedico(){return true;}


};

#endif // MEDICO_H
