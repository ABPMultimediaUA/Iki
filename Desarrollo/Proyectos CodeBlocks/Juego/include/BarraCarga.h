#ifndef BARRACARGA_H
#define BARRACARGA_H

//#include "winalleg.h"
//#include <allegro.h>

class BarraCarga
{
    private:
         BITMAP *imagen;
         // posicion donde mostrarlo
         int x,y;
         // numero total de partes en el que se divide la barra de progreso
         int total_partes;
     public:
         // inicializa los valores necesarios para la barra
         void Inicia( BITMAP* _imagen, int _x, int _y, int _total_partes );
         // muestra la barra de progreso segun el valor c
         void Progreso( int c );
};

#endif // BARRACARGA_H
