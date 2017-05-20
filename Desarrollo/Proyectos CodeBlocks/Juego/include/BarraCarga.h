/*#ifndef BARRACARGA_H
#define BARRACARGA_H

#include "Structs.h"
#include <allegro.h>

class BarraCarga
{
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
#include<stdio.h>
#include<conio.h>
#include <windows.h>

void gotoxy(int x,int y){                          ///Inicio funcion (x,y)
      HANDLE hcon;                                  ///
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);       ///
      COORD dwPos;                                  ///
      dwPos.X = x;                                  ///
      dwPos.Y= y;                                   ///
      SetConsoleCursorPosition(hcon,dwPos);         ///
 }

int main()
{
 int x,y,i,z,a;
 gotoxy(35,10);
 printf("CARGANDO");


 for(i=1; i<90; i++)
 {
  gotoxy(i,13);
  printf("%c",177);

  for(x=50;x<70;x++){
   for(y=1;y<70;y++){
    gotoxy(y,24);
   }
  }
 }
 printf("\n \n Carga Completa, puede salir presionando cualquier tecla \n");
 getch();
}﻿*/

#endif // BARRACARGA_H
