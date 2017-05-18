#include "Player_Ray.h"
#include "Fachada/MeshSceneNode.h"
#include "Fachada/GraphicsFacade.h"
#include "PhisicsWorld.h"
#include "EntityManager.h"
#include "Enemy.h"
#include "Congelado.h"

Player_Ray::Player_Ray()
{
    //Structs::TMedida medida     = {10,0.5,0.5};
    //Structs::TPosicion posicion = {0,0,0};
    //Structs::TColor color       = {0,30,144,255};
    modelo = new MeshSceneNode("resources/Modelos/disptorre.obj");
    modelo->setTexture("resources/Texturas/rayo_azul.png");
    modelo->setVisible(false);
    balas = 4;
    vida = 0;
    input.maxFraction	=	1.0f;
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
    input.p2.Set(pos_prota.X+((vec_distancia.X/modulo)*20), pos_prota.Z+((vec_distancia.Z/modulo)*20));

    distancia = sqrt(pow(input.p2.x-input.p1.x, 2)+pow(input.p2.y-input.p1.y, 2));
    angulo = atan2f((input.p2.y-input.p1.y) , -(input.p2.x-input.p1.x)) * 180.f / irr::core::PI;

    Structs::TMedida med = {distancia/10, 0.5, 1};
    Structs::TPosicion pos = {(input.p1.x+input.p2.x)/2, 0, (input.p1.y+input.p2.y)/2};

    modelo->setScale(med);
    modelo->setPosition(pos);
    modelo->setRotation(angulo);
    modelo->setVisible(true);

    comprobarEnemigos();
}

void Player_Ray::borrar_rayo(){
    if(GraphicsFacade::getInstance().getTimer()->getTime()/1000.f - vida > 0.2)
        modelo->setVisible(false);
}

void Player_Ray::comprobarEnemigos(){

    std::vector<Enemy*> enemies = EntityManager::Instance()->getEnemigos();
    for(size_t i = 0; i < enemies.size(); i++){
        if(enemies[i]->getBody()->GetFixtureList()->RayCast(&output,input,0)){
            enemies[i]->GetFSM()->ChangeState(Congelado::Instance());
        }
    }
}
