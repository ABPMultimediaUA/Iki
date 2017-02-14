#include "Scene.h"
#include "GraphicsFacade.h"
#include "PhisicsWorld.h"

Scene::Scene()
{
    world = new World();
    player = new Player();
    mousePosition = {170,0,50};
}

Scene::~Scene()
{
    delete player;
}

void Scene::inicializar_escena(){

    Structs::TPosicion posicionCamara = {190,30,40};
    Structs::TPosicion targetCamara = {170,-10,40};
    Structs::TPosicion rayPos = {170,0,50};

    camara = GraphicsFacade::getInstance().createCamera(posicionCamara, targetCamara);
    GraphicsFacade::getInstance().iniciarRay(rayPos);
    //camera = smgr->addCameraSceneNode(0,core::vector3df(0,90,-40),core::vector3df(0,0,0));

    TimeStamp = GraphicsFacade::getInstance().getTimer()->getTime();
    DeltaTime = GraphicsFacade::getInstance().getTimer()->getTime() - TimeStamp;

    player->inicializar_player();
    world->inicializar_mundo();

    std::cout<<"MousePosition: "<<mousePosition.X<<std::endl;
    bucle_juego();
}

void Scene::bucle_juego(){

    while(GraphicsFacade::getInstance().run()){
        player->update(camara, mousePosition);
        camara->render(player->getPosition());
        PhisicsWorld::getInstance().Step(DeltaTime);
        DeltaTime = GraphicsFacade::getInstance().getTimer()->getTime() - TimeStamp;
        TimeStamp = GraphicsFacade::getInstance().getTimer()->getTime();

        GraphicsFacade::getInstance().draw();
    }

    GraphicsFacade::getInstance().drop();

//    world->update_mundo();
//    player->update_player();

}
