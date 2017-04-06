#include "GUI/HUD.h"
#include "Fachada/Image.h"

#include "EntityManager.h"
#include "Player.h"

#include "Fachada/GraphicsFacade.h"

HUD::HUD()
{
    Vida          = nullptr;
    Balas         = nullptr;
    Leyenda       = nullptr;
    Rayo          = nullptr;
    Sigilo        = nullptr;
    Tarjeta       = nullptr;
    AvisoTarjeta  = nullptr;
    AvisoMunicion = nullptr;

    player  = nullptr;
    //player  = static_cast<Player*>(EntityManager::Instance()->getEntities()[0]);
}

HUD::~HUD()
{
    delete Vida;
    delete Balas;
    delete Leyenda;
    delete Rayo;
    delete Sigilo;
    delete Tarjeta;
    delete AvisoTarjeta;
    delete AvisoMunicion;

    delete player;
}

void HUD::inicializar_HUD(){

    player = static_cast<Player*>(EntityMgr->getEntityByID(0));

    ///Vida del prota
    Structs::TRectangulo rec = {450, 0, 605, 250};
    elementos.push_back(new HUD_Element(10, 10, rec, "vidaprota", true));
    Vida = elementos[0];

    ///Imágenes de habilidades
    rec = {0, 0, 79, 79};
    elementos.push_back(new HUD_Element(1080, 585, rec, "Q", true));
    //Golpe = elementos[1];

    rec = {0, 0, 79, 79};
    elementos.push_back(new HUD_Element(1160, 585, rec, "W", true));
    Rayo = elementos[2];

    rec = {0, 0, 79, 79};
    elementos.push_back(new HUD_Element(1240, 585, rec, "shift", true));
    Sigilo = elementos[3];

    ///Descripcion del rayo
    rec = {0, 0, 429, 164};
    elementos.push_back(new HUD_Element(840, 435, rec, "leyendalaser", false));
    Leyenda = elementos[4];

    ///Balas del rayo
    rec = {85, 0, 98, 17};
    elementos.push_back(new HUD_Element(955, 460, rec, "numerobalas", false));
    Balas = elementos[5];

    ///Tarjetita cuando tenemos llave
    rec = {0, 0, 162, 105};
    elementos.push_back(new HUD_Element(1180, 10, rec, "tarjetaesquina", false));
    Tarjeta = elementos[6];

    ///Avisos
    rec = {0, 0, 122, 25};
    elementos.push_back(new HUD_Element(1200, 280, rec, "tarjeta", false));
    AvisoTarjeta = elementos[7];

    rec = {0, 0, 122, 25};
    elementos.push_back(new HUD_Element(1200, 280, rec, "municion", false));
    AvisoMunicion = elementos[8];

}

void HUD::draw(){

    actualizarVidas();
    actualizarBalas();
    //actualizarPosicionEnemies();
    if(Rayo->comprobarEncima()){
        Leyenda->setActive(true);
        Balas->setActive(true);
    }
    else{
        Leyenda->setActive(false);
        Balas->setActive(false);
    }
    if(GraphicsFacade::getInstance().getTimer()->getTime()/1000.f - tiempo_con_aviso > 1.5){
        AvisoTarjeta->setActive(false);
        AvisoMunicion->setActive(false);
    }

    for(size_t i = 0; i < elementos.size(); i++){
        if(elementos[i]->isActive())
            elementos[i]->draw();
    }
}

void HUD::actualizarVidas(){
    Structs::TRectangulo rec = {10 + (110 *(player->getVida()-1)), 0, 115 + (110 *(player->getVida()-1)), 250};
    Vida->cambiarRect(rec);
}

void HUD::actualizarBalas(){
    Structs::TRectangulo rec = {player->getMunicion() * 17, 0, (player->getMunicion() * 17.5) + 10, 16.9};
    Balas->cambiarRect(rec);
}

void HUD::rayoUsed(){
    Rayo->changeColor({255,113,113,133});
}

void HUD::rayoNotUsed(){
    Rayo->changeColor({255,255,255,255});
}

void HUD::sigiloUsed(){
    Sigilo->changeColor({255,113,113,133});
}

void HUD::sigiloNotUsed(){
    Sigilo->changeColor({255,255,255,255});
}

void HUD::activateTarjeta(){
    Tarjeta->setActive(true);
    AvisoTarjeta->setActive(true);
    tiempo_con_aviso = GraphicsFacade::getInstance().getTimer()->getTime()/1000.f;
}

void HUD::desactivateTarjeta(){
    Tarjeta->setActive(false);
}

void HUD::activateMunicion(){
    AvisoMunicion->setActive(true);
    tiempo_con_aviso = GraphicsFacade::getInstance().getTimer()->getTime()/1000.f;
}
