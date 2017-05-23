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
#include "TLinea.h"
#include "TPlano.h"
#include "TDraw2D.h"
#include "TDisplay.h"


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
        TShader *cargarShader(const std::string& filename);
        TNodo *cargarAnimacion(const std::string& filename, const unsigned int& longitud);

        TNodo *getEscena(){return escena;}
        TNodo *getCamaraActiva();

        void updateOpenGL(TNodo*);
        void updateDisplay();

        bool isOpen(){ return window.isOpen(); }

        int registrarLuz(TNodo* nod);
        int registrarCamara(TNodo* nod);

        void setLuzActiva(int i)    {l_activa[i] = true; }
        void setLuzApagada(int i)   {l_activa[i] = false;}
        void setCamaraActiva(int i) {c_activa[i] = true; }
        void setCamaraApagada(int i){c_activa[i] = false;}

        void drawLuces();
        void drawCamaras();
        void draw();
        void draw2D(int, int, TDraw2D*);

        int getWindowWidth() { return window.getWidth(); }
        int getWindowHeigth(){ return window.getHeigth(); }

        void cambiarRay(TNodo*);
        bool interseccionRayPlano(TVector &mousePosition);

        void doDisplay();
        int getTime();
        void pushStates();
        void popStates();
        void closeDevice();
        //bool Evented();

    protected:

    private:
        TNodo* escena;
        TGestorRecursos* gestorRecursos;
        TDisplay window;
        TShader* shader;
        TLinea ray;
        TPlano plane;

        vector<bool> l_activa, c_activa;
        vector<TNodo*> luces;
        vector<TNodo*> camaras;

        int flag = 0;

        //Atributos para mantenimiento de las camaras, luces y viewports.
};

#endif // TMOTORTAG_H
