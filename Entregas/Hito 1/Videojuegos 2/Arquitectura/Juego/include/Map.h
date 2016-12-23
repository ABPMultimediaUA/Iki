#ifndef MAP_H
#define MAP_H

#include <irrlicht.h>
#include <Box2D/Box2D.h>

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
        void inicializar_mapa(ISceneManager*);

    protected:

    private:

        IMesh *mesh;
        IMeshSceneNode *suelo;

};

#endif // MAP_H
