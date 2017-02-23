#ifndef TRECURSOMALLA_H
#define TRECURSOMALLA_H

#include <TRecurso.h>


class TRecursoMalla : public TRecurso
{
    public:
        TRecursoMalla();
        virtual ~TRecursoMalla();
        void cargarFichero(char* nombre);
        void draw();

    protected:

    private:
        float* vertices, normales, texturas;
        float* verTriangulos, normTriangulos, textTriangulos;
        long nTriangulos;
};

#endif // TRECURSOMALLA_H
