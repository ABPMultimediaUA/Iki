#include "World.h"
#include "Enemy.h"
#include "PatrolRoute.h"

World::World()
{
    mapa = new Map;
}

World::~World()
{
    delete mapa;
}

void World::crearRutas(Map* mapa){

    int enem = 0;

    //std::vector<PatrolPoint*> puntos = mapa->getPatrullas();
    PatrolPoint* aux = mapa->getPatrullas().at(0);

    for(std::vector<PatrolPoint*>::iterator it = mapa->getPatrullas().begin() ; it != mapa->getPatrullas().end(); ++it){
    //for(int i = 0; i < puntos.size(); i++){

        if(aux != *it && (*it)->getEnemigo() == aux->getEnemigo()){
            aux->setNext(*it);
            (*it)->setPrev(aux);
            if(aux->getID() == 1){
                rutas.push_back(new PatrolRoute(aux));
            }
            aux = *it;
        }
    }
}

void World::inicializar_mundo(){

    Structs::TPosicion pos = {150,0,50};
    mapa->inicializar_mapa();
    crearRutas(mapa);
    for(int i = 0; i < rutas.size(); i++){
        enemigos.push_back(new Enemy(rutas.at(i)));
        enemigos.at(i)->inicializar_enemigo(1);
    }

    //Enemy* pruebaEnemigo = new Enemy(num_enemigos);
    //pruebaEnemigo->inicializar_enemigo(1, pos);
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
