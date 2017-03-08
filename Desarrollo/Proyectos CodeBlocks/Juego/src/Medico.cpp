#include "Medico.h"
#include "Fachada/GraphicsFacade.h"

void Medico::inicializar_enemigo()
{
    Structs::TColor color = {0,0,0,255};
    tipo = 3;
    modelo = GraphicsFacade::getInstance().createCubeSceneNode(2, posicion);
    modelo->cambiarColor(color);

}
