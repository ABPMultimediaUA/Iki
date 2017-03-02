#include "Enemy.h"
#include "Fachada/GraphicsFacade.h"



void Enemy::inicializar_enemigo(int t)
{
    Structs::TColor color = {0,0,255,0};
    tipo = t;
    modelo = GraphicsFacade::getInstance().createCubeSceneNode(2, posicion);
    modelo->cambiarColor(color);

}



