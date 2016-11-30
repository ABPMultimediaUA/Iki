#include "../include/Enemigo.h"


    void Enemigo::inicialiazar(int t, scene::ISceneManager* smgr,core::vector3df p)
    {
        estado = 0;
        direccion = 0;
        tipo = t;
        sospecha = 0.0;
        posicion = p; //Meter en interfaz
        puntoInteres = core::vector3df(0,0,0); //Meter en interfaz
        modelo = smgr->addCubeSceneNode(5); //Meter en interfaz
        modelo->setMaterialFlag(video::EMF_LIGHTING, false); //Meter en el interfaz
        modelo->setPosition(posicion); //Meter en el interfaz
        cuboEnemigo = modelo->getPosition();
    }

    int Enemigo::getEstado()
    {
        return estado;
    }

    core::vector3df Enemigo::getPosicion() //Meter en interfaz
    {
        return posicion;
    }

    core::vector3df Enemigo::getPunto() //Meter en interfaz
    {
        return puntoInteres;
    }

    void Enemigo::setPosicion(core::vector3df este) //Meter en interfaz
    {
        posicion = este;
    }

    void Enemigo::setPunto(core::vector3df este) //Meter en interfaz
    {
        puntoInteres = este;
    }

    float Enemigo::getSospecha()
    {
        return sospecha;
    }

    scene::IMeshSceneNode* Enemigo::getModelo(){
        return modelo;
    }

    core::vector3df Enemigo::getCuboEnemigo(){
        return cuboEnemigo;
    }


    void Enemigo::sospechar(core::vector3df posicionProta)
    {

    }
    void Enemigo::curar(Enemigo aliado)
    {

    }

    //Funcionamiento maquina de estados

    int Enemigo::maquinaEstados(core::vector3df posicionProta)
    {
        switch (estado)
        {
        case 0://PATRULLAR
            if(posicion.getDistanceFrom(posicionProta)<30)
            {
                sospecha++;
            }
            if(sospecha >= 100.0)
            {
                //acciones de la transicion 1-2
                //...
                estado = 1;
                puntoInteres = posicionProta;
            }
            break;
        case 1: //VIGILAR
            break;
        case 2: //COMBATE/ALARMA/DECISION MEDICO
            break;
        case 3: //PEDIR AYUDA
            break;
        case 4: //HUIR
            break;
        case 5: //PERSEGUIR
            break;
        case 6: //ATACAR
            break;
        case 7: //INSPECCIONAR
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
        case 8: //PROTEGER
            break;

        default:
            estado = 3;
            break;

        }
        return estado;
    }

    void Enemigo::update(core::vector3df direccionProta, core::vector3df cuboProta, f32 frameDeltaTime)
    {
        if(modelo)
        {
            const f32 availableMovement = 15.f * frameDeltaTime;
            maquinaEstados(cuboProta);

            if(estado == 0) //PATRULLAR
            {

                switch(direccion)
                {
                case 0: //Movimiento hacia arriba
                    if(cuboEnemigo.getDistanceFrom(posicionInicial) <= 20)
                    {
                        cuboEnemigo.X -= availableMovement;
                    }
                    else
                    {
                        direccion = 1;
                        posicionInicial = cuboEnemigo;
                    }
                    break;
                case 1: //Movimiento hacia la derecha
                    if(cuboEnemigo.getDistanceFrom(posicionInicial) <= 20)
                    {
                        cuboEnemigo.Z += availableMovement;
                    }
                    else
                    {
                        direccion = 2;
                        posicionInicial = cuboEnemigo;
                    }
                    break;
                case 2:
                    if(cuboEnemigo.getDistanceFrom(posicionInicial) <= 20)
                    {
                        cuboEnemigo.X += availableMovement;
                    }
                    else
                    {
                        direccion = 3;
                        posicionInicial = cuboEnemigo;
                    }
                    break;
                case 3:
                    if(cuboEnemigo.getDistanceFrom(posicionInicial) <= 20)
                    {
                        cuboEnemigo.Z -= availableMovement;
                    }
                    else
                    {
                        direccion = 0;
                        posicionInicial = cuboEnemigo;
                    }
                    break;
                }
                posicion = cuboEnemigo;
            }
            else if(estado == 1) //VIGILAR
            {

            }
            else if(estado == 2) //COMBATE/ALARMA/DECISION MEDICO
            {
                if(tipo == 0){
                    cuboEnemigo += direccionProta.normalize() * availableMovement;
                    posicion = cuboEnemigo;
                }
                else if(tipo == 1){
                    posicion = cuboEnemigo;
                }
                else if(tipo == 2){
                   //si hay enemigo pedir ayuda, cuando le encuentre avisarle y curarle o perseguirle;
                   //si no hay huir, cuando haya huido volver a patrullar
                }
            }
            else if (estado == 3){}//PEDIR AYUDA
            else if (estado == 4){}//HUIR
            else if (estado == 5){}//PERSEGUIR
            else if (estado == 6){}//ATACAR
            else if (estado == 7){ //INSPECCIONAR
                if(cuboEnemigo.getDistanceFrom(puntoInteres) != 0)
                {
                    cuboEnemigo += ((puntoInteres) - (cuboEnemigo)).normalize() * availableMovement;
                    posicion = cuboEnemigo;
                }
                if(cuboEnemigo.getDistanceFrom(puntoInteres) <= 0.1)
                {
                    cuboEnemigo = puntoInteres;
                    posicion = cuboEnemigo;
                }
            }
            else if (estado == 8){}//PROTEGER
            else if (estado == 9){}//MUERTO
        }
    }

