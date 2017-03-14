#ifndef TANIMACION_H
#define TANIMACION_H

#include <TEntidad.h>
#include <TMalla.h>

class TAnimacion : public TEntidad
{
    public:
        TAnimacion();
        virtual ~TAnimacion();

        void almacenarMalla(TMalla malla);
        void beginDraw();
        void endDraw();

    protected:

    private:
        vector<TMalla*> animacion;
        int frame;
};

#endif // TANIMACION_H
