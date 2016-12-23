#include "Scene.h"

Scene::Scene()
{
    world = new World;
    player = new Player;
}

Scene::~Scene()
{
    delete world;
    delete player;
}

void Scene::inicializar_escena(IrrlichtDevice* device){

    smgr = device->getSceneManager();
    camera = smgr->addCameraSceneNode(0,core::vector3df(0,90,-40),core::vector3df(0,0,0));

    player->inicializar_player(smgr);
    world->inicializar_mundo(smgr);
}

void Scene::update_escena(){

//    world->update_mundo();
//    player->update_player();

}

void Scene::render(){
    smgr->drawAll();
}
