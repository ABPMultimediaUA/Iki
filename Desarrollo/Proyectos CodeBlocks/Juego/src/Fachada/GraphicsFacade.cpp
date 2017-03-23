#include "Fachada/GraphicsFacade.h"

GraphicsFacade::GraphicsFacade()
{
    crearDevice();

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();

	timer = device->getTimer();



	//cout << "Graphics Engine inicializado" << endl;
}

GraphicsFacade::~GraphicsFacade()
{
    //dtor
}

void GraphicsFacade::beginScene(){
    driver->beginScene(true, true, SColor(255,113,133,133));
}

void GraphicsFacade::crearDevice(){
    device = createDevice(video::EDT_OPENGL, dimension2d<u32>(resolucionX, resolucionY), 16, false, false, false, &MyEventReceiver::getInstance());
	device->setResizable(true);
}

void GraphicsFacade::endScene(){
    driver->endScene();
}

void GraphicsFacade::draw(){
	//Dibujamos los nodos y los cuadros de texto del entorno
	beginScene();
	smgr->drawAll();
	endScene();

}

bool GraphicsFacade::run(){

	return device->run();

}

void GraphicsFacade::close(){
    device->closeDevice();
}

void GraphicsFacade::drop(){

	device->drop();

}

/*void GraphicsEngine::setWindowCaption(){

	device->setWindowCaption(L"IKI");

}*/

void GraphicsFacade::iniciarRay(Structs::TPosicion rayPos){
    ray = line3df(vector3df(rayPos.X,rayPos.Y,rayPos.Z), vector3df(rayPos.X,rayPos.Y,rayPos.Z));
}

void GraphicsFacade::cambiarRay(Camera* camara){
    ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(
                      MyEventReceiver::getInstance().GetMouseState().Position, camara->getCamera());
}

bool GraphicsFacade::interseccionRayPlano(Structs::TPosicion &mousePosition){

    vector3df mousePosition2(170,0,50);

    if(plane.getIntersectionWithLine(ray.start, ray.getVector(), mousePosition2)){
        mousePosition.X = mousePosition2.X;
        mousePosition.Y = mousePosition2.Y;
        mousePosition.Z = mousePosition2.Z;
        return true;
    }
    else
        return false;
}

float GraphicsFacade::calcularDistancia(Structs::TPosicion position){
    vector3df toCalculate(position.X, position.Y, position.Z);
    return toCalculate.getLength();
}


SceneNode* GraphicsFacade::createCubeSceneNode(float tam, Structs::TPosicion posicionInicial){

    SceneNode* nodo = new SceneNode(tam, posicionInicial);

	return nodo;
}

Camera* GraphicsFacade::createCamera(Structs::TPosicion position, Structs::TPosicion lookAt){

    Camera* cam = new Camera(position, lookAt);

	return cam;
}

void GraphicsFacade::changeResolution(int number){
    ///number: 0-> 1360x768 1-> 1280x720 2-> 1024x768 3-> 768x576

    bool holi = false;

    switch(number){
    case 0:
        if(resolucionX != 1280){
            resolucionX = 1280;
            resolucionY = 720;
            holi = true;
        }
        break;
    case 1:
        if(resolucionX != 1360){
            resolucionX = 1360;
            resolucionY = 768;
            holi = true;
        }
        break;
    case 2:
        if(resolucionX != 1024){
            resolucionX = 1024;
            resolucionY = 768;
            holi = true;
        }
        break;
    case 3:
        if(resolucionX != 1280){
            resolucionX = 768;
            resolucionY = 576;
            holi = true;
        }
        break;
    default:
        break;
    }

    if(holi){
        /*close();
        drop();
        createDevice();*/
    }
}

/*void GraphicsFacade::reSizeWindow(){
    driver->OnResize(dimension2du(resolucionX, resolucionY));
    smgr->getActiveCamera()->setAspectRatio((float)resolucionX/resolucionY);
}*/
