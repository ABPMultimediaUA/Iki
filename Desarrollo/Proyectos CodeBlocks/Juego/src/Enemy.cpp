#include "Enemy.h"
#include "Fachada/GraphicsFacade.h"
#include "PatrolRoute.h"
#include "PatrolPoint.h"




Enemy::Enemy(PatrolRoute* rutita)
{
    ruta = rutita;
    posicion = rutita->getInicial()->getPunto();
    estado = 0;
    sospecha = 0.0;
}


void Enemy::inicializar_enemigo(int t)
{
    Structs::TColor color = {0,0,255,0};
    tipo = t;
    modelo = GraphicsFacade::getInstance().createCubeSceneNode(2, posicion);
    modelo->cambiarColor(color);

}



