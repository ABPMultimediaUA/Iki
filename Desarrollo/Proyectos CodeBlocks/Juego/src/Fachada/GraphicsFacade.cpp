#include "Fachada/GraphicsFacade.h"
#include "GUI/GUI.h"
#include "Fachada/MeshSceneNode.h"

GraphicsFacade::GraphicsFacade()
{
    motor = new TMotorTAG();
    gui = new GUI();
    /*crearDevice();

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();

	//guienv = device->getGUIEnvironment();

	timer      = device->getTimer();*/


	//cout << "Graphics Engine inicializado" << endl;
}

GraphicsFacade::~GraphicsFacade()
{
    //dtor
}

void GraphicsFacade::inicializar_gui(int menu){

    if(menu != 0)
        gui->inicializar_hd();

    ///MENU

    gui->anyadirmenu (400, 60, 0);

    ///BOTONES
    if(menu == 0)
        gui->anyadirboton(540, 160, "nuevapartidaboton");
    else
        gui->anyadirboton(540, 160, "botoncontinuar");

    gui->anyadirboton(540, 440, "salirboton");

    gui->anyadirboton(540, 300, "botonopciones");

    gui->anyadirboton(540, 540, "botonatras");

    ///TITULOS
    gui->anyadirtitulo(570, 125, "titulovolumen");

    gui->anyadirtitulo(570, 270, "resolucionboton");

    gui->anyadirtitulo(570, 340, "controlestitulo");

    gui->anyadirtitulo(565, 390, "controlespanel");

    ///CONTROLES

    gui->anyadircontrol(565, 320, "resoluciondentro", "checklleno");

    ///CONTROL VOLUMEN

    gui->anyadirvolumen(540, 175);

    if(menu == 0)
        gui->anyadirmenu (0, 0, 1);

}

void GraphicsFacade::vaciar_gui(){
    gui->clean();
}

/*void GraphicsFacade::beginScene(){
    driver->beginScene(true, true, SColor(255,113,133,133));
}

void GraphicsFacade::crearDevice(){
    device = createDevice(video::EDT_OPENGL, dimension2d<u32>(resolucionX, resolucionY), 16, false, false, false, &MyEventReceiver::getInstance());
	device->setResizable(true);
}

void GraphicsFacade::endScene(){
    driver->endScene();
}*/

/*void GraphicsFacade::draw(int draw_type){
	//Dibujamos los nodos y los cuadros de texto del entorno

	beginScene();
	smgr->drawAll();
    gui->draw(draw_type);
	endScene();

}*/

bool GraphicsFacade::run(int draw_type, TNodo* camara){

//    if(motor->Evented()){
        bool holi = motor->run(camara);
        gui->draw(draw_type);
        updateTiempo();
        motor->doDisplay();
        return holi;
   /* }
    else
        return false;*/
}

void GraphicsFacade::close(){
    //motor->closeDevice();
}

void GraphicsFacade::drop(){

	//device->drop();

}

void GraphicsFacade::iniciarRay(Structs::TPosicion rayPos){
    //ray = line3df(vector3df(rayPos.X,rayPos.Y,rayPos.Z), vector3df(rayPos.X,rayPos.Y,rayPos.Z));
}

void GraphicsFacade::cambiarRay(Camera* camara){
    /*ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(
          MyEventReceiver::getInstance().GetMouseState().Position, camara->getCamera());*/
    motor->cambiarRay(camara->getCamera());
}

bool GraphicsFacade::interseccionRayPlano(Structs::TPosicion &mousePosition){

    TVector vec(0,0,0);
    if(motor->interseccionRayPlano(vec)){
        mousePosition = {vec.X, vec.Y, vec.Z};
        return true;
    }
    else
        return false;
    /*TVector mousePosition2;

    if(plane.getIntersectionWithLine(ray.start, ray.getVector(), mousePosition2)){
        mousePosition.X = mousePosition2.X;
        mousePosition.Y = mousePosition2.Y;
        mousePosition.Z = mousePosition2.Z;
        return true;
    }
    else
        return false;*/
}

Camera* GraphicsFacade::createCamera(Structs::TPosicion position){

	return new Camera(position);
}

MeshSceneNode* GraphicsFacade::createMalla(const char* cadena){

	return new MeshSceneNode(cadena);
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

void GraphicsFacade::setTiempo(float tiempo){
    tiempo_quitado = tiempo_quitado + (motor->getTime() - tiempo);
}

void GraphicsFacade::updateTiempo(){
    tiempo_actual = motor->getTime() - tiempo_quitado;
}
/*void GraphicsFacade::pararTiempo(int time){
    if(time == 0)
        timer->stop();
    else
        timer_menu->stop();
}

void GraphicsFacade::reanudarTiempo(int time){
    if(time == 0)
        timer->start();
    else
        timer_menu->start();
}*/

