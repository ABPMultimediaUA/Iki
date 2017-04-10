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
        void comprobarAvisos();

        void rayoUsed();
        void rayoNotUsed();

        void sigiloUsed();
        void sigiloNotUsed();

        void activateTarjeta();
        void desactivateTarjeta();

        void activateMunicion();
        void activateAceite();

        void activateNotMunicion();
        void activateNotTarjeta();

        void GameOver();

    protected:

    private:
        HUD();
        std::vector<HUD_Element*> elementos;

        HUD_Element* Vida;
        HUD_Element* Balas;
        HUD_Element* Leyenda;
        HUD_Element* LeyendaQ;
        HUD_Element* LeyendaShift;
        HUD_Element* Rayo;
        HUD_Element* Golpe;
        HUD_Element* Sigilo;
        HUD_Element* Tarjeta;
        HUD_Element* AvisoTarjeta;
        HUD_Element* AvisoMunicion;
        HUD_Element* AvisoAceite;
        HUD_Element* AvisoNotTarjeta;
        HUD_Element* AvisoNotMunicion;
        HUD_Element* GOver;
        HUD_Element* BotonFinJuego;

        Player* player;

        f32 tiempo_con_aviso;
};

#endif // HUD_H
