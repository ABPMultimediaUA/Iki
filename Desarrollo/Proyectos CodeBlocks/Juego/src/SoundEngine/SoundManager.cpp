#include "SoundManager.h"

SoundManager::SoundManager()
{
    //ctor
    engine = irrklang::createIrrKlangDevice();
}

SoundManager::~SoundManager()
{
    //dtor
    canales.clear();
    sonidos.clear();

}

void SoundManager::cargarSonido(std::string cadena)
{
    std::string str = "resources/Sonidos/" + cadena;
    const char *cstr = str.c_str();

    irrklang::ISoundSource* sonido = engine->addSoundSourceFromFile(cstr);
    sonidos.insert(std::make_pair(cadena,sonido));
}

void SoundManager::playSonido(std::string s)
{
    //irrklang::ISound* canal = engine->play3D(sonidos[s],posicion,true,false,true);
    // canales->push_back(canal);
}

bool SoundManager::isPlaying(std::string s)
{
   return engine->isCurrentlyPlaying(sonidos[s]);
}

void SoundManager::volumenGeneral(float f)
{
    engine->setSoundVolume(f);
}

void SoundManager::volumenSonido(float f, const char *s)
{
    sonidos[s]->setDefaultVolume(f);
}

void SoundManager::Update()
{

}
