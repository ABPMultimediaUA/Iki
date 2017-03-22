#include "Sonido.h"

Sonido::Sonido(char *cad, ISoundEngine* engine)
{
    //ctor
    sonido = engine->addSoundSourceFromFile(cad);
}

Sonido::~Sonido()
{
    //dtor
}
