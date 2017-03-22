#include "World.h"
#include "Enemy.h"
#include "Guardia.h"
#include "PatrolRoute.h"
#include "Medico.h"
#include "Dron.h"
#include "EntityManager.h"

World::World()
{
    mapa = new Map();
}

World::~World()
{
    delete mapa;
}

void World::crearRutas(Map* mapa){ ///REVISAR SI ES POSIBLE OPTIMIZAR

    int enem = 0;

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
    crearRutas(mapa);
    //crear e inicializar enemigos
    for(int i = 0; i < rutas.size(); i++){
        switch(mapa->getTipos()[i]){
            case 1:
                enemigos.push_back(new Guardia(i+1,rutas[i]));
                break;
            case 2:
                enemigos.push_back(new Medico(i+1,rutas[i]));
                break;
            case 3:
                enemigos.push_back(new Dron(i+1,rutas[i]));
                break;
            default:
                break;
        }
        enemigos[i]->inicializar_enemigo(mapa);
        //EntityMgr->registrarEntity(enemigos[i]);
    }
}

void World::update_mundo(){
    for(std::vector<Enemy*>::iterator it = enemigos.begin(); it != enemigos.end(); ++it){
        (*it)->update();
    }
    //mapa->update_mapa();
}
