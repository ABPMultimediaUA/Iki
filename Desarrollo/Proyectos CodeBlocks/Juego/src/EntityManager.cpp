#include "EntityManager.h"
#include "GameEntity.h"
#include "Enemy.h"
#include "World.h"



EntityManager* EntityManager::Instance()
{
  static EntityManager instance;

  return &instance;
}


GameEntity* EntityManager::getEntityByID(int id)const
{
  EntityMap::const_iterator ent = entityMap.find(id);

  assert ( (ent !=  entityMap.end()) && "<EntityManager::GetEntityFromID>: invalid ID");

  return ent->second;
}

void EntityManager::borrarEntity(GameEntity* pEntity)
{
  entityMap.erase(entityMap.find(pEntity->ID()));
}

void EntityManager::registrarEntity(GameEntity* NewEntity)
{
  entityMap.insert(std::make_pair(NewEntity->ID(), NewEntity));
  entities.push_back(NewEntity);
}
void EntityManager::registrarEnemigo(Enemy* newEnemigo){
    enemigos.push_back(newEnemigo);
    }
void EntityManager::borrarEnemigo(Enemy* enemigo){
       for (std::vector<Enemy*>::iterator it = enemigos.begin() ; it != enemigos.end(); ++it){
            if((*it)->ID() == enemigo->ID()){
                enemigos.erase(it);
                break;
            }
        }
    }
Enemy* EntityManager::getGuardiaCerca(Structs::TPosicion posicion){
    Enemy* aux;
    float distanciaAUX;
    for (std::vector<Enemy*>::iterator it = enemigos.begin() ; it != enemigos.end(); ++it){
        if((*it)->isGuardia()){
            aux = (*it);
            distanciaAUX = aux->getPosition().Distance(posicion);
            break;
            }
        }
    for (std::vector<Enemy*>::iterator it = enemigos.begin() ; it != enemigos.end(); ++it){
        if((*it)->ID() != aux->ID() && (*it)->isGuardia()){
            if(posicion.Distance((*it)->getPosition()) < distanciaAUX ){
                distanciaAUX=posicion.Distance((*it)->getPosition());
                aux=(*it);
            }
        }
    }
    return aux;
}
bool EntityManager::hayGuardia(){
    for (std::vector<Enemy*>::iterator it = enemigos.begin() ; it != enemigos.end(); ++it){
        if((*it)->isGuardia()){
            return true;
            }
        }
    return false;
}
void EntityManager::crearGuardia(PatrolRoute* ruta){
    world->crearEnemigo(1,nextID,ruta);
    nextID = nextID + 1;
}
void EntityManager::registrarWorld(World* w){
    world = w;
    nextID = world->getEnemies().back()->ID() + 1;
}

void EntityManager::Clear(){
    std::vector<GameEntity*>::iterator curTrg;
    for (curTrg = entities.begin(); curTrg != entities.end(); ++curTrg)
    {
        delete *curTrg;
    }

    entities.clear();
    enemigos.clear();
    entityMap.clear();
    nextID = 1;
}
