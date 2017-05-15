#ifndef TMOTORTAG_H
#define TMOTORTAG_H

#include "TShader.h"
#include "TNodo.h"
#include "TTransform.h"
#include "TLuz.h"
#include "TCamara.h"
#include "TMalla.h"
#include "TGestorRecursos.h"
#include "TAnimacion.h"
#include <SFML/Graphics.hpp>


class TMotorTAG
{
    public:
        TMotorTAG();
        virtual ~TMotorTAG();

        TNodo *crearNodo(TNodo *padre, TEntidad *ent);
        TTransform *crearTransform();
        TLuz *crearLuz();
        TNodo *crearCamara(const vec3& pos, float grad, int anch, int alt, float cer, float lej);
        TNodo *crearMalla(const std::string& filename);
        TShader cargarShader(const std::string& filename);
        TNodo *cargarAnimacion(const std::string& filename, const unsigned int& longitud);

        TNodo *getEscena(){return escena;}
        TNodo *getCamaraActiva();

        bool run();

        int registrarLuz(TNodo* nod);
        int registrarCamara(TNodo* nod);

        void setLuzActiva(int i)    {l_activa[i] = true; }
        void setLuzApagada(int i)   {l_activa[i] = false;}
        void setCamaraActiva(int i) {c_activa[i] = true; }
        void setCamaraApagada(int i){c_activa[i] = false;}

        void drawLuces();
        void drawCamaras();
        void draw();

    protected:

    private:
        TNodo* escena;
        TGestorRecursos* gestorRecursos;
        TDisplay window;
        TShader shader;

        vector<bool> l_activa, c_activa;
        vector<TNodo*> luces;
        vector<TNodo*> camaras;

        //Atributos para mantenimiento de las camaras, luces y viewports.
};

#endif // TMOTORTAG_H
