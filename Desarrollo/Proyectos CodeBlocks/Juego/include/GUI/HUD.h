#ifndef HUD_H
#define HUD_H

#include "HUD_Element.h"

class Player;

class HUD
{
    public:
        static HUD* getInstance() {
            static HUD singleton;
            return &singleton;
        };

        ~HUD();

        void inicializar_HUD();
        void draw();

        void actualizarBalas();
        void actualizarVidas();

        void rayoUsed();
        void rayoNotUsed();

        void activateTarjeta();
        void desactivateTarjeta();

        void activateMunicion();

    protected:

    private:
        HUD();
        std::vector<HUD_Element*> elementos;

        HUD_Element* Vida;
        HUD_Element* Balas;
        HUD_Element* Leyenda;
        HUD_Element* Rayo;
        HUD_Element* Tarjeta;
        HUD_Element* AvisoTarjeta;
        HUD_Element* AvisoMunicion;

        Player* player;

        f32 tiempo_con_aviso;
};

#endif // HUD_H
