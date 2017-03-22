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

void TriggerSystem::TryTriggers()
{
            //test each entity against the triggers
            std::vector<GameEntity*> entities = EntityMgr->getEntities();
            std::vector<GameEntity*>::iterator curEnt = entities.begin();
            for (curEnt; curEnt != entities.end(); ++curEnt)
            {
                //an entity must be ready for its next trigger update and it must be
                //alive before it is tested against each trigger.
                //if ((*entity)->isReadyForTriggerUpdate() && (*entity)->isAlive())
                //{
                    TriggerList::const_iterator curTrg;
                    if (!m_Triggers.empty())
                        for (curTrg = m_Triggers.begin(); curTrg != m_Triggers.end(); ++curTrg)
                        {
                            (*curTrg)->Try(*curEnt);
                        }
                //}
            }
}

void TriggerSystem::Update()
{
    //UpdateTriggers();
    TryTriggers();
}

void TriggerSystem::Render()
{
    TriggerList::iterator curTrg;
    for (curTrg = m_Triggers.begin(); curTrg != m_Triggers.end(); ++curTrg)
    {
        ///(*curTrg)->Render();
    }
}

void TriggerSystem::CrearTipoTrigger(int tipo, tinyxml2::XMLElement* objectGroup)
{
    tinyxml2::XMLElement* object;
    TriggerFactory factory;
    float z, x, r;

    if (objectGroup->FirstChildElement("object")){
        object = objectGroup->FirstChildElement("object");
        while (object){

            object->QueryFloatAttribute("x", &z);
            object->QueryFloatAttribute("y", &x);
            object->QueryFloatAttribute("rotation", &r);

            Trigger* trigger = factory.crearTrigger(tipo,z,x,r);
            m_Triggers.push_back(trigger);

            object = object->NextSiblingElement("object");
        }
    }
}

void TriggerSystem::LeerMapa()
{
    //int _width, _tileWidth, _height, _tileHeigth;

    //Se lee el fichero .tmx
    tinyxml2::XMLDocument* docFile;
    docFile = new tinyxml2::XMLDocument;
    docFile->LoadFile("resources/Mapas/Mapa.tmx");

    tinyxml2::XMLElement* mapElement = docFile->FirstChildElement("map");
   // mapElement->QueryIntAttribute("width", &_width);
   // mapElement->QueryIntAttribute("height", &_height);
   // mapElement->QueryIntAttribute("tilewidth", &_tileWidth);
   // mapElement->QueryIntAttribute("tileheight", &_tileHeigth);

    //Se recorre la cada capa de Objects
    tinyxml2::XMLElement* objectGroup = mapElement->FirstChildElement("objectgroup");
    while (objectGroup){

        //Para cada capa se asigna un tipo de Trigger
        if      (objectGroup->Attribute("name", "Puertas"))
            CrearTipoTrigger(2, objectGroup);
        //else if (objectGroup->Attribute("name", "Palancas"))   CrearTipoTrigger(3, objectGroup);
        else if (objectGroup->Attribute("name", "Objetos"))
            CrearTipoTrigger(4, objectGroup);
        //else if (objectGroup->Attribute("name", "Apisonadora"))CrearTipoTrigger(5, objectGroup);

        objectGroup = objectGroup->NextSiblingElement("objectgroup");

    }
}
