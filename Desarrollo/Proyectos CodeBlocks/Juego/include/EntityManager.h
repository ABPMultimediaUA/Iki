#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#pragma warning (disable:4786)
//------------------------------------------------------------------------
//
//  Name:   EntityManager.h
//
//  Desc:   Singleton class to handle the  management of Entities.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <map>
#include <cassert>
#include <string>


class GameEntity;

//provide easy access
#define EntityMgr EntityManager::Instance()



class EntityManager
{
private:
    typedef std::map<int, GameEntity*> EntityMap;

    //to facilitate quick lookup the entities are stored in a std::map, in which
    //pointers to entities are cross referenced by their identifying number
    EntityMap entityMap;

    EntityManager(){}
    //copy ctor and assignment should be private
    EntityManager(const EntityManager&);
    EntityManager& operator=(const EntityManager&);

public:
    //es SINGLETON
    static EntityManager* Instance();
    void registrarEntity(GameEntity* newE);
    void borrarEntity(GameEntity* entity);
    GameEntity* getEntityByID(int id)const;
};







#endif
