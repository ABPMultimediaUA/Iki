#ifndef MYEVENTRECEIVER_H
#define MYEVENTRECEIVER_H

/*#include <irrlicht.h>

#include <SFML/Window.hpp>

using namespace irr;

using namespace core; //namespace fundamentales;
using namespace scene; //namespace de escena;
using namespace video; //namespace de vídeo;
using namespace io; //namespace io;
using namespace gui; //namespace gui;*/
#include "Structs.h"

class MyEventReceiver
{
    public:

        static MyEventReceiver& getInstance() {
            static MyEventReceiver singleton;
            return singleton;
        }
        ~MyEventReceiver();

        sf::Event getEvent(){ return evento;}

        /*struct SMouseState{
            position2di Position;
            bool RightButtonDown;
            bool LeftButtonDown;
            SMouseState() : RightButtonDown(false) { }
        } MouseState;

        virtual bool OnEvent(const SEvent& event){
                // Remember the mouse state
            if (event.EventType == irr::EET_MOUSE_INPUT_EVENT){
                switch(event.MouseInput.Event){

                    case EMIE_RMOUSE_PRESSED_DOWN:
                        MouseState.RightButtonDown = true;
                    break;

                    case EMIE_RMOUSE_LEFT_UP:
                        MouseState.RightButtonDown = false;
                    break;

                    case EMIE_LMOUSE_PRESSED_DOWN:
                        MouseState.LeftButtonDown = true;
                    break;

                    case EMIE_LMOUSE_LEFT_UP:
                        MouseState.LeftButtonDown = false;
                    break;

                    case EMIE_MOUSE_MOVED:
                        MouseState.Position.X = event.MouseInput.X;
                        MouseState.Position.Y = event.MouseInput.Y;
                    break;

                    default:
                    // We won't use the wheel
                    break;
                }
            }
            else if (event.EventType == irr::EET_KEY_INPUT_EVENT){
                KeyDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
            }
        };
        virtual bool isKeyDown(EKEY_CODE keyCode) const { return KeyDown[keyCode]; }
        virtual bool isKeyUp(EKEY_CODE keyCode) const { return !KeyDown[keyCode]; }
        const SMouseState & GetMouseState(void) const { return MouseState; }*/

    protected:

    private:
        //bool KeyDown[KEY_KEY_CODES_COUNT];
        sf::Event evento;
        MyEventReceiver(){}
};

#endif // MYEVENTRECEIVER_H



