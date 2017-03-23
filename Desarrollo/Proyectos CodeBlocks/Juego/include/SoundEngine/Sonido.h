#ifndef SONIDO_H
#define SONIDO_H

#include <string>
#include <irrKlang.h>
#include "../lib/irrKlang/conio.h"


class Sonido
{
    public:
        Sonido(std::string s, irrklang::ISoundEngine* engine);
        virtual ~Sonido();

        irrklang::ISoundSource* getSonido(){ return sonido; }

        void setVolumen(float f);

    protected:

    private:

        irrklang::ISoundSource* sonido;
};

#endif // SONIDO_H
