#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "GameEntity.h"

class Enemy : public GameEntity
{
    public:
        Enemy();
        ~Enemy();
        void inicializar_enemigo(int, ISceneManager*, vector3df);

    private:
        int estado; //0-> patrulla, 1-> sospechar, 2-> atacar, 3-> nsnc

};

#endif // ENEMIGO_H

