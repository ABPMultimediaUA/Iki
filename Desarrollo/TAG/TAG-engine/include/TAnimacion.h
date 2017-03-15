#ifndef TANIMACION_H
#define TANIMACION_H

#include <TEntidad.h>

#include <vector>
#include "TRecursoMalla.h"


class TAnimacion : public TEntidad
{
    public:
        TAnimacion();
        virtual ~TAnimacion();

        void almacenarMalla(TRecursoMalla* malla);
        void beginDraw(int frame);
        void endDraw();

    protected:

    private:
        vector<TRecursoMalla*> animacion;
        int frame;
};

#endif // TANIMACION_H
