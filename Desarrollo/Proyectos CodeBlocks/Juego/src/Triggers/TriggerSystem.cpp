#include "TriggerSystem.h"
#include <iostream>

#include "TriggerFactory.h"

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

void TriggerSystem::UpdateTriggers()
{
    if (!m_Triggers.empty())
    {
        TriggerList::iterator curTrg = m_Triggers.begin();
        while (curTrg != m_Triggers.end())
        {
            if ((*curTrg)->isToBeRemoved())
            {
                delete *curTrg;
                curTrg = m_Triggers.erase(curTrg);
            }
            else
            {
                (*curTrg)->Update();
                ++curTrg;
            }
        }
    }
}

void TriggerSystem::TryTriggers(GameEntity* entity)
{
        /*    //test each entity against the triggers
            ContainerOfEntities::iterator curEnt = entities.begin();
            for (curEnt; curEnt != entities.end(); ++curEnt)
            {
                //an entity must be ready for its next trigger update and it must be
                //alive before it is tested against each trigger.
        */      //if ((*entity)->isReadyForTriggerUpdate() && (*entity)->isAlive())
                //{
                    TriggerList::const_iterator curTrg;
                    if (!m_Triggers.empty())
                        for (curTrg = m_Triggers.begin(); curTrg != m_Triggers.end(); ++curTrg)
                        {
                            (*curTrg)->Try(entity);
                        }
                //}
            //}
}

void TriggerSystem::Update(GameEntity* entity)
{
    //UpdateTriggers();
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

void TriggerSystem::CrearTipoTrigger(tinyxml2::XMLElement* objectGroup)
{
    tinyxml2::XMLElement* object;
    TriggerFactory factory;
    float z, x, r, t;

    if (objectGroup->FirstChildElement("object")){
        object = objectGroup->FirstChildElement("object");
        while (object){

            object->QueryFloatAttribute("x", &z);
            object->QueryFloatAttribute("y", &x);
            object->QueryFloatAttribute("rotation", &r);
            object->QueryFloatAttribute("type", &t);

            Trigger* trigger = factory.crearTrigger(t,z,x,r);
            m_Triggers.push_back(trigger);

            object = object->NextSiblingElement("object");

        }
    }
}

void TriggerSystem::LeerMapa()
{
    //Se lee el fichero .tmx
    tinyxml2::XMLDocument* docFile;
    docFile = new tinyxml2::XMLDocument;
    docFile->LoadFile("resources/Mapas/Mapa.tmx");

    tinyxml2::XMLElement* mapElement = docFile->FirstChildElement("map");
    //Se recorre la cada capa de Objects
    tinyxml2::XMLElement* objectGroup = mapElement->FirstChildElement("objectgroup");
    while (objectGroup){
        if (objectGroup->Attribute("name", "Triggers")){
            CrearTipoTrigger(objectGroup);
            objectGroup = nullptr;
        }else{
            objectGroup = objectGroup->NextSiblingElement("objectgroup");
        }
    }
}
