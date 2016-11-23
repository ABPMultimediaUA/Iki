#include "Enemigo.h"

    void inicialiazar(int t)
    {
        estado = 0;
        tipo = t;
        sospecha = 0.0;
        posicion = core::vector3df(35,0,35); //Meter en interfaz
        puntoInteres = core::vector3df(0,0,0); //Meter en interfaz
    }

    int getEstado()
    {
        return estado;
    }

    core::vector3df getPosicion() //Meter en interfaz
    {
        return posicion;
    }

    core::vector3df getPunto() //Meter en interfaz
    {
        return puntoInteres;
    }

    void setPosicion(core::vector3df este) //Meter en interfaz
    {
        posicion = este;
    }

    void setPunto(core::vector3df este) //Meter en interfaz
    {
        puntoInteres = este;
    }

    float getSospecha()
    {
        return sospecha;
    }

    void patrullar()
    {

    }
    void sospecha(core::vector3df posicionProta)
    {

    }
    void atacar(core::vector3df posicionProta)
    {

    }

    //Funcionamiento maquina de estados

    int maquinaEstados(core::vector3df posicionProta)
    {
        switch (estado)
        {
        case 0:
            //patrullar();
            if(posicion.getDistanceFrom(posicionProta)<30)
            {
                sospecha++;
            }
            if(sospecha >= 100.0)
            {
                //acciones de la transicion 1-2
                //...
                estado = 1;
            }
            break;
        case 1:
            //sospechar(posicionProta);
            if(posicion.getDistanceFrom(puntoInteres) == 0)
            {
                if(posicion.getDistanceFrom(posicionProta) < 40)
                {
                    sospecha++;
                }
                else if(posicion.getDistanceFrom(posicionProta) > 30)
                {
                    sospecha--;
                }
            }
            if(sospecha < 50.0)
            {
                //acciones de la transicion2-1
                //...
                estado = 0;
                sospecha = 0.0;
            }
            else if(sospecha >= 200.0)
            {
                //acciones de la transicion2-3
                //...
                estado = 2;
            }
            break;
        case 2:
            //atacar(posicionProta);
            break;
        default:
            estado = 3;
            break;

        }
        return estado;
    }
