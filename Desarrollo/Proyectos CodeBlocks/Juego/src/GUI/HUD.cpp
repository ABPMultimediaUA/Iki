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
    AvisoAceite   = nullptr;

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
    delete AvisoAceite;

    delete player;
}

void HUD::inicializar_HUD(){

    player = static_cast<Player*>(EntityMgr->getEntityByID(0));

    ///Overlay
    Structs::TRectangulo rec = {0, 0, 1360, 768};
    elementos.push_back(new HUD_Element(0, 0, rec, "Overlay", true));

    ///Vida del prota
    rec = {450, 0, 605, 250};
    elementos.push_back(new HUD_Element(10, 10, rec, "vidaprota", true));
    Vida = elementos[1];

    ///Imágenes de habilidades
    rec = {0, 0, 79, 79};
    elementos.push_back(new HUD_Element(1080, 585, rec, "Q", true));
    Golpe = elementos[2];

    rec = {0, 0, 79, 79};
    elementos.push_back(new HUD_Element(1160, 585, rec, "W", true));
    Rayo = elementos[3];

    rec = {0, 0, 79, 79};
    elementos.push_back(new HUD_Element(1240, 585, rec, "shift", true));
    Sigilo = elementos[4];

    ///Descripciones
    rec = {0, 0, 429, 164};
    elementos.push_back(new HUD_Element(840, 420, rec, "leyendalaser", false));
    Leyenda = elementos[5];

    rec = {0, 0, 429, 164};
    elementos.push_back(new HUD_Element(760, 420, rec, "leyendaQ", false));
    LeyendaQ = elementos[6];

    rec = {0, 0, 429, 164};
    elementos.push_back(new HUD_Element(920, 420, rec, "leyendasigilo", false));
    LeyendaShift = elementos[7];

    ///Balas del rayo
    rec = {85, 0, 98, 17};
    elementos.push_back(new HUD_Element(955, 445, rec, "numerobalas", false));
    Balas = elementos[8];

    ///Tarjetita cuando tenemos llave
    rec = {0, 0, 162, 105};
    elementos.push_back(new HUD_Element(1180, 10, rec, "tarjetaesquina", false));
    Tarjeta = elementos[9];

    ///Avisos
    rec = {0, 0, 122, 25};
    elementos.push_back(new HUD_Element(1200, 280, rec, "tarjeta", false));
    AvisoTarjeta = elementos[10];

    rec = {0, 0, 122, 25};
    elementos.push_back(new HUD_Element(1200, 280, rec, "municion", false));
    AvisoMunicion = elementos[11];

    rec = {0, 0, 125, 25};
    elementos.push_back(new HUD_Element(1200, 280, rec, "aceite", false));
    AvisoAceite = elementos[12];

    ///Avisos de falta de objeto

    rec = {0, 0, 31, 31};
    elementos.push_back(new HUD_Element(1200, 280, rec, "tarjetafalta", false));
    AvisoNotTarjeta = elementos[13];

    rec = {0, 0, 31, 31};
    elementos.push_back(new HUD_Element(1200, 280, rec, "faltamunicion", false));
    AvisoNotMunicion = elementos[14];



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
    if(Golpe->comprobarEncima())
        LeyendaQ->setActive(true);
    else
        LeyendaQ->setActive(false);

    if(Sigilo->comprobarEncima())
        LeyendaShift->setActive(true);
    else
        LeyendaShift->setActive(false);

    comprobarAvisos();


    for(size_t i = 0; i < elementos.size(); i++){
        if(elementos[i]->isActive())
            elementos[i]->draw();
    }
}

void HUD::comprobarAvisos(){
    if(GraphicsFacade::getInstance().getTimer()->getTime()/1000.f - tiempo_con_aviso > 1.5){
        AvisoTarjeta->setActive(false);
        AvisoMunicion->setActive(false);
        AvisoAceite->setActive(false);
        AvisoNotTarjeta->setActive(false);
        AvisoNotMunicion->setActive(false);
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

void HUD::activateAceite(){
    AvisoAceite->setActive(true);
    tiempo_con_aviso = GraphicsFacade::getInstance().getTimer()->getTime()/1000.f;
}

void HUD::activateNotMunicion(){
    AvisoNotMunicion->setActive(true);
    tiempo_con_aviso = GraphicsFacade::getInstance().getTimer()->getTime()/1000.f;
}

void HUD::activateNotTarjeta(){
    AvisoNotTarjeta->setActive(true);
    tiempo_con_aviso = GraphicsFacade::getInstance().getTimer()->getTime()/1000.f;
}
