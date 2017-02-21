#ifndef WORLD_H
#define WORLD_H

#include "LevelData.h"
#include "Map.h"
#include "Enemy.h"

class World
{
    friend class Map;
    friend class Enemy;
    friend class MapComponent;

    public:
        static World* getInstance() {
            static World singleton;
            return &singleton;
        };
        virtual ~World();
        void inicializar_mundo();
        void update_mundo();

        void Step(float DeltaTime);
        Map* getMapa(){return mapa;};
        std::vector<Enemy*> getEnemies(){return enemigos;};
        b2World* getWorld(){return phisics_world;};


    protected:

    private:
        World();
        LevelData *datos_nivel;
        Map* mapa;
        std::vector<Enemy*> enemigos;

        b2World* phisics_world;
        b2Vec2 gravity;
};

#endif // WORLD_H
