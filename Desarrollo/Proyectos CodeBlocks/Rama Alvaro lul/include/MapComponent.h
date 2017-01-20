#include <irrlicht.h>
#include "driverChoice.h"
#include <World.h>



using namespace irr;

using namespace core; //namespace fundamentales;
using namespace scene; //namespace de escena;
using namespace video; //namespace de vídeo;
using namespace io; //namespace io;
using namespace gui; //namespace gui;

class MapComponent
{


    public:
        MapComponent(core::vector3df, core::vector3df, scene::ISceneManager*);

    private:
        scene::IAnimatedMesh *mesh;
        scene::IAnimatedMeshSceneNode *modelo;
        class World* iworld;
        b2Body *body;










};


