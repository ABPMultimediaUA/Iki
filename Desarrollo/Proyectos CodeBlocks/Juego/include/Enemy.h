#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <GameEntity.h>


class Guardia;
class PatrolRoute;

class Enemy : public GameEntity
{
    public:
        Enemy(PatrolRoute*);
        ~Enemy();
        void inicializar_enemigo(int);
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
        int estado;
        float sospecha;
        PatrolRoute* ruta;


        /*PatrolRoute ruta;
        PatrolPoint* pRuta;*/

};

#endif // ENEMIGO_H

