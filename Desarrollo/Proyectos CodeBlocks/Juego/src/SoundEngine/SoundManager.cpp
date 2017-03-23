#include "SoundManager.h"

SoundManager::SoundManager()
{
    //ctor
    engine = irrklang::createIrrKlangDevice();
}

SoundManager::~SoundManager()
{
    //dtor
}

void SoundManager::cargarSonido(std::string cadena)
{
   Sonido* sonido;
   sonido = new Sonido(cadena, engine);
   sonidos.insert(std::make_pair(cadena,sonido));
}

void SoundManager::playSonido(std::string s)
{
    //ISound* canal = engine->play3D(sonido,posicion,true,false,true);
}

bool SoundManager::isPlaying(std::string s)
{
   return engine->isCurrentlyPlaying(sonidos[s]->getSonido());
}

void SoundManager::volumenGeneral(float f)
{
    engine->setSoundVolume(f);
}

void SoundManager::volumenSonido(float f, const char *s)
{
    sonidos[s]->setVolumen(f);
}

void SoundManager::Update()
{

}
