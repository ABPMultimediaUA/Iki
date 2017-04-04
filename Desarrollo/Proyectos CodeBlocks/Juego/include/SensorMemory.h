#ifndef SENSOR_H
#define SENSOR_H

#include "MemoryRecord.h"

class Raven_SensoryMemory
{
private:
typedef std::map<Raven_Bot*, MemoryRecord> MemoryMap;
//the owner of this instance
Raven_Bot* m_pOwner;
//this container is used to simulate memory of sensory events. A MemoryRecord
//is created for each opponent in the environment. Each record is updated
//whenever the opponent is encountered. (when it is seen or heard)
MemoryMap m_MemoryMap;
//a bot has a memory span equivalent to this value. When a bot requests a
//list of all recently sensed opponents, this value is used to determine if
//the bot is able to remember an opponent or not.
double m_dMemorySpan;
//this methods checks to see if there is an existing record for pBot. If
//not, a new MemoryRecord record is made and added to the memory map.(Called
//by UpdateWithSoundSource & UpdateVision)
void MakeNewRecordIfNotAlreadyPresent(Raven_Bot* pBot);
public:
Raven_SensoryMemory(Raven_Bot* owner, double MemorySpan);
//this method is used to update the memory map whenever an opponent makes
//a noise
void UpdateWithSoundSource(Raven_Bot* pNoiseMaker);
//this method iterates through all the opponents in the game world and
//updates the records of those that are in the owner's FOV
void UpdateVision();
bool isOpponentShootable(Raven_Bot* pOpponent)const;
bool isOpponentWithinFOV(Raven_Bot* pOpponent)const;
Vector2D GetLastRecordedPositionOfOpponent(Raven_Bot* pOpponent)const;
double GetTimeOpponentHasBeenVisible(Raven_Bot* pOpponent)const;
double GetTimeSinceLastSensed(Raven_Bot* pOpponent)const;
double GetTimeOpponentHasBeenOutOfView(Raven_Bot* pOpponent)const;
//this method returns a list of all the opponents that have had their
//records updated within the last m_dMemorySpan seconds.
std::list<Raven_Bot*> GetListOfRecentlySensedOpponents()const;
};

#endif // SENSOR_H
