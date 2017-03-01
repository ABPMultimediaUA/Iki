#include "Enemy.h"
#include "Fachada/GraphicsFacade.h"


Enemy::Enemy(int &num_enemigos)
{
    num_enemigos++;
    id = num_enemigos;
    estado = 0;
    sospecha = 0.0;
}

Enemy::~Enemy()
{

}

void Enemy::inicializar_enemigo(int t, Structs::TPosicion p)
{
    Structs::TColor color = {0,0,255,0};
    tipo = t;
    posicion = p;
    modelo = GraphicsFacade::getInstance().createCubeSceneNode(2, posicion);
    modelo->cambiarColor(color);

}


