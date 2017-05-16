#include "World.h"
#include "Enemy.h"
#include "Enemies/Guardia.h"
#include "PatrolRoute.h"
#include "Enemies/Medico.h"
#include "Enemies/Dron.h"
#include "EntityManager.h"

World::World()
{
    mapa = new Map();
}

World::~World()
{
    delete mapa;
    for(std::vector<Enemy*>::iterator it = enemigos.begin(); it != enemigos.end(); ++it){
        delete (*it);
    }

}

void World::crearRutas(){ ///REVISAR SI ES POSIBLE OPTIMIZAR


    std::vector<PatrolPoint*> puntos = mapa->getPatrullas();
    PatrolPoint* aux = mapa->getPatrullas().at(0);

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
                aux->setNext(rutas[rutas.size()-1]->getInicial());
                rutas[rutas.size()-1]->getInicial()->setPrev(aux);
            }
            else{
                aux->setNext(aux->getPrev());
                rutas[rutas.size()-1]->getInicial()->setPrev(rutas[rutas.size()-1]->getInicial()->getNext());
            }
        }
        aux = puntos.at(i);

        if(puntos.size()-1 == i){
            if(aux->getNext0() == 0){
                aux->setNext(rutas[rutas.size()-1]->getInicial());
                rutas[rutas.size()-1]->getInicial()->setPrev(aux);
            }
            else{
                aux->setNext(aux->getPrev());
                rutas[rutas.size()-1]->getInicial()->setPrev(rutas[rutas.size()-1]->getInicial()->getNext());
            }
        }

    }
}

void World::inicializar_mundo(){
    //inicializar mapa
    mapa->inicializar_mapa();
    //crear e inicializar rutas
    crearRutas();
    //crear e inicializar enemigos
    crearEnemigos();
    //registro el world
    EntityMgr->registrarWorld(this);
}
void World::crearEnemigos(){
    for(int i = 0; i < rutas.size(); i++){
        switch(mapa->getTiposEnemigos()[i]){
            //Les asigno el ID i+1 porque el player sera el 0
            case 1:
                crearEnemigo(1,i+1,rutas[i]);
                break;
            case 2:
                crearEnemigo(2,i+1,rutas[i]);
                break;
            case 3:
                crearEnemigo(3,i+1,rutas[i]);
                break;
            default:
                break;
        }
    }
}
void World::crearEnemigo(int tipo, int id, PatrolRoute* ruta){
    switch(tipo){
        case 1:
            enemigos.push_back(new Guardia(id,ruta));
            std::cout<<"creo guardia"<<id<<std::endl;
            break;
        case 2:
            enemigos.push_back(new Medico(id,ruta));
            std::cout<<"creo medico"<<id<<std::endl;
            break;
        case 3:
            enemigos.push_back(new Dron(id,ruta));
            std::cout<<"creo dron"<<id<<std::endl;
            break;

    }
    enemigos.back()->inicializar_enemigo(mapa);
}
void World::update_mundo(){
    for(int i = 0; i < enemigos.size(); i++){
        enemigos[i]->update();
    }
}
