#include "World.h"

World::World()
{
    datos_nivel = new LevelData;
    mapa = new Map();
}

World::~World()
{
    delete datos_nivel;
    delete mapa;
}

void World::inicializar_mundo(){
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
