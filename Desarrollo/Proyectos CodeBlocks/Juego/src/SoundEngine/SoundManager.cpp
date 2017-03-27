#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager()
{
    //ctor
    engine = irrklang::createIrrKlangDevice();
    engine->setSoundVolume(1.0f);
}

SoundManager::~SoundManager()
{
    //dtor
    canales.clear();
    sonidos.clear();

}

bool SoundManager::isCargado(std::string cadena)
{
    if (sonidos[cadena] != nullptr)
        return true;
    return false;
}

void SoundManager::cargarSonido(std::string cadena)
{
    if (!isCargado(cadena)){
        std::string str = "resources/Sonidos/" + cadena;
        const char *cstr = str.c_str();

        irrklang::ISoundSource* sonido = engine->addSoundSourceFromFile(cstr);
        sonidos.insert(std::make_pair(cadena,sonido));

    }
}

void SoundManager::playSonido(std::string s)
{
    irrklang::ISound* canal = engine->play3D(sonidos[s],irrklang::vec3df(0,0,0),true,false,true);
    canales.push_back(canal);
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

void SoundManager::Update()
{
 //   for(std::size_t i = canales.size(); i > 0 ; i--)
 //  {
 //       if(soundIsFinished(canales[i]))
 //          delete canales[i];
 //   }
}
