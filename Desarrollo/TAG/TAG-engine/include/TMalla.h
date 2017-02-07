#ifndef TMALLA_H
#define TMALLA_H

#include <TEntidad.h>
#include "TFichero.h"
#include "TRecursoMalla.h"

class TMalla : public TEntidad
{
    public:
        TMalla();
        virtual ~TMalla();

        void cargarMalla(TFichero);

        void beginDraw();
        void endDraw();

    protected:

    private:
        TRecursoMalla *malla;
};

#endif // TMALLA_H
