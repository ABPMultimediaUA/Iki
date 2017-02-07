#ifndef MAP_H
#define MAP_H

#include <irrlicht.h>
#include <Box2D/Box2D.h>
#include "MeshSceneNode.h"

using namespace irr;

using namespace core; //namespace fundamentales;
using namespace scene; //namespace de escena;
using namespace video; //namespace de vídeo;
using namespace io; //namespace io;
using namespace gui; //namespace gui;


class Map
{
    public:
        Map();
        virtual ~Map();
        void inicializar_mapa();

    protected:

    private:

        MeshSceneNode *suelo;
        /*IMesh *mesh;
        IMeshSceneNode *suelo;*/

};

#endif // MAP_H
