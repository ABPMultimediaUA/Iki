#include "Scene.h"

Scene::Scene()
{
    world = new World;
    entity_man = new GameEntity;
}

Scene::~Scene()
{
    world = nullptr;
    entity_man = nullptr;
}

void Scene::inicializar_escena(){

    world->inicializar_mundo();
    entity_man->inicializar_entidades();
}

void update_escena(){

    world->update_mundo();
    entity_man->update_entidades();

}
