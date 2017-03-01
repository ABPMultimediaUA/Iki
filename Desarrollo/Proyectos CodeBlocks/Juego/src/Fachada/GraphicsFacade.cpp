#include "Fachada/GraphicsFacade.h"

GraphicsFacade::GraphicsFacade()
{
    device = createDevice(video::EDT_OPENGL, dimension2d<u32>(1280, 720), 16, false, false, false, &MyEventReceiver::getInstance());
	//device->activateJoysticks(*MastEventReceiver::getInstance().getJoystickInfo()); //activamos el joystick
	//cout << "Hay " << MastEventReceiver::getInstance().getJoystickInfo()->size() << " mando(s) conectado(s)" << endl;
	device->setResizable(true);

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

void GraphicsFacade::draw(){

	driver->beginScene(true, true, SColor(255,113,113,133));
	//Dibujamos los nodos y los cuadros de texto del entorno
	smgr->drawAll();
	guienv->drawAll();
	driver->endScene();

}

bool GraphicsFacade::run(){

	return device->run();

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
