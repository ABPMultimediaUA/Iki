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
        //a container of all the triggers
        TriggerList m_Triggers;
        //this method iterates through all the triggers present in the system and
        //calls their Update method in order that their internal state can be
        //updated if necessary. It also removes any triggers from the system that
        //have their m_bRemoveFromGame field set to true.
        void UpdateTriggers();

        //this method iterates through the container of entities passed as a
        //parameter and passes each one to the Try method of each trigger provided
        //the entity is alive and is ready for a trigger update.
        //template <class ContainerOfEntities>
        void TryTriggers(GameEntity* entity);

    public:
        //this deletes any current triggers and empties the trigger list
        void Clear();

        //this is used to register triggers with the TriggerSystem (the TriggerSystem
        //will take care of tidying up memory used by a trigger)
        void Register(Trigger* trigger);

        //crea un trigger de un tipo y lo registra
        void CrearTipoTrigger(int tipo, tinyxml2::XMLElement* objectGroup);
        //lee el mapa tmx y crea y registra los triggers correspondientes
        void LeerMapa();
        //updates

        void Update(GameEntity* entity);
        //some triggers are required to be rendered (like giver-triggers for example)
        void Render();
        const TriggerList& GetTriggers()const{return m_Triggers;}

};

#endif // TRIGGERSYSTEM_H
