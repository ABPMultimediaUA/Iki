#include "Map.h"








MapComponent::MapComponent(core::vector3df a, core::vector3df b, scene::ISceneManager* smgr){


mesh = smgr->getMesh("cubito.obj");
//smgr->getParameters()->setAttribute(irr::scene::COLLADA_CREATE_SCENE_INSTANCES, true);
modelo = smgr->addAnimatedMeshSceneNode(mesh);
modelo->setPosition(b);
//modelo->setScale(a);


}
