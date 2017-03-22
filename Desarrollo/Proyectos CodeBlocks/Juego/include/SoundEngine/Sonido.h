#ifndef SONIDO_H
#define SONIDO_H

#include <irrKlang.h>
#include "../lib/irrKlang/conio.h"

using namespace irrklang;

class Sonido
{
    public:
        Sonido(char *cad, ISoundEngine* engine);
        virtual ~Sonido();

    protected:

    private:

        ISoundSource* sonido;
};

#endif // SONIDO_H
