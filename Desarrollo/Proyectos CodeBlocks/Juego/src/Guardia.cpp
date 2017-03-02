#include "Guardia.h"
#include "Fachada/GraphicsFacade.h"


void Guardia::inicializar_guardia(Structs::TPosicion p)
{
    Structs::TColor color = {0,0,255,0};
    tipo = 1;
    posicion = p;
    modelo = GraphicsFacade::getInstance().createCubeSceneNode(2, posicion);
    modelo->cambiarColor(color);

}
