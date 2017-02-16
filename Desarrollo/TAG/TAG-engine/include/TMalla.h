#ifndef TMALLA_H
#define TMALLA_H

#include <iostream>
#include <TEntidad.h>
#include "TFichero.h"
#include "TRecursoMalla.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing fla

class TMalla : public TEntidad
{
    public:
        TMalla();
        virtual ~TMalla();

        void cargarMalla(TFichero fich);

        void beginDraw();
        void endDraw();

    protected:

    private:
        TRecursoMalla *malla;
};

#endif // TMALLA_H
