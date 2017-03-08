#include "World.h"
#include "Enemy.h"
#include "Guardia.h"
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

    std::vector<PatrolPoint*> puntos = mapa->getPatrullas();
    PatrolPoint* aux = mapa->getPatrullas().at(0);

    //for(std::vector<PatrolPoint*>::iterator it = mapa->getPatrullas().begin() ; it != mapa->getPatrullas().end(); ++it){
    for(int i = 1; i < puntos.size(); i++){

        if(puntos.at(i)->getEnemigo() == aux->getEnemigo()){
            aux->setNext(puntos.at(i));
            puntos.at(i)->setPrev(aux);
            if(aux->getID() == 1){
                rutas.push_back(new PatrolRoute(aux));
            }
        }
        else{
            if(aux->getNext0() == 0){
                aux->setNext(rutas.back()->getInicial());
                rutas.back()->getInicial()->setPrev(aux);
            }
            else{
                aux->setNext(aux->getPrev());
                rutas.back()->getInicial()->setPrev(rutas.back()->getInicial()->getNext());
            }
        }
        aux = puntos.at(i);

    }
}

void World::inicializar_mundo(){

    Structs::TPosicion pos (150,0,50);
    mapa->inicializar_mapa();

    crearRutas(mapa);
    for(int i = 0; i < rutas.size(); i++){
        switch(mapa->getTipos()[i]){
            case 1:
                enemigos.push_back(new Guardia(rutas[i]));
                break;
            default:
                break;
        }
        enemigos[i]->inicializar_enemigo();
    }
}

void World::update_mundo(){
    for(std::vector<Enemy*>::iterator it = enemigos.begin(); it != enemigos.end(); ++it){
        (*it)->update();
    }
    //mapa->update_mapa();
}
