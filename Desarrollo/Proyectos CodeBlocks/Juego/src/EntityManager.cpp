#include "EntityManager.h"
#include "GameEntity.h"



EntityManager* EntityManager::Instance()
{
  static EntityManager instance;

  return &instance;
}


GameEntity* EntityManager::getEntityByID(int id)const
{
  //find the entity
  EntityMap::const_iterator ent = entityMap.find(id);

  //assert that the entity is a member of the map
  assert ( (ent !=  entityMap.end()) && "<EntityManager::GetEntityFromID>: invalid ID");

  return ent->second;
}

void EntityManager::borrarEntity(GameEntity* pEntity)
{
  entityMap.erase(entityMap.find(pEntity->ID()));
}

//---------------------------- RegisterEntity ---------------------------------
//-----------------------------------------------------------------------------
void EntityManager::registrarEntity(GameEntity* NewEntity)
{
  entityMap.insert(std::make_pair(NewEntity->ID(), NewEntity));
}
