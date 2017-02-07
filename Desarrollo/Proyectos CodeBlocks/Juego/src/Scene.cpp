#include "Scene.h"
#include "GraphicsFacade.h"
#include "PhisicsWorld.h"

Scene::Scene()
{
    world = new World();
    player = new Player();
    mousePosition = {0,0,0};
}

Scene::~Scene()
{
    delete player;
}

void Scene::inicializar_escena(){

    Structs::TPosicion posicionCamara = {0,90,-40};
    Structs::TPosicion targetCamara = {0,0,0};

    camara = GraphicsFacade::getInstance().createCamera(posicionCamara, targetCamara);
    //camera = smgr->addCameraSceneNode(0,core::vector3df(0,90,-40),core::vector3df(0,0,0));

    TimeStamp = GraphicsFacade::getInstance().getTimer()->getTime();
    DeltaTime = GraphicsFacade::getInstance().getTimer()->getTime() - TimeStamp;

    player->inicializar_player();
    world->inicializar_mundo();

    bucle_juego();
}

void Scene::bucle_juego(){

    while(GraphicsFacade::getInstance().run()){
        player->update(camara, mousePosition);
//        camara.render(player->getPosition());
        PhisicsWorld::getInstance().Step(DeltaTime);
        DeltaTime = GraphicsFacade::getInstance().getTimer()->getTime() - TimeStamp;
        TimeStamp = GraphicsFacade::getInstance().getTimer()->getTime();

        GraphicsFacade::getInstance().draw();
    }

    GraphicsFacade::getInstance().drop();

//    world->update_mundo();
//    player->update_player();

}
