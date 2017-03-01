#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "GameEntity.h"
#include "Structs.h"

class Enemy : public GameEntity
{
    public:
        Enemy(int&);
        ~Enemy();
        void inicializar_enemigo(int, Structs::TPosicion);

        int getEstado(){ return estado;}
        int getID()    { return id;}

    private:
        int estado, id; //0-> patrulla, 1-> sospechar, 2-> atacar, 3-> nsnc
        float sospecha;

        /*PatrolRoute ruta;
        PatrolPoint* pRuta;*/

};

#endif // ENEMIGO_H

