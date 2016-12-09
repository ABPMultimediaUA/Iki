#ifndef WORLD_H
#define WORLD_H

#include "LevelData.h"
#include "Map.h"
#include "Enemy.h"

class World
{
    public:
        World();
        virtual ~World();
        void inicializar_mundo();
        void update_mundo();

    protected:

    private:
        LevelData *datos_nivel;
        Map *mapa;
        std::vector<Enemy*> enemigos;
};

#endif // WORLD_H
