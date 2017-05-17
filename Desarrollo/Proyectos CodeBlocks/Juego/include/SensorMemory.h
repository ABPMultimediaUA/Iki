#ifndef SENSOR_H
#define SENSOR_H

#include "MemoryRecord.h"
#include <map>
#include <list>

class Enemy;
class GameEntity;

class SensorMemory
{
private:

    typedef std::map<GameEntity*, MemoryRecord> MemoryMap;
    Enemy* enemigo;
    //this container is used to simulate memory of sensory events.Each record is updated
    //whenever the opponent is encountered.
    MemoryMap memoryMap;
    float memorySpan;
    //this methods checks to see if there is an existing record for pBot. If
    //not, a new MemoryRecord record is made and added to the memory map.
    void comprobarRecord(GameEntity* pBot);
public:

    SensorMemory(Enemy* e, float capacidadMemoria);
    void removeMemory(GameEntity* entidad);
    //this method is used to update the memory map whenever an opponent makes
    //a noise
    void updateSoundSource(GameEntity* ruidoso);
    //this method iterates through all the opponents in the game world and
    //updates the records of those that are in the owner's FOV
    void updateVision(GameEntity* cantoso);
    bool isEntityVisible(GameEntity* entidad)const;
    bool isEntityInFOV(GameEntity* entidad)const;
    Structs::TPosicion GetLastRecordedPositionOfEntity(GameEntity* entidad)const;
    float GetTimeEntityHasBeenVisible(GameEntity* entidad)const;
    float GetTimeSinceLastSensed(GameEntity* entidad)const;
    float GetTimeEntityHasBeenOutOfView(GameEntity* entidad)const;

    //this method returns a list of all the opponents that have had their
    //records updated within the last memorySpan seconds.
    std::list<GameEntity*> GetListOfRecentlySensedOpponents()const;
};

#endif // SENSOR_H
