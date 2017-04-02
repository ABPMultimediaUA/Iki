#include "EntityManager.h"
#include "GameEntity.h"
#include "Enemy.h"



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
void EntityManager::registrarGuardia(Enemy* newGuardia){
    guardias.push_back(newGuardia);
    }
void EntityManager::borrarGuardia(Enemy* enemigo){
       for (std::vector<Enemy*>::iterator it = guardias.begin() ; it != guardias.end(); ++it){
            if((*it)->ID() == enemigo->ID()){
                guardias.erase(it);
                break;
            }
        }
    }
Enemy* EntityManager::getGuardiaCerca(Structs::TPosicion posicion){
    Enemy* aux = guardias.at(0);
    float distanciaAUX = aux->getPosition().Distance(posicion);
    for (std::vector<Enemy*>::iterator it = guardias.begin() ; it != guardias.end(); ++it){
        if((*it)->ID() != aux->ID()){
            if(posicion.Distance((*it)->getPosition()) < distanciaAUX ){
                distanciaAUX=posicion.Distance((*it)->getPosition());
                aux=(*it);
            }
        }
    }
    return aux;
}
