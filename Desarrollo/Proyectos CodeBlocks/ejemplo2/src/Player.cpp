#include "Player.h"

Player::Player()
{
    //ctor
}

Player::~Player()
{
    //dtor
}

void Player::inicializar(scene::ISceneManager* smgr){

    modelo = smgr->addCubeSceneNode(5);
    modelo->setMaterialFlag(video::EMF_LIGHTING, false);
    modelo->setPosition(core::vector3df(40,0,0));
    cuboProta = modelo->getPosition();

}

core::vector3df Player::getCuboProta(){
    return cuboProta;
}

void Player::setCuboProta(core::vector3df cb){
    cuboProta = cb;
}

scene::IMeshSceneNode* Player::getModelo(){
    return modelo;
}
