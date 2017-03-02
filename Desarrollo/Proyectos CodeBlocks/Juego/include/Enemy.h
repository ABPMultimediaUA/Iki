#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <GameEntity.h>

class Guardia;
class Enemy : public GameEntity
{
    public:

        Enemy(){}
        virtual ~Enemy(){}

        virtual void update()=0;
        void SetID(int val);
        int getID()const{return id;}
        int getEstado(){ return estado;}
        int getTipo(){return tipo;}

    protected:
        int estado, id;
        int tipo;
    private:
        static int m_iNextValidID;
        Guardia* guardia;

        /*PatrolRoute ruta;
        PatrolPoint* pRuta;*/

};

#endif // ENEMIGO_H

