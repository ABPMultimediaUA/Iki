#ifndef SENSOR_H
#define SENSOR_H

#include "MemoryRecord.h"
#include "GameEntity.h"

class SensorMemory
{
private:

    typedef std::map<GameEntity*, MemoryRecord> MemoryMap;
    GameEntity* enemigo;
    //this container is used to simulate memory of sensory events.Each record is updated
    //whenever the opponent is encountered.
    MemoryMap memoryMap;
    double memorySpan;
    //this methods checks to see if there is an existing record for pBot. If
    //not, a new MemoryRecord record is made and added to the memory map.
    void MakeNewRecordIfNotAlreadyPresent(GameEntity* pBot);
public:

    SensorMemory(GameEntity* e, double capacidadMemoria);
    //this method is used to update the memory map whenever an opponent makes
    //a noise
    void updateSoundSource(GameEntity* ruidoso);
    //this method iterates through all the opponents in the game world and
    //updates the records of those that are in the owner's FOV
    void updateVision();
    bool isPlayerVisible(GameEntity* player)const;
    bool isPlayerInFOV(GameEntity* player)const;
    Structs::TPosicion GetLastRecordedPositionOfPlayer(GameEntity* player)const;
    double GetTimePlayerHasBeenVisible(GameEntity* player)const;
    double GetTimeSinceLastSensed(GameEntity* player)const;
    double GetTimePlayerHasBeenOutOfView(GameEntity* player)const;

    //this method returns a list of all the opponents that have had their
    //records updated within the last memorySpan seconds.
    std::list<GameEntity*> GetListOfRecentlySensedOpponents()const;
};

#endif // SENSOR_H
