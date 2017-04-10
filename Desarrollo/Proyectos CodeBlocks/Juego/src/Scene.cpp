#include "Scene.h"
#include "Fachada/GraphicsFacade.h"
#include "Fachada/Camera.h"
#include "PhisicsWorld.h"
#include "World.h"
#include "Player.h"
#include "Map.h"
#include "Menu.h"
#include "EntityManager.h"
#include "TriggerSystem.h"
#include "SoundManager.h"

Scene::Scene()
{
    world = new World();
    player = new Player();
    menu_ingame = new Menu();
}

Scene::~Scene()
{
    TriggerSystem::getInstance()->Clear();
    delete world;
    delete player;
    delete menu_ingame;

}

void Scene::cargarSonidos()
{
    //SoundMgr->cargarMusica("Ambientes/ambiente_desierto");
    //SoundMgr->cargarMusica("Ambientes/ambiente_desierto");
    //SoundMgr->cargarMusica("Ambientes/ambiente_desierto");

    //SoundMgr->cargarSonido("Triggers/ambiente_desierto");
    SoundMgr->cargarSonido("Triggers/cargadelarma");
    SoundMgr->cargarSonido("Triggers/tarjeta");
    SoundMgr->cargarSonido("Triggers/agua");
    SoundMgr->cargarSonido("Triggers/puerta_abrir");
    SoundMgr->cargarSonido("Triggers/puerta_cerrar");

    SoundMgr->cargarSonido("Player/disparoprota");
    SoundMgr->cargarSonido("Player/correr");
    SoundMgr->cargarSonido("Player/error");
    SoundMgr->cargarSonido("Player/metal1");
    SoundMgr->cargarSonido("Player/metal2");
    SoundMgr->cargarSonido("Player/pasosnormales");
    SoundMgr->cargarSonido("Player/articulacion2");
    SoundMgr->cargarSonido("Player/andarsigiloso");
}

void Scene::inicializar_escena(){

    Structs::TPosicion posicionCamara (190,30,40);
    Structs::TPosicion targetCamara (70,-10,40);
    Structs::TPosicion rayPos (170,0,50);

    camara = GraphicsFacade::getInstance().createCamera(posicionCamara, targetCamara);
    GraphicsFacade::getInstance().iniciarRay(rayPos);

    world->inicializar_mundo();

    Mapa = world->getMapa();
    player->inicializar_player(Mapa);
    //GraphicsFacade::getInstance().inicializar_gui(1);
    menu_ingame->inicializar_menu(1);

    Trigger* ruido = player->getRuido();
    TriggerSystem::getInstance()->Register(ruido);
    TriggerSystem::getInstance()->LeerMapa();

    cargarSonidos();
    SoundMgr->playMusica("Ambientes/ambiente_desierto");

    bucle_juego();
}

void Scene::bucle_juego(){

    while(GraphicsFacade::getInstance().run()){

        if(MyEventReceiver::getInstance().isKeyDown(KEY_ESCAPE)){
            f32 tiempo_anterior = GraphicsFacade::getInstance().getTimer()->getTime();
            menu_ingame->run();
            GraphicsFacade::getInstance().setTiempo(tiempo_anterior);
        }
        world->update_mundo();
        player->update(camara);
        TriggerSystem::getInstance()->Update();
        camara->render(player->getPosition());
        PhisicsWorld::getInstance()->Step();

        GraphicsFacade::getInstance().draw(0);
    }

    GraphicsFacade::getInstance().drop();

}
