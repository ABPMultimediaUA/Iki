#ifndef GRAPHICSFACADE_H
#define GRAPHICSFACADE_H

#include "MyEventReceiver.h"

#include "Camera.h"
#include "Structs.h"

class GUI;

class GraphicsFacade
{
    friend class MeshSceneNode;
    friend class AnimatedMesh;
    friend class Camera;

    public:

        static GraphicsFacade& getInstance() {
            static GraphicsFacade singleton;
            return singleton;
        }
        ~GraphicsFacade();

        void inicializar_gui(int);
        void vaciar_gui();

        //void beginScene();
        //void endScene();

        //void draw(int);
        bool run(int);
        void doDisplay();
        void close();
        void drop();

        void iniciarRay(Structs::TPosicion rayPos);
        void cambiarRay(Camera* camara);
        void changeResolution(int);
        //void reSizeWindow();
        bool interseccionRayPlano(Structs::TPosicion &mousePosition);
        /*ISceneManager* getScene() { return smgr; }
        IrrlichtDevice* getDevice() { return device; }
        IVideoDriver* getDriver() { return driver; }*/
        TMotorTAG* getMotor(){ return motor; }
        GUI* getGUI() { return gui; }
        //ITimer* getTimer()  { return timer; };

        Camera* createCamera(Structs::TPosicion position, Structs::TPosicion lookAt);

        void setTiempo(f32);

        int getWindowWidth() { return motor->getWindowWidth();}
        int getWindowHeigth(){ return motor->getWindowHeigth();}

    protected:

    private:

        GraphicsFacade();
        TMotorTAG* motor;
        GUI* gui;
        /*void crearDevice();
        IrrlichtDevice* device;
        IVideoDriver* driver;
        ISceneManager* smgr;
        ITimer* timer;
        plane3df plane;
        line3df ray;*/

        //TMotorTAG* motor;

        int resolucionX = 1360, resolucionY = 768;
};

#endif // GRAPHICSFACADE_H
