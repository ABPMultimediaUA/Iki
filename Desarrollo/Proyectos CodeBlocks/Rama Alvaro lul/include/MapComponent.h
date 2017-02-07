#include <irrlicht.h>
#include "driverChoice.h"
#include <World.h>
#include "PatrolRoute.h"


using namespace irr;

using namespace core; //namespace fundamentales;
using namespace scene; //namespace de escena;
using namespace video; //namespace de vídeo;
using namespace io; //namespace io;
using namespace gui; //namespace gui;

class MapComponent
{


public:
    void getlul();
    MapComponent(float, core::vector3df, scene::ISceneManager*, int);
    scene::IAnimatedMeshSceneNode *modelo;
    void setPosition(core::vector3df vec);
    void setPosicionBody(float ang);
    void destroyObj();
    void Activar();
    void Desactivar();
    bool comprobarPunto(b2Vec2 v);
    core::vector3df getPosicionObjeto();
     b2Body *body;
     PatrolPoint *pp;

private:
    scene::IAnimatedMesh *mesh;
    class World* iworld;











};


