#include "TriggerSystem.h"

TriggerSystem::TriggerSystem()
{
    //ctor
}

TriggerSystem::~TriggerSystem()
{
    //dtor
    Clear();
}

void TriggerSystem::Clear()
{
    //this deletes any current triggers and empties the trigger list
    TriggerList::iterator curTrg;
    for (curTrg = m_Triggers.begin(); curTrg != m_Triggers.end(); ++curTrg)
    {
        delete *curTrg;
    }

    m_Triggers.clear();
}

void TriggerSystem::Register(Trigger* trigger)
{
    m_Triggers.push_back(trigger);
}

void TriggerSystem::Update(GameEntity* entity)
{
    UpdateTriggers();
    TryTriggers(entity);
}

void TriggerSystem::Render()
{
    TriggerList::iterator curTrg;
    for (curTrg = m_Triggers.begin(); curTrg != m_Triggers.end(); ++curTrg)
    {
        ///(*curTrg)->Render();
    }
}

void TriggerSystem::LeerMapa()
{

}
