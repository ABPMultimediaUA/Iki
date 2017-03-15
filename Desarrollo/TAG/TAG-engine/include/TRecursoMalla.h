#ifndef TRECURSOMALLA_H
#define TRECURSOMALLA_H

#include <TRecurso.h>


class TRecursoMalla : public TRecurso
{
    public:
        TRecursoMalla();
        virtual ~TRecursoMalla();
        cargarFichero(char* nombre);
        draw();

        char *getNombre();
        void setNombre(char* n);

    protected:

    private:
        float* vertices, normales, texturas;
        float* verTriangulos, normTriangulos, textTriangulos;
        long nTriangulos;
};

#endif // TRECURSOMALLA_H
