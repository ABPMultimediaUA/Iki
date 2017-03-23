#include "Sonido.h"

Sonido::Sonido(std::string s, irrklang::ISoundEngine* engine)
{
    //ctor
    std::string str = "ruta de sonidos" + s;
    const char *cstr = str.c_str();
    sonido = engine->addSoundSourceFromFile(cstr);
}

Sonido::~Sonido()
{
    //dtor
}

void Sonido::setVolumen(float f)
{
    sonido->setDefaultVolume(f);
}
