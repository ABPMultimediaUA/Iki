#include "World.h"

#define VELITER 10
#define POSITER 10
#define TIMESTEP 1.0f / 250.0f

World::World()
{
    datos_nivel = new LevelData;

    gravity.x = 0.0f;
    gravity.y = 0.0f;
    phisics_world = new b2World(gravity);
}

World::~World()
{
    delete datos_nivel;
    delete mapa;
}

void World::Step(float DeltaTime){
    phisics_world->Step(DeltaTime * TIMESTEP, VELITER, POSITER);
}

void World::inicializar_mundo(){

    mapa = new Map();
    mapa->inicializar_mapa();
    /*std::vector<vector3df> posiciones = datos_nivel->getEnemPosiciones();
    for(std::vector<vector3df>::iterator it = posiciones.begin(); it != posiciones.end(); ++it){
        Enemy *enemigo = new Enemy;
        enemigo->inicializar_enemigo(1, smgr, *it);
        enemigos.push_back(enemigo);
    }*/
}

/*void World::update_mundo(){
    for(std::vector<Enemy*>::iterator it = enemigos.begin(); it != posiciones.end(); ++it){
        it->update_enem();
    }
    mapa->update_mapa();
}*/
