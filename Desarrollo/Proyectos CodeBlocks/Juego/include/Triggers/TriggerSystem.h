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

        TriggerList triggers;
        void UpdateTriggers();
        void TryTriggers();

    public:
        void Clear();
        void Register(Trigger* trigger);
        void CrearTipoTrigger(tinyxml2::XMLElement* objectGroup);
        void LeerMapa();

        void Update();
        void Render();
        const TriggerList& GetTriggers()const{return triggers;}

};

#endif // TRIGGERSYSTEM_H
