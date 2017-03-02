#ifndef WORLD_H
#define WORLD_H

#include "Map.h"

class Enemy;
class PatrolRoute;

class World
{
    public:
        World();
        virtual ~World();
        void crearRutas(Map*);
        void inicializar_mundo();
        void update_mundo();

        Map* getMapa(){return mapa;};
        std::vector<Enemy*> getEnemies(){return enemigos;};

    protected:

    private:

        Map* mapa;
        std::vector<PatrolRoute*> rutas;
        std::vector<Enemy*> enemigos;

};

#endif // WORLD_H
