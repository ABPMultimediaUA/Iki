#include "../include/Enemy.h"


Enemy::Enemy()
{
    estado = 0;
}

Enemy::~Enemy()
{

}

void Enemy::inicializar_enemigo(int t, ISceneManager* smgr, vector3df p)
{
        estado = 0;
        tipo = t;
        posicion = p; //Meter en interfaz
        modelo = smgr->addCubeSceneNode(5);
        modelo->setPosition(posicion);
        smgr->getMeshManipulator()->setVertexColors(modelo->getMesh(),irr::video::SColor(0, 0, 255, 0));
}


