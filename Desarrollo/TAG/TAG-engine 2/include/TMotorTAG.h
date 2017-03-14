#ifndef TMOTORTAG_H
#define TMOTORTAG_H

#include "TNodo.h"
#include "TTransform.h"
#include "TLuz.h"
#include "TCamara.h"
#include "TMalla.h"
#include "TGestorRecursos.h"

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

class TMotorTAG
{
    public:
        TMotorTAG();
        virtual ~TMotorTAG();

        TNodo *crearNodo(TNodo * padre, TEntidad *ent);
        TTransform *crearTransform();
        TLuz *crearLuz();
        TCamara *crearCamara();
        TMalla *crearMalla(const std::string& FileName);

        TNodo *getEscena(){return escena;};
        TNodo *getCamaraActiva();

        int registrarLuz(TNodo* nod);
        int registrarCamara(TNodo* nod);

        void setLuzActiva(int i)    {l_activa[i] = true; };
        void setLuzApagada(int i)   {l_activa[i] = false;};
        void setCamaraActiva(int i) {c_activa[i] = true; };
        void setCamaraApagada(int i){c_activa[i] = false;};

        void draw();

    protected:

    private:
        TNodo* escena;
        TGestorRecursos *gestorRecursos;

        vector<bool> l_activa, c_activa;
        vector<TNodo*> luces;
        vector<TNodo*> camaras;

        //Atributos para mantenimiento de las camaras, luces y viewports.
};

#endif // TMOTORTAG_H
