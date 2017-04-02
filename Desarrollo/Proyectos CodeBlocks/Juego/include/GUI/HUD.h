#ifndef HUD_H
#define HUD_H

#include "HUD_Element.h"

class Player;

class HUD
{
    public:
        HUD();
        ~HUD();

        void inicializar_HUD();
        void draw();

        void actualizarBalas();
        void actualizarVidas();
        //void actualizarPosicionEnemies();

    protected:

    private:
        std::vector<HUD_Element*> elementos;
        //std::vector<HUD_Element*> enemies;

        HUD_Element* Vida;
        HUD_Element* Balas;
        HUD_Element* Leyenda;
        HUD_Element* Rayo;

        Player* player;
};

#endif // HUD_H
