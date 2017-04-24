#ifndef TEVENTRECEIVER_H
#define TEVENTRECEIVER_H

#include <SDL2\SDL.h>

#define EVENTO          SDL_Event
#define RATON           SDL_MouseButtonEvent
#define TECLADO         SDL_KeyboardEvent
#define ON_EVENT        SDL_PollEvent
#define TYPE            SDL_EventType
#define KPULSADA        SDL_KEYDOWN
#define KNO_PULSADA     SDL_KEYUP
#define RATON_IZQ       SDL_BUTTON_LEFT
#define RATON_DCH       SDL_BUTTON_RIGHT
#define RPULSADO        SDL_MOUSEBUTTONDOWN
#define RNO_PULSADO     SDL_MOUSEBUTTONUP
#define KEY_CODE        SDL_Keysym
#define KEY_CODE_COUNT  0xFF


class TEventReceiver
{
public:
    virtual ~TEventReceiver() {}


protected:

private:
};

#endif // TEVENTRECEIVER_H
