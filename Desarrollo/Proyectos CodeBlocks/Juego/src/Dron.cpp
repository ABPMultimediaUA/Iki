#include "Dron.h"
#include "Fachada/GraphicsFacade.h"

void Dron::inicializar_enemigo()
{
    Structs::TColor color = {0,255,0,0};
    tipo = 3;
    modelo = GraphicsFacade::getInstance().createCubeSceneNode(2, posicion);
    modelo->cambiarColor(color);

}
