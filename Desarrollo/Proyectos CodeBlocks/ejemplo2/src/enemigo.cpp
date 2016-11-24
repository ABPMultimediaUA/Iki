#include "../Headers/enemigo.h"


    void enemigo::inicialiazar(int t)
    {
        estado = 0;
        tipo = t;
        sospecha = 0.0;
        posicion = core::vector3df(35,0,35); //Meter en interfaz
        puntoInteres = core::vector3df(0,0,0); //Meter en interfaz
        //modelo = smgr->addCubeSceneNode(5); //Meter en interfaz
    }

    int enemigo::getEstado()
    {
        return estado;
    }

    core::vector3df enemigo::getPosicion() //Meter en interfaz
    {
        return posicion;
    }

    core::vector3df enemigo::getPunto() //Meter en interfaz
    {
        return puntoInteres;
    }

    void enemigo::setPosicion(core::vector3df este) //Meter en interfaz
    {
        posicion = este;
    }

    void enemigo::setPunto(core::vector3df este) //Meter en interfaz
    {
        puntoInteres = este;
    }

    float enemigo::getSospecha()
    {
        return sospecha;
    }

    void enemigo::patrullar()
    {

    }
    void enemigo::sospechar(core::vector3df posicionProta)
    {

    }
    void enemigo::atacar(core::vector3df posicionProta)
    {

    }

    //Funcionamiento maquina de estados

    int enemigo::maquinaEstados(core::vector3df posicionProta)
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