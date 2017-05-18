#include "SensorMemory.h"
#include "Fachada/GraphicsFacade.h"
#include "PhisicsWorld.h"
#include "EntityManager.h"
#include "Enemy.h"

 SensorMemory:: SensorMemory(Enemy* owner,float mSpan):enemigo(owner),memorySpan(mSpan)
{}

void SensorMemory::comprobarRecord(GameEntity* entidad)
{
    //Comprueba si la entidad existe en memoria y sino se crea un nuevo recuerdo
    if (memoryMap.find(entidad) == memoryMap.end())
    {
        memoryMap[entidad] = MemoryRecord();
    }
}

void SensorMemory::removeMemory(GameEntity* entidad)
{
    MemoryMap::iterator record = memoryMap.find(entidad);
    if (record != memoryMap.end())
    {
        memoryMap.erase(record);
    }
}

//----------------------- UpdateWithSoundSource -------------------------------
//
// this updates the record for an individual opponent. Note, there is no need to
// test if the opponent is within the FOV because that test will be done when the
// UpdateVision method is called
//-----------------------------------------------------------------------------
void SensorMemory::updateSoundSource(GameEntity* ruidoso)
{
  if (enemigo != ruidoso)
  {
    comprobarRecord(ruidoso);

    MemoryRecord& info = memoryMap[ruidoso];

    info.ultimaPosicion = ruidoso->getPosition();
    info.ultimaPercepcion = PhisicsWorld::getInstance()->getTimeStamp()/1000;
    /*
    //test if there is LOS between bots
    //if (enemigo->GetWorld()->isLOSOkay(enemigo->Pos(), ruidoso->Pos()))
    if (enemigo->canWalkBetween(enemigo->getPosition(), ruidoso->getPosition()))
    {
      info.sinObstaculos = true;
     //record the position of the bot
      info.ultimaPosicion = ruidoso->getPosition();
    }
    else
    {
      info.sinObstaculos = false;
    }

    //record the time it was sensed
    info.ultimaPercepcion = PhisicsWorld::getInstance()->getTimeStamp()/1000;
    */
  }
}

void SensorMemory::updateVision(GameEntity* cantoso){
    comprobarRecord(cantoso);
    //get a reference to this bot's data
    MemoryRecord& info = memoryMap[cantoso];

    info.ultimaPercepcion = PhisicsWorld::getInstance()->getTimeStamp()/1000;
    info.ultimaPosicion = cantoso->getPosition();
    info.ultimaVista = PhisicsWorld::getInstance()->getTimeStamp()/1000;

    if (info.entraEnFOV == false)
    {
        info.entraEnFOV  = true;
        info.primeraVista = info.ultimaPercepcion;
    }
    if(info.estado == todoCorrecto){
        if(cantoso->isEnemy() && cantoso->getVida() == 0)
            info.estado = muerto;
        else if(cantoso->isPlayer())
            info.estado = sospechoso;
        else if(cantoso->isTrigger() && cantoso->isPuertaAbierta() )
                info.estado = abierta;

    }
    else{
        if(cantoso->isEnemy() && cantoso->getVida() == 0)
            info.estado = yaLoSabia;
        else if(cantoso->isTrigger())
            info.estado = yaLoSabia;
    }

    /*//test if there is LOS between bots
    if(enemigo->canWalkBetween(enemigo->getPosition(),(cantoso)->getPosition()))
    {
        info.sinObstaculos = true;

        //test if the bot is within FOV
        if (enemigo->isEnemySeeing(cantoso->getPosition()))
        {
            info.ultimaPercepcion = PhisicsWorld::getInstance()->getTimeStamp()/1000;
            info.ultimaPosicion = cantoso->getPosition();
            info.ultimaVista = PhisicsWorld::getInstance()->getTimeStamp()/1000;

            if (info.entraEnFOV == false)
            {
                info.entraEnFOV  = true;
                info.primeraVista = info.ultimaPercepcion;
            }
        }

        else
        {
            info.entraEnFOV = false;
        }
    }

    else
    {
        info.sinObstaculos = false;
        info.entraEnFOV = false;
    }*/
}

//------------------------ GetListOfRecentlySensedEntities -------------------
//
//  returns a vector of the bots that have been sensed recently
//-----------------------------------------------------------------------------
std::list<GameEntity*> SensorMemory::GetListOfRecentlySensedEntitites()const
{
  //this will store all the entities the bot can remember
  std::list<GameEntity*> entities;

  float CurrentTime = PhisicsWorld::getInstance()->getTimeStamp();

  MemoryMap::const_iterator curRecord = memoryMap.begin();
  for (curRecord; curRecord!=memoryMap.end(); ++curRecord)
  {
    //if this bot has been updated in the memory recently, add to list
    if ( (CurrentTime - curRecord->second.ultimaPercepcion) <= memorySpan)
    {
      entities.push_back(curRecord->first);
    }
  }

  return entities;
}

//---------------------------- GetLastRecordedPositionOfOpponent -------------------
//
//  returns the last recorded position of the bot
//-----------------------------------------------------------------------------
Structs::TPosicion  SensorMemory::GetLastRecordedPositionOfEntity(GameEntity* entidad)const
{
  MemoryMap::const_iterator it = memoryMap.find(entidad);

  if (it != memoryMap.end())
  {
    return it->second.ultimaPosicion;
  }

  throw std::runtime_error("< SensorMemory::GetLastRecordedPositionOfOpponent>: Attempting to get position of unrecorded bot");
}

//----------------------------- GetTimeOpponentHasBeenVisible ----------------------
//
//  returns the amount of time the given bot has been visible
//-----------------------------------------------------------------------------
float  SensorMemory::GetTimeEntityHasBeenVisible(GameEntity* entidad)const
{
  MemoryMap::const_iterator it = memoryMap.find(entidad);

  if (it != memoryMap.end() && it->second.entraEnFOV)
  {
    return PhisicsWorld::getInstance()->getTimeStamp()/1000 - it->second.primeraVista;
  }

  return 0;
}

//-------------------- GetTimeOpponentHasBeenOutOfView ------------------------
//
//  returns the amount of time the given opponent has remained out of view
//  returns a high value if opponent has never been seen or not present
//-----------------------------------------------------------------------------
float SensorMemory::GetTimeEntityHasBeenOutOfView(GameEntity* entidad)const
{
  MemoryMap::const_iterator it = memoryMap.find(entidad);

  if (it != memoryMap.end())
  {
    return PhisicsWorld::getInstance()->getTimeStamp()/1000 - it->second.ultimaVista;
  }

  //return MaxDouble;
  return 0;
}

//------------------------ GetTimeSinceLastSensed ----------------------
//
//  returns the amount of time the given bot has been visible
//-----------------------------------------------------------------------------
float  SensorMemory::GetTimeSinceLastSensed(GameEntity* entidad)const
{
  MemoryMap::const_iterator it = memoryMap.find(entidad);

  if (it != memoryMap.end())
  {
    return PhisicsWorld::getInstance()->getTimeStamp()/1000 - it->second.ultimaPercepcion;
  }

  return 0;
}
//------------------------ GetEstadoEntity----------------------
//
//  returns the state of the Entity
//-----------------------------------------------------------------------------
EstadoEntity SensorMemory::getEstadoEntity(GameEntity* entidad)const{
    MemoryMap::const_iterator it = memoryMap.find(entidad);
    if (it != memoryMap.end())
    {
    return it->second.estado;
    }
}
