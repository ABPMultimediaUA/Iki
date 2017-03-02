#include "Guardia.h"
#include "Fachada/GraphicsFacade.h"


void Guardia::inicializar_enemigo()
{
    Structs::TColor color = {0,0,255,0};
    tipo = 1;
    modelo = GraphicsFacade::getInstance().createCubeSceneNode(2, posicion);
    modelo->cambiarColor(color);

}
