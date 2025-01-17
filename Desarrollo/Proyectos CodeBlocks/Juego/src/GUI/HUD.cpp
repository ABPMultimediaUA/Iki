#include "GUI/HUD.h"
#include "Fachada/Image.h"

#include "EntityManager.h"
#include "Player.h"

#include "Fachada/GraphicsFacade.h"

HUD::HUD()
{
    Vida             = nullptr;
    Balas            = nullptr;
    Leyenda          = nullptr;
    LeyendaQ         = nullptr;
    LeyendaShift     = nullptr;
    Rayo             = nullptr;
    Golpe            = nullptr;
    Sigilo           = nullptr;
    Tarjeta          = nullptr;
    AvisoTarjeta     = nullptr;
    AvisoMunicion    = nullptr;
    AvisoAceite      = nullptr;
    AvisoNotTarjeta  = nullptr;
    AvisoNotMunicion = nullptr;
    GOver            = nullptr;
    BotonReintentar  = nullptr;
    BotonFinJuego    = nullptr;

    player  = nullptr;
    //player  = static_cast<Player*>(EntityManager::Instance()->getEntities()[0]);
}

HUD::~HUD()
{
    Vida             = nullptr;
    Balas            = nullptr;
    Leyenda          = nullptr;
    LeyendaQ         = nullptr;
    LeyendaShift     = nullptr;
    Rayo             = nullptr;
    Golpe            = nullptr;
    Sigilo           = nullptr;
    Tarjeta          = nullptr;
    AvisoTarjeta     = nullptr;
    AvisoMunicion    = nullptr;
    AvisoAceite      = nullptr;
    AvisoNotTarjeta  = nullptr;
    AvisoNotMunicion = nullptr;
    GOver            = nullptr;
    BotonReintentar  = nullptr;
    BotonFinJuego    = nullptr;

    player  = nullptr;
}

void HUD::inicializar_HUD(){

    player = static_cast<Player*>(EntityMgr->getEntityByID(0));

    ///Overlay
    Structs::TRectangulo rec = {0, 0, 1360, 768};
    elementos.push_back(new HUD_Element(0, -8, rec, "Overlay", true));

    ///Vida del prota
    rec = {560, 0, 675, 230};
    elementos.push_back(new HUD_Element(10, 2, rec, "vidaprota", true));
    Vida = elementos[1];

    ///Im�genes de habilidades
    rec = {0, 0, 79, 79};
    elementos.push_back(new HUD_Element(1080, 605, rec, "Q", true));
    Golpe = elementos[2];

    rec = {0, 0, 79, 79};
    elementos.push_back(new HUD_Element(1165, 605, rec, "W", true));
    Rayo = elementos[3];

    rec = {0, 0, 79, 79};
    elementos.push_back(new HUD_Element(1250, 605, rec, "shift", true));
    Sigilo = elementos[4];

    ///Descripciones
    rec = {0, 0, 429, 164};
    elementos.push_back(new HUD_Element(840, 440, rec, "leyendalaser", false));
    Leyenda = elementos[5];

    rec = {0, 0, 429, 164};
    elementos.push_back(new HUD_Element(765, 440, rec, "leyendaQ", false));
    LeyendaQ = elementos[6];

    rec = {0, 0, 429, 164};
    elementos.push_back(new HUD_Element(930, 440, rec, "leyendasigilo", false));
    LeyendaShift = elementos[7];

    ///Balas del rayo
    rec = {85, 0, 98, 17};
    elementos.push_back(new HUD_Element(955, 465, rec, "numerobalas", false));
    Balas = elementos[8];

    ///Tarjetita cuando tenemos llave
    rec = {0, 0, 162, 105};
    elementos.push_back(new HUD_Element(1180, 10, rec, "tarjetaesquina", false));
    Tarjeta = elementos[9];

    ///Avisos
    rec = {0, 0, 122, 25};
    elementos.push_back(new HUD_Element(1180, 550, rec, "tarjeta", false));
    AvisoTarjeta = elementos[10];

    rec = {0, 0, 122, 25};
    elementos.push_back(new HUD_Element(1180, 550, rec, "municion", false));
    AvisoMunicion = elementos[11];

    rec = {0, 0, 125, 25};
    elementos.push_back(new HUD_Element(1180, 550, rec, "aceite", false));
    AvisoAceite = elementos[12];

    ///Avisos de falta de objeto

    rec = {0, 0, 31, 31};
    elementos.push_back(new HUD_Element(660, 290, rec, "tarjetafalta", false));
    AvisoNotTarjeta = elementos[13];

    rec = {0, 0, 31, 31};
    elementos.push_back(new HUD_Element(1190, 625, rec, "faltamunicion", false));
    AvisoNotMunicion = elementos[14];

    ///Pantalla Game Over

    rec = {0, 0, 1360, 768};
    elementos.push_back(new HUD_Element(0, 0, rec, "GAMEOVER", false));
    GOver = elementos[15];

    rec = {0, 0, 240, 120};
    elementos.push_back(new HUD_Element(560, 350, rec, "reintentar", false));
    BotonReintentar = elementos[16];

    rec = {0, 0, 240, 120};
    elementos.push_back(new HUD_Element(560, 480, rec, "salirrojo", false));
    BotonFinJuego = elementos[17];

    rec = {0, 0, 20, 20};
    elementos.push_back(new HUD_Element(665, 295, rec, "E", false));
    Palanca = elementos[18];

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
    int v;
    int vidas = player->getVida();
    if (vidas<=100) v = 5;if (vidas<81) v = 4;if (vidas<61) v = 3;if (vidas<41) v = 2;if (vidas<21) v = 1;
    Structs::TRectangulo rec = {10 + (110 * v), 0, 115 + (110 * v), 230};
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

void HUD::activatePalanca(){
    Palanca->setActive(true);
}

void HUD::desactivatePalanca(){
    Palanca->setActive(false);
}

void HUD::GameOver(){
    GOver->setActive(true);
    BotonReintentar->setActive(true);
    BotonFinJuego->setActive(true);
}

bool HUD::comprobarReintentar(){
    return BotonReintentar->comprobarEncima();
}

void HUD::clean(){
    Vida             = nullptr;
    Balas            = nullptr;
    Leyenda          = nullptr;
    LeyendaQ         = nullptr;
    LeyendaShift     = nullptr;
    Rayo             = nullptr;
    Golpe            = nullptr;
    Sigilo           = nullptr;
    Tarjeta          = nullptr;
    AvisoTarjeta     = nullptr;
    AvisoMunicion    = nullptr;
    AvisoAceite      = nullptr;
    AvisoNotTarjeta  = nullptr;
    AvisoNotMunicion = nullptr;
    GOver            = nullptr;
    BotonReintentar  = nullptr;
    BotonFinJuego    = nullptr;

    player = nullptr;

    std::vector<HUD_Element*>::iterator curTrg;
    for (curTrg = elementos.begin(); curTrg != elementos.end(); ++curTrg)
    {
        delete *curTrg;
    }

    elementos.clear();
}
