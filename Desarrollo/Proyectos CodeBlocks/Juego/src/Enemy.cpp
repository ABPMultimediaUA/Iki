#include "../include/Enemy.h"


    void Enemy::inicialiazar(int t, scene::ISceneManager* smgr,core::vector3df p)
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

    int Enemy::getEstado()
    {
        return estado;
    }

    core::vector3df Enemy::getPosicion() //Meter en interfaz
    {
        return posicion;
    }

    core::vector3df Enemy::getPunto() //Meter en interfaz
    {
        return puntoInteres;
    }

    void Enemy::setPosicion(core::vector3df este) //Meter en interfaz
    {
        posicion = este;
    }

    void Enemy::setPunto(core::vector3df este) //Meter en interfaz
    {
        puntoInteres = este;
    }

    float Enemy::getSospecha()
    {
        return sospecha;
    }

    scene::IMeshSceneNode* Enemy::getModelo(){
        return modelo;
    }

    core::vector3df Enemy::getCuboEnemigo(){
        return cuboEnemigo;
    }

    void Enemy::patrullar()
    {

    }
    void Enemy::sospechar(core::vector3df posicionProta)
    {

    }
    void Enemy::atacar(core::vector3df posicionProta)
    {

    }

    //Funcionamiento maquina de estados

    int Enemy::maquinaEstados(core::vector3df posicionProta)
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
                puntoInteres = posicionProta;
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

    void Enemy::update(core::vector3df direccionProta, core::vector3df cuboProta, f32 frameDeltaTime)
    {
        if(modelo)
        {
            const f32 availableMovement = 15.f * frameDeltaTime;
            maquinaEstados(cuboProta);

            if(estado == 0)
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
            else if(estado == 1)
            {
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
            else if(estado == 2)
            {
                if(tipo == 0){
                    cuboEnemigo += direccionProta.normalize() * availableMovement;
                    posicion = cuboEnemigo;
                }
                else if(tipo == 1){
                    posicion = cuboEnemigo;
                }
            }
        }
    }
