#include "SoundFacade.h"

SoundFacade::SoundFacade()
{
    //ctor
    engine = createIrrKlangDevice();
}

SoundFacade::~SoundFacade()
{
    //dtor
}

Sonido* SoundFacade::cargarSonido(char *cadena)
{
    Sonido* sonido;
    sonido = new Sonido(cadena, engine);
    return sonido;
}

void SoundFacade::playSonido(Sonido* sonido)
{
    //ISound* canal = engine->play3D(sonido,posicion,true,false,true);
}
