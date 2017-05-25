#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <map>
#include <cassert>
#include <string>
#include "Structs.h"



class GameEntity;
class Enemy;
class World;
class PatrolRoute;


//provide easy access
#define EntityMgr EntityManager::Instance()



class EntityManager
{
private:
    typedef std::map<int, GameEntity*> EntityMap;
    std::vector<Enemy*> enemigos;
    std::vector<GameEntity*> entities;
    EntityMap entityMap;
    World* world;
    int nextID;

    EntityManager(){}
    EntityManager(const EntityManager&);
    EntityManager& operator=(const EntityManager&);

public:
    //es SINGLETON
    static EntityManager* Instance();
    void registrarEntity(GameEntity* newE);
    void borrarEntity(GameEntity* entity);
    GameEntity* getEntityByID(int id)const;
    Enemy* getGuardiaCerca(Structs::TPosicion posicion);
    std::vector<Enemy*> getEnemigos(){return enemigos;}
    std::vector<GameEntity*> getEntities(){ return entities;}
    void registrarWorld(World* w);
    void crearGuardia(PatrolRoute* ruta);
    void setNextValidID(int i){nextID=i;}
    bool hayGuardia();
    int getNextID(){return nextID;}

    void registrarEnemigo(Enemy* newEnemigo);
    void borrarEnemigo(Enemy* enemigo);

    void Clear();
    bool hayEnemyAtacando();
};







#endif
