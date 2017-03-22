#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <map>
#include <cassert>
#include <string>
#include "Structs.h"


class GameEntity;
class Enemy;

//provide easy access
#define EntityMgr EntityManager::Instance()



class EntityManager
{
private:
    typedef std::map<int, GameEntity*> EntityMap;

    EntityMap entityMap;
    EntityManager(){}
    EntityManager(const EntityManager&);
    EntityManager& operator=(const EntityManager&);
    std::vector<Enemy*> guardias;
    std::vector<GameEntity*> entities;

public:
    //es SINGLETON
    static EntityManager* Instance();
    void registrarEntity(GameEntity* newE);
    void borrarEntity(GameEntity* entity);
    GameEntity* getEntityByID(int id)const;
    void registrarGuardia(Enemy* newGuardia);
    void borrarGuardia(Enemy* enemigo);
    Enemy* getGuardiaCerca(Structs::TPosicion posicion);

    std::vector<GameEntity*> getEntities(){ return entities; };
};







#endif
