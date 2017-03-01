#ifndef WORLD_H
#define WORLD_H

#include "Map.h"

class Enemy;

class World
{
    public:
        World();
        virtual ~World();
        void inicializar_mundo();
        void update_mundo();

        Map* getMapa(){return mapa;};
        std::vector<Enemy*> getEnemies(){return enemigos;};

    protected:

    private:

        int num_enemigos;
        Map* mapa;
        std::vector<Enemy*> enemigos;

};

#endif // WORLD_H
