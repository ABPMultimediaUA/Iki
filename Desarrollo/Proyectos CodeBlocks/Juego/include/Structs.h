#ifndef STRUCTS_H
#define STRUCTS_H

#include <irrlicht.h>
#include <stdio.h>
#include "vector"
#include "string"

#include <Box2D/Box2D.h>

using namespace irr;

using namespace core; //namespace fundamentales;
using namespace scene; //namespace de escena;
using namespace video; //namespace de vídeo;
using namespace io; //namespace io;
using namespace gui; //namespace gui;

class Structs
{
    public:
        Structs();
        virtual ~Structs();
        typedef struct{
            float X;
            float Y;
            float Z;
        }TPosicion;

        typedef struct{
            int opacity;
            int r;
            int g;
            int b;
        }TColor;

        typedef struct{
            float ancho;
            float alto;
            float profundo;
        }TMedida;

    protected:

    private:
};

#endif // STRUCTS_H
