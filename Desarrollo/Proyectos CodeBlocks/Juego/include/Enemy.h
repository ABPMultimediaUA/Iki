#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "GameEntity.h"
#include "Structs.h"

class PatrolRoute;

class Enemy : public GameEntity
{
    public:
        Enemy(PatrolRoute*);
        ~Enemy();
        void inicializar_enemigo(int);

        int getEstado(){ return estado;}
        int getID()    { return id;}

    private:
        int estado, id; //0-> patrulla, 1-> sospechar, 2-> atacar, 3-> nsnc
        float sospecha;
        PatrolRoute* ruta;

        /*PatrolRoute ruta;
        PatrolPoint* pRuta;*/

};

#endif // ENEMIGO_H

