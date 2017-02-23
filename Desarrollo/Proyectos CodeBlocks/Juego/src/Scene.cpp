#include "Scene.h"
#include "GraphicsFacade.h"

Scene::Scene()
{
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
    DeltaTime = 0;

    player->inicializar_player();
    World::getInstance()->inicializar_mundo();

    bucle_juego();
}

void Scene::bucle_juego(){

    while(GraphicsFacade::getInstance().run()){
        player->update(camara, mousePosition);
        camara->render(player->getPosition());
        World::getInstance()->Step(DeltaTime);
        DeltaTime = GraphicsFacade::getInstance().getTimer()->getTime() - TimeStamp;
        TimeStamp = GraphicsFacade::getInstance().getTimer()->getTime();

        GraphicsFacade::getInstance().draw();
    }

    GraphicsFacade::getInstance().drop();

//    world->update_mundo();
//    player->update_player();

}
