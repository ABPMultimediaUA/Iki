#include "Enemies/Dron.h"
#include "Fachada/GraphicsFacade.h"
#include "PhisicsWorld.h"


void Dron::inicializar_enemigo(Map* m)
{
    //De momento todos tienen el mismo body y cosas en comun asi que las inicializo para los tres en init
    init(m);
    tipo = 3;
    vida = 1;
    Structs::TColor color = {0,255,150,150};
    aniMesh = new AnimatedMesh("resources/Modelos/dronbueno.obj", color, posicion, 0);
    aniMesh->setTexture("resources/Texturas/dron.png");
    aniMesh->setScale(5);
   // modelo->cambiarColor(color);
}
