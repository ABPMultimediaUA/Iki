#include "Scene.h"
#include "Fachada/GraphicsFacade.h"
#include "Fachada/Camera.h"
#include "PhisicsWorld.h"
#include "World.h"
#include "Player.h"
#include "Map.h"
#include "Menu.h"
#include "EntityManager.h"
#include "SoundManager.h"
#include "TriggerSystem.h"
#include "Percibir.h"
#include <iostream>
using namespace std;
//#include "BarraCarga.h"


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
    SoundMgr->cargarMusica("Ambientes/ambiente_desierto");
    SoundMgr->cargarMusica("Musica/musica_general");

    SoundMgr->cargarSonido("Triggers/agua");
    SoundMgr->cargarSonido("Triggers/engranaje");
    SoundMgr->cargarSonido("Triggers/cargadelarma");
    SoundMgr->cargarSonido("Triggers/tarjeta");
    SoundMgr->cargarSonido("Triggers/agua");
    SoundMgr->cargarSonido("Triggers/puerta_abrir");
    SoundMgr->cargarSonido("Triggers/puerta_cerrar");
    SoundMgr->cargarSonido("Triggers/acceso_denegado");
    SoundMgr->cargarSonido("Triggers/acceso_confirmado");

    SoundMgr->cargarSonido("Player/disparoprota");
    SoundMgr->cargarSonido("Player/correr");
    SoundMgr->cargarSonido("Player/error");
    SoundMgr->cargarSonido("Player/metal1");
    SoundMgr->cargarSonido("Player/metal2");
    SoundMgr->cargarSonido("Player/pasosnormales");
    SoundMgr->cargarSonido("Player/articulacion2");
    SoundMgr->cargarSonido("Player/andarsigiloso");

    //SoundMgr->cargarSonido("AccionesRobots/muertedron");
    SoundMgr->cargarSonido("AccionesRobots/muertemedico");
    SoundMgr->cargarSonido("AccionesRobots/muertedron");
    SoundMgr->cargarSonido("AccionesRobots/conoelectrico");
    SoundMgr->cargarSonido("AccionesRobots/conoelectrico2");
    SoundMgr->cargarSonido("AccionesRobots/capsulas_aterrizando");
    SoundMgr->cargarSonido("AccionesRobots/alarma_sintetizada");

    SoundMgr->cargarSonido("VocesRobots/Guardia/protocolo_combate");
    SoundMgr->cargarSonido("VocesRobots/Guardia/escaneando");
    SoundMgr->cargarSonido("VocesRobots/Guardia/investigando");
    SoundMgr->cargarSonido("VocesRobots/Guardia/area_despejada_fin");
    //SoundMgr->cargarSonido("VocesRobots/Guardia/diagnostico_terreno");

    //SoundMgr->cargarSonido("VocesRobots/Medico/diagnostico_terreno_medico");
    SoundMgr->cargarSonido("VocesRobots/Medico/intruso_detectado_medico");
    SoundMgr->cargarSonido("VocesRobots/Medico/investigando_medico");
    SoundMgr->cargarSonido("VocesRobots/Medico/escaneando_medico");
    SoundMgr->cargarSonido("VocesRobots/Medico/area_despejada_medico");

    SoundMgr->cargarSonido("VocesRobots/Dron/beepaliviado");
    SoundMgr->cargarSonido("VocesRobots/Dron/beepenfadado");
    SoundMgr->cargarSonido("VocesRobots/Dron/beepinvestigar");
    SoundMgr->cargarSonido("VocesRobots/Dron/beepveralgo");
    //SoundMgr->cargarSonido("VocesRobots/Dron/beepvigilar");
}

void Scene::inicializar_escena(int nivel){

   /* int segundos=5;
    for(int i=0; i<=21; i++)
        cout << "\n";
    cout << "\t\t\t\t   CARGANDO...\n";
    for(int i=0; i<=79; i++)
        cout << "_";
*/
    GraphicsFacade::getInstance().drawCarga(0);
    isGameActive = true;
    reintentar = true;
    Structs::TPosicion posicionCamara;
    Structs::TPosicion targetCamara;
    Structs::TPosicion rayPos;

    f32 tiempo_anterior = GraphicsFacade::getInstance().getTimer()->getTime();

    if(nivel == 1){
        posicionCamara = {190,30,40};
        targetCamara   = {70,-10,40};
        rayPos         = {170,0,50};

    }else{
        posicionCamara = {190,30,40};
        targetCamara   = {70,-10,40};
        rayPos         = {190,0,50};
    }

    camara = GraphicsFacade::getInstance().createCamera(posicionCamara, targetCamara);
    GraphicsFacade::getInstance().iniciarRay(rayPos);

    GraphicsFacade::getInstance().drawCarga(1);
    world->inicializar_mundo(nivel);
    Mapa = world->getMapa();

    GraphicsFacade::getInstance().drawCarga(2);
    player->inicializar_player(Mapa, nivel);

    GraphicsFacade::getInstance().drawCarga(3);
    menu_ingame->inicializar_menu(1);

    //GraphicsFacade::getInstance().inicializar_gui(1);

    Trigger* ruido = player->getRuido();
    TriggerSystem::getInstance()->Register(ruido);
    TriggerSystem::getInstance()->LeerMapa(nivel);

    GraphicsFacade::getInstance().drawCarga(4);
    cargarSonidos();
    SoundMgr->playMusica("Ambientes/ambiente_desierto");
    SoundMgr->playMusica("Musica/musica_general");

    GraphicsFacade::getInstance().setTiempo(tiempo_anterior);
    PhisicsWorld::getInstance()->setTimeStamp();
    /*   for(int i=0; i<=79; i++)
    {
        cout<<char(219);//lo que rellena la barra
        Sleep(segundos*1000/80);
    }
    cout<<"\nCompletado!\n";
    */
    bucle_juego(nivel);


}

void Scene::bucle_juego(int nivel){

    while(isGameActive){

        GraphicsFacade::getInstance().run();

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

        /*if(player->wantReintentar()){
            cleanScene();
            isGameActive = false;
            reintentar = true;
        }*/
        if(player != nullptr){
            //if(MyEventReceiver::getInstance().isKeyDown(KEY_SPACE)){
            if(player->isNivelFinished()){
                cleanScene();
                isGameActive = false;
            }
        }
    }

    /*if(reintentar)
        inicializar_escena(nivel);*/
    if(nivel == 2)
        GraphicsFacade::getInstance().drop();

}

void Scene::cleanScene(){
    Mapa = nullptr;
    player = nullptr;
    EntityManager::Instance()->Clear();
    TriggerSystem::getInstance()->Clear();
    world->cleanWorld();
    delete camara;
    Percibir::Instance()->Salgo();
    GraphicsFacade::getInstance().clearEscena();
    GraphicsFacade::getInstance().vaciar_gui();
}
