#ifndef TMOTORTAG_H
#define TMOTORTAG_H

#include "TNodo.h"
#include "TTransform.h"
#include "TLuz.h"
#include "TMalla.h"
#include "TCamara.h"
#include "TGestorRecursos.h"

class TMotorTAG
{
    public:
        TMotorTAG();
        virtual ~TMotorTAG();
        TNodo *crearNodo(TNodo * padre, TEntidad *ent);
        TTransform *crearTransform();
        TCamara *crearCamara();
        TLuz *crearLuz();
        TMalla *crearMalla(char *fichero);
        int registrarCamara(TNodo* nod);
        int registrarLuz(TNodo* nod);
        void setCamaraActiva(int i);
        void setCamaraApagada(int i);
        void setLuzActiva(int i);
        void setLuzApagada(int i);
        void draw();
        //Metodos para el regsitro y manejo de las camaras, luces y viewports.

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
