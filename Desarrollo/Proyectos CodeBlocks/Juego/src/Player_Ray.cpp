#include "Player_Ray.h"
#include "Fachada/MeshSceneNode.h"
#include "Fachada/GraphicsFacade.h"
#include "PhisicsWorld.h"

Player_Ray::Player_Ray()
{
    Structs::TMedida medida     = {10,0.5,0.5};
    Structs::TPosicion posicion = {0,0,0};
    Structs::TColor color       = {0,128,128,128};
    modelo = new MeshSceneNode(medida,posicion,color);
    modelo->setVisible(false);
    balas = 5;
    vida = 0;
}

Player_Ray::~Player_Ray()
{
    delete modelo;
}

void Player_Ray::lanzar_rayo(Structs::TPosicion pos_prota){

    Structs::TPosicion mousePosition = {0,0,0};
    float angulo, distancia;
    balas--;
    vida = GraphicsFacade::getInstance().getTimer()->getTime()/1000.f;

    GraphicsFacade::getInstance().interseccionRayPlano(mousePosition);
    vec_distancia.X = mousePosition.X - pos_prota.X;
    vec_distancia.Y = mousePosition.Y - pos_prota.Y;
    vec_distancia.Z = mousePosition.Z - pos_prota.Z;

    input.p1.Set(pos_prota.X, pos_prota.Z);
    float modulo = sqrt((vec_distancia.X*vec_distancia.X) + (vec_distancia.Z*vec_distancia.Z));
    input.p2.Set(pos_prota.X+((vec_distancia.X/modulo)*30), pos_prota.Z+((vec_distancia.Z/modulo)*30));

    distancia = sqrt(pow(input.p2.x-input.p1.x, 2)+pow(input.p2.y-input.p1.y, 2));
    angulo = atan2f((input.p2.y-input.p1.y) , -(input.p2.x-input.p1.x)) * 180.f / irr::core::PI;

    Structs::TMedida med = {distancia/10, 0.5, 0.5};
    Structs::TPosicion pos = {(input.p2.x+input.p1.x)/2, 0, (input.p2.y+input.p1.y)/2};

    modelo->setScale(med);
    modelo->setPosition(pos);
    modelo->setRotation(angulo);
    modelo->setVisible(true);
}

void Player_Ray::borrar_rayo(){
    if(GraphicsFacade::getInstance().getTimer()->getTime()/1000.f - vida > 0.3)
        modelo->setVisible(false);
}
