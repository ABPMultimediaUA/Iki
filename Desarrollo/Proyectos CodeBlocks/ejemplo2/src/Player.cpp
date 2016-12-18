#include "Player.h"

Player::Player()
{
    //ctor
}

Player::~Player()
{
    //dtor
}

void Player::inicializar(scene::ISceneManager* smgr,video::IVideoDriver* driver){

    modelo = smgr->addCubeSceneNode(5,0,57);
    modelo->setMaterialFlag(video::EMF_LIGHTING, false);
    modelo->setMaterialTexture( 0, driver->getTexture("texturas/metal.png") );
    modelo->setMaterialType( video::EMT_SOLID );
    modelo->setPosition(core::vector3df(40,0,0));
    cuboProta = modelo->getPosition();
    vida=100;
    muerto=false;
}

core::vector3df Player::getCuboProta(){
    return cuboProta;
}

void Player::setCuboProta(core::vector3df cb){
    cuboProta = cb;
}
void Player::setRotationProta(float cb){
    modelo->setRotation(core::vector3df(0,cb,0));
}

scene::IMeshSceneNode* Player::getModelo(){
    return modelo;
}
float Player::getVida(){
    return vida;
}
void Player::matar(){
    modelo->remove();
    muerto=true;
}
bool Player::estaMuerto(){
    if(muerto)
        return false;
    else
        return true;
}
