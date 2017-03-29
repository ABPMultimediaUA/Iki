#include "Scene.h"
#include "Fachada/GraphicsFacade.h"
#include "Fachada/Camera.h"
#include "PhisicsWorld.h"
#include "World.h"
#include "Player.h"
#include "Map.h"
#include "Menu.h"
#include "EntityManager.h"

Scene::Scene()
{
    world = new World();
    player = new Player();
    menu_ingame = new Menu();
}

Scene::~Scene()
{
    triggersystem.Clear();
    delete world;
    delete player;
    delete menu_ingame;

}

void Scene::inicializar_escena(){

    Structs::TPosicion posicionCamara (190,30,40);
    Structs::TPosicion targetCamara (70,-10,40);
    Structs::TPosicion rayPos (170,0,50);

    camara = GraphicsFacade::getInstance().createCamera(posicionCamara, targetCamara);
    GraphicsFacade::getInstance().iniciarRay(rayPos);
    GraphicsFacade::getInstance().inicializar_gui(1);
    //camera = smgr->addCameraSceneNode(0,core::vector3df(0,90,-40),core::vector3df(0,0,0));
    world->inicializar_mundo();
    Mapa = world->getMapa();
    player->inicializar_player(Mapa);
    menu_ingame->inicializar_menu(1);

    //EntityMgr->registrarEntity(player);

    Trigger* ruido = player->getRuido();
    triggersystem.Register(ruido);
    triggersystem.LeerMapa();

    bucle_juego();
}

void Scene::bucle_juego(){

    while(GraphicsFacade::getInstance().run()){

        if(MyEventReceiver::getInstance().isKeyDown(KEY_ESCAPE)){
            menu_ingame->run(false);
        }
        world->update_mundo();
        player->update(camara);
        triggersystem.Update();
        camara->render(player->getPosition());
        PhisicsWorld::getInstance()->Step();

        GraphicsFacade::getInstance().draw(0);
    }

    GraphicsFacade::getInstance().drop();

}
