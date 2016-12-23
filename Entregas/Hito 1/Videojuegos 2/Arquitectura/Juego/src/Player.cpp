#include "Player.h"

Player::Player()
{
    tipo = 0;
}

Player::~Player()
{

}

void Player::inicializar_player(ISceneManager* smgr){

    modelo = smgr->addCubeSceneNode(5);
    modelo->setPosition(vector3df(40,0,0));
    //smgr->getMeshManipulator()->setVertexColors(modelo->getMesh(), SColor(0, 255, 255, 255));
    posicion = modelo->getPosition();

}
