#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <map>
#include <vector>
#include <string>

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

        typedef std::map<std::string, irrklang::ISoundSource*> SoundMap;
        typedef std::map<std::string, irrklang::ISoundSource*> MusicMap;
        typedef std::map<std::string, irrklang::ISound*> SoundChannels;

        bool isCargado(std::string s);
        void cargarSonido(std::string s);
        void cargarMusica(std::string s);

        bool isPlaying(std::string s);
        void playSonido(std::string s);
        void playMusica(std::string s);

        void volumenGeneral(float f);
        void volumenSonido(float f, std::string s);
        void volumenMusica(float f, std::string s);

        bool soundIsFinished(std::string s);
        void soundStop(std::string s);
        void stopAll(){ engine->stopAllSounds(); }

        void Update();

    protected:

    private:
        SoundManager();
        irrklang::ISoundEngine* engine;

        SoundMap sonidos;
        MusicMap musica;
        SoundChannels canales;

};

#endif // SOUNDMANAGER_H
