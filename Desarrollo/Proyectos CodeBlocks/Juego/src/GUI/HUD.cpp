#include "GUI/HUD.h"
#include "Fachada/Image.h"

#include "EntityManager.h"
#include "Player.h"

HUD::HUD()
{
    Vida    = nullptr;
    Balas   = nullptr;
    Leyenda = nullptr;
    Rayo    = nullptr;

    player  = nullptr;
    //player  = static_cast<Player*>(EntityManager::Instance()->getEntities()[0]);
}

HUD::~HUD()
{
    delete Vida;
    delete Balas;
    delete Leyenda;
    delete Rayo;
    delete player;
}

void HUD::inicializar_HUD(){

    player = static_cast<Player*>(EntityMgr->getEntityByID(0));

    ///Vida del prota
    Structs::TRectangulo rec = {450, 0, 605, 250};
    elementos.push_back(new HUD_Element(10, 10, rec, "vidaprota", true));
    Vida = elementos[0];

    ///Imagen del rayo
    rec = {0, 0, 110, 109};
    elementos.push_back(new HUD_Element(1240, 585, rec, "lasertocar", true));
    Rayo = elementos[1];

    ///Descripcion del rayo
    rec = {0, 0, 429, 164};
    elementos.push_back(new HUD_Element(920, 435, rec, "leyendalaser", false));
    Leyenda = elementos[2];

    ///Balas del rayo
    rec = {85, 0, 98, 17};
    elementos.push_back(new HUD_Element(1035, 460, rec, "numerobalas", false));
    Balas = elementos[3];

    /*vector<GameEntity*> vec = EntityMgr->getEntities();
    for(size_t i = 0; i < vec.size() - 1; i++){
        rec = {0, 0, 35, 50};
        elementos.push_back(new HUD_Element(vec[i]->getPosition().X, vec[i]->getPosition().Z, rec, "preguntavacia", true));
        enemies.push_back(elementos[i+4]);
    }*/
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

/*void HUD::actualizarPosicionEnemies(){

    vector<GameEntity*> vec = EntityMgr->getEntities();

    for(size_t i = 0; i < enemies.size(); i++){
        enemies[i]->setPosition(vec[i]->getPosition().X + 680, vec[i]->getPosition().Z + 384);
    }
}*/
