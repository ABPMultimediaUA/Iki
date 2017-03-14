#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "GameEntity.h"
#include "StateMachine.h"

#include "PatrolRoute.h"
#include "PatrolPoint.h"


class Enemy : public GameEntity
{

    private:
        std::vector<Enemy*> aliados;
        static int m_iNextValidID;

    public:
        Enemy(){}
        ~Enemy(){}
        virtual void inicializar_enemigo(Map* m)=0;
        virtual void update()=0;
        virtual StateMachine<Enemy>* GetFSM()const=0;
        void init(Map* m);
        void SetID(int val);
        int getID()const{return id;}
        int getTipo(){return tipo;}
        PatrolPoint* getPPatrulla(){return pRuta; }
        PatrolRoute* getPatrulla() {return ruta;  }
        void setPosition();
        f32 getTiempo() { return tiempoEnEstado;}
        void resetTime() { tiempoEnEstado = 0;}
        void patrullar();
        void vigilar();
        virtual bool HandleMessage(const Mensaje& msg)=0;
        void registrarEnemigo(Enemy* newE){
            aliados.push_back(newE);
        }
        //this method removes the entity from the list
        void borrarEnemigo(Enemy* enemigo){
           for (std::vector<Enemy*>::iterator it = aliados.begin() ; it != aliados.end(); ++it){
                if((*it)->getID() == enemigo->getID()){
                    aliados.erase(it);
                    break;
                }
            }
        }

    protected:

        int tipo,direccion,estadoVigilando;
        PatrolRoute* ruta;
        PatrolPoint* pRuta;
        float sospecha,angulo,avMovement,deltaTime;
        Structs::TPosicion posinit,posaux;
        Map* Mapa;
        f32 tiempoEnEstado;



};

#endif // ENEMIGO_H

