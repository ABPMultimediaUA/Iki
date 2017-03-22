#ifndef SOUNDFACADE_H
#define SOUNDFACADE_H

#include <irrKlang.h>
#include "../lib/irrKlang/conio.h"

#include "Sonido.h"

class SoundFacade
{
    public:
        static SoundFacade& getInstance() {
            static SoundFacade singleton;
            return singleton;
        }
        ~SoundFacade();

        ISoundEngine* getEngine(){ return engine; }

        Sonido* cargarSonido(char *cadena);
        void playSonido(Sonido* sonido);
        /*
        ISound;
        isound->stop;
        isound->isFinished()

        sonido->setVolumen(float);

         engine->setSoundVolume(float);
         engine->setSoundVolume(float);
        */
    protected:


    private:
        SoundFacade();

        ISoundEngine* engine;

};

#endif // SOUNDFACADE_H
