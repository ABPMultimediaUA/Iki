#include <irrlicht.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif
class CAppReceiver : public IEventReceiver {

    private:
        bool KeyDown[KEY_KEY_CODES_COUNT];

    public:
        CAppReceiver() {
            for(int i=0;i<KEY_KEY_CODES_COUNT;i++) {
                KeyDown[i] = false;
            }
        }

    virtual bool OnEvent(const SEvent &event) {
        switch(event.EventType) {

            case irr::EET_KEY_INPUT_EVENT:{
                KeyDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
            }
            default:
            break;
        }
        return false;
    }

    virtual bool isKeyDown(EKEY_CODE keyCode) const {
        return KeyDown[keyCode];
    }

    virtual bool isKeyUp(EKEY_CODE keyCode) const{
        return !KeyDown[keyCode];
    }
};

int main() {
    CAppReceiver appReceiver;
    IrrlichtDevice *device = createDevice(video::EDT_OPENGL, dimension2d<u32>(640,480),16,false,false,false, &appReceiver);
    if(!device)
        return 1;

    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();

    IMeshSceneNode *cubeNode = smgr->addCubeSceneNode(10);

    if(cubeNode) {
          cubeNode->setMaterialFlag(EMF_LIGHTING, false);
          cubeNode->setPosition(vector3df(5,15,5));
    }
    smgr->addCameraSceneNode(0,vector3df(0,90,-40),vector3df(0,0,0));

    while(device->run()) {
        if(device->isWindowActive()) {
            vector3df cubePos = cubeNode->getPosition();
            if(appReceiver.isKeyDown(KEY_ESCAPE)) {
                device->closeDevice();
                return 0;
            }
            else if(appReceiver.isKeyDown(KEY_RIGHT)) {
                cubePos.X+=0.1;
            }
            else if (appReceiver.isKeyDown(KEY_LEFT)) {
                cubePos.X-=0.1;
            }

            cubeNode->setPosition(cubePos);
            driver->beginScene(true,true,SColor(255,255,101,140));
            smgr->drawAll();
            guienv->drawAll();
            driver->endScene();
        }else{
            device->yield();
        }
    }
}
