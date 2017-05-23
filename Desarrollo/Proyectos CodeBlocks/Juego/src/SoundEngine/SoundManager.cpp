#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager()
{
    //ctor
    engine = irrklang::createIrrKlangDevice();
    engine->setSoundVolume(0.5f);
}

SoundManager::~SoundManager()
{
    //dtor
    //engine->removeAllSoundSources();
    canales.clear();
    sonidos.clear();
    musica.clear();

}

bool SoundManager::isCargado(std::string cadena)
{
    if (sonidos[cadena] != nullptr)
        return true;
    return false;
}
bool SoundManager::isCargado2(std::string cadena)
{
    if (musica[cadena] != nullptr)
        return true;
    return false;
}

void SoundManager::cargarSonido(std::string cadena)
{
    if (!isCargado(cadena)){
        std::string str = "resources/BSO/" + cadena + ".wav";
        irrklang::ISoundSource* sonido = engine->addSoundSourceFromFile(str.c_str());
        sonidos[cadena] = sonido;
    }
}

void SoundManager::cargarMusica(std::string cadena)
{
    if (!isCargado2(cadena)){
    std::string str = "resources/BSO/" + cadena + ".wav";
    irrklang::ISoundSource* sonido = engine->addSoundSourceFromFile(str.c_str());
    musica[cadena] = sonido;
    }
}

void SoundManager::playSonido(std::string s)
{
    if(sonidos[s]){
        if (!canales[s]){
            irrklang::ISound* canal = engine->play3D(sonidos[s],irrklang::vec3df(0,0,0),false,false,true);
            canales[s] = canal;
        }else{
            canales[s] = engine->play3D(sonidos[s],irrklang::vec3df(0,0,0),false,false,true);
        }
    }
}

void SoundManager::playMusica(std::string s)
{
    if (!canales[s]){
        irrklang::ISound* canal = engine->play3D(musica[s],irrklang::vec3df(0,0,0),true,false,true);
        canales[s] = canal;
    }else{
        canales[s] = engine->play3D(musica[s],irrklang::vec3df(0,0,0),true,false,true);
    }
}

bool SoundManager::isPlaying(std::string s)
{
    if (sonidos[s])
        return engine->isCurrentlyPlaying(sonidos[s]);
    return false;
}

void SoundManager::volumenGeneral(float f)
{
    engine->setSoundVolume(f);
}

void SoundManager::volumenSonido(float f, std::string s)
{
    if (sonidos[s])
        sonidos[s]->setDefaultVolume(f);
}

void SoundManager::volumenMusica(float f, std::string s)
{
    if (musica[s])
        musica[s]->setDefaultVolume(f);
}

bool SoundManager::soundIsFinished(std::string s)
{
    if (canales[s])
        return canales[s]->isFinished();
    return nullptr;
}

void SoundManager::soundStop(std::string s)
{
    if (canales[s])
        canales[s]->stop();
}

void SoundManager::Update()
{
    /*
    for(std::size_t i = canales.size(); i > 0 ; i--)
   {
        if(soundIsFinished(canales[i]))
           delete canales[i];
   }
   */
}
