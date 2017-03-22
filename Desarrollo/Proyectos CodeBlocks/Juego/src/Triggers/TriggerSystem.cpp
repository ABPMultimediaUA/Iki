#include "TriggerSystem.h"
#include "TriggerFactory.h"
#include "EntityManager.h"

#include <iostream>

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
    for (curTrg = triggers.begin(); curTrg != triggers.end(); ++curTrg)
    {
        delete *curTrg;
    }

    triggers.clear();
}

void TriggerSystem::Register(Trigger* trigger)
{
    triggers.push_back(trigger);
}

void TriggerSystem::UpdateTriggers()
{
    if (!triggers.empty())
    {
        TriggerList::iterator curTrg = triggers.begin();
        while (curTrg != triggers.end())
        {
            if ((*curTrg)->isToBeRemoved())
            {
                delete *curTrg;
                curTrg = triggers.erase(curTrg);
            }
            else
            {
                (*curTrg)->Update();
                ++curTrg;
            }
        }
    }
}

void TriggerSystem::TryTriggers()
{
        //test each entity against the triggers;
           // std::vector<GameEntity*>::iterator curEnt = EntityMgr->getEntities().begin();
           // for (curEnt; curEnt != EntityMgr->getEntities().end(); ++curEnt)
           // {
            TriggerList::iterator curTrg;
            for (curTrg = triggers.begin(); curTrg != triggers.end(); ++curTrg)
            {
                (*curTrg)->Try(EntityMgr->getEntityByID(0));
            }
}

void TriggerSystem::Update()
{
    UpdateTriggers();
    TryTriggers();
}

void TriggerSystem::Render()
{
    TriggerList::iterator curTrg;
    for (curTrg = triggers.begin(); curTrg != triggers.end(); ++curTrg)
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
            triggers.push_back(trigger);

                std::cout << triggers.size() << std::endl;

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
