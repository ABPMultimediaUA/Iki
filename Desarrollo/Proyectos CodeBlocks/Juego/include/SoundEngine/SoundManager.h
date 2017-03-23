#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <map>
#include <string>
#include "Sonido.h"

#include <irrKlang.h>
#include "../lib/irrKlang/conio.h"

class SoundManager
{
    public:
        static SoundManager* getInstance() {
            static SoundManager singleton;
            return &singleton;
        }
        virtual ~SoundManager();

        typedef std::map<std::string, Sonido*> SoundMap;

        void cargarSonido(std::string cadena);
        void playSonido(std::string s);

        bool isPlaying(std::string s);

        void volumenGeneral(float f);
        void volumenSonido(float f, const char *s);
        /*
        ISound;
        isound->stop;
        isound->isFinished();
        */
        void Update();

    protected:

    private:
        SoundManager();
        irrklang::ISoundEngine* engine;
        SoundMap sonidos;

};

#endif // SOUNDMANAGER_H
