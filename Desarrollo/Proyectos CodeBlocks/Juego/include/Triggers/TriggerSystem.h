#ifndef TRIGGERSYSTEM_H
#define TRIGGERSYSTEM_H

#include "vector"
#include "Trigger.h"

#include "tinyxml2.h"

class TriggerSystem
{
    public:
        TriggerSystem();
        virtual ~TriggerSystem();

        typedef std::vector<Trigger*> TriggerList;

    private:

        TriggerList m_Triggers;
        void UpdateTriggers();
        void TryTriggers(GameEntity* entity);

    public:
        void Clear();
        void Register(Trigger* trigger);
        void CrearTipoTrigger(tinyxml2::XMLElement* objectGroup);
        void LeerMapa();

        void Update(GameEntity* entity);
        void Render();
        const TriggerList& GetTriggers()const{return m_Triggers;}

};

#endif // TRIGGERSYSTEM_H
