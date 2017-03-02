#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <GameEntity.h>


class PatrolRoute;

class Enemy : public GameEntity
{
    public:
        Enemy(){}
        ~Enemy(){}
        virtual void inicializar_enemigo()=0;
        virtual void update()=0;
        void SetID(int val);
        int getID()const{return id;}
        int getEstado(){ return estado;}
        int getTipo(){return tipo;}

    protected:
        int estado, id;
        int tipo;
        PatrolRoute* ruta;
        float sospecha;
    private:

        static int m_iNextValidID;



        /*PatrolRoute ruta;
        PatrolPoint* pRuta;*/

};

#endif // ENEMIGO_H

