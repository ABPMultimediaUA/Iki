#include "World.h"
#include "Enemy.h"

World::World()
{
    num_enemigos = 0;
    mapa = new Map;
}

World::~World()
{
    delete mapa;
}

void World::inicializar_mundo(){

    Structs::TPosicion pos = {150,0,50};
    mapa->inicializar_mapa();
    Enemy* pruebaEnemigo = new Enemy(num_enemigos);
    pruebaEnemigo->inicializar_enemigo(1, pos);
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
