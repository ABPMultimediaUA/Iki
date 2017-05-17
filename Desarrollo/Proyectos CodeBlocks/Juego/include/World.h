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
        void crearRutas();
        void inicializar_mundo(int);
        void update_mundo();
        void crearEnemigos();
        void crearEnemigo(int tipo, int id, PatrolRoute* ruta);

        Map* getMapa(){return mapa;};
        std::vector<Enemy*> getEnemies(){return enemigos;}

        void cleanWorld();

    protected:

    private:

        Map* mapa;
        std::vector<PatrolRoute*> rutas;
        std::vector<Enemy*> enemigos;

};

#endif // WORLD_H
