#include "GUI/HUD.h"
#include "Fachada/Image.h"

HUD::HUD()
{
    Vida       = nullptr;
    Laser      = nullptr;
    Desc_laser = nullptr;
    Num_balas  = nullptr;
}

HUD::~HUD()
{
    delete Vida;
    delete Laser;
    delete Desc_laser;
    delete Num_balas;
}

void HUD::inicializar_HUD(){
    Vida = new Image("resources/texturas/vidaprota.png");
    Laser = new Image("resources/texturas/lasertocar.png");
    Desc_laser = new Image("resources/texturas/leyendalaser.png");
    Num_balas = new Image("resources/texturas/numerobalas.png");
}

void HUD::draw(){

}
