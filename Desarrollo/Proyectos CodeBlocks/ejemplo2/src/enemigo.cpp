#include "../include/Enemigo.h"



    void Enemigo::inicialiazar(int ID, int t, scene::ISceneManager* smgr,core::vector3df p)
    {
        id=ID;
        estado = 0;
        vida=100;
        direccion = 0;
        tipo = t;
        sospecha = 0.0;
        posicion = p; //Meter en interfaz
        puntoInteres = core::vector3df(0,0,0); //Meter en interfaz
        modelo = smgr->addCubeSceneNode(5); //Meter en interfaz
        modelo->setMaterialFlag(video::EMF_LIGHTING, false); //Meter en el interfaz
        modelo->setPosition(posicion); //Meter en el interfaz
        cuboEnemigo = modelo->getPosition();
        tiempoVigilando = 0.0;
        tiempoEscaneando = 0;
        avMovement = 0.0;
        primeraVez=true;
        time=0.0;
        mensajePendiente=false;
        muerto=false;
        hayAliado=false;
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
    void Enemigo::setEstado(int este)
    {
        estado=este;
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

    void Enemigo::patrullar()
    {
    switch(direccion)
        {
            case 0: //Movimiento hacia arriba
                if(cuboEnemigo.getDistanceFrom(posicionInicial) <= 20){
                    cuboEnemigo.X -= avMovement;
                }else{
                    direccion = 1;
                    posicionInicial = cuboEnemigo;
                }
                break;

            case 1: //Movimiento hacia la derecha
                if(cuboEnemigo.getDistanceFrom(posicionInicial) <= 20){
                    cuboEnemigo.Z += avMovement;
                }else{
                    direccion = 2;
                    posicionInicial = cuboEnemigo;
                }
                break;

            case 2:
                if(cuboEnemigo.getDistanceFrom(posicionInicial) <= 20){
                    cuboEnemigo.X += avMovement;
                }else{
                    direccion = 3;
                    posicionInicial = cuboEnemigo;
                }
                break;

            case 3:
                if(cuboEnemigo.getDistanceFrom(posicionInicial) <= 20){
                    cuboEnemigo.Z -= avMovement;
                }else{
                    direccion = 0;
                    posicionInicial = cuboEnemigo;
                }
                break;
        }
        posicion = cuboEnemigo;
    }
    void Enemigo::inspeccionar(){
          if(cuboEnemigo.getDistanceFrom(puntoInteres) != 0){
                    cuboEnemigo += ((puntoInteres) - (cuboEnemigo)).normalize() * avMovement;
                    posicion = cuboEnemigo;
                }
                if(cuboEnemigo.getDistanceFrom(puntoInteres) <= 0.1){
                    cuboEnemigo = puntoInteres;
                    posicion = cuboEnemigo;
                }
    }
    void Enemigo::vigilar(){
        //devuelve tiempo en s
        time=tiempo.getTime();
        tiempoVigilando=(time-reloj);
        //printf("tiempoVigilando:  %0.2f \n", tiempoVigilando);
        if(tiempoVigilando < 3.0){
            modelo->setRotation(vector3df(0,30,0));
        }
        else if(tiempoVigilando>= 3.0 && tiempoVigilando<= 6.0){
            modelo->setRotation(vector3df(0,-30,0));
        }
        else if(tiempoVigilando>6.0){
            modelo->setRotation(vector3df(0,0,0));
        }

    }
    void Enemigo::sospechar(core::vector3df posicionProta)
    {

    }
    void Enemigo::curar(Enemigo aliado)
    {

    }
    void Enemigo::perseguir(){
        cuboEnemigo += direccionHaciaProta.normalize() * avMovement;
        posicion = cuboEnemigo;
    }
    void Enemigo::pedirAyuda(){
        cuboEnemigo += direccionHaciaAliado.normalize() * avMovement;
        posicion = cuboEnemigo;
    }
    void Enemigo::proteger(){
        cuboEnemigo += direccionHaciaAliado.normalize() * avMovement;
        posicion = cuboEnemigo;
    }
    void Enemigo::escanear(){
        time=tiempo.getTime();
        tiempoEscaneando=(time-reloj);
        //printf("tiempoVigilando:  %0.2f \n", tiempoVigilando);
        if(tiempoEscaneando<3.0){
            if(tiempoEscaneando % 5 == 0){
                sospecha+=0.1;
                std::cout << sospecha << std::endl;
            }
        }
    }
    void Enemigo::matar(){
        modelo->remove();
        muerto=true;
    }
    void Enemigo::avisarCapsulas(){
    }
    float Enemigo::getVida(){
        return vida;
    }

    //Funcionamiento maquina de estados

    int Enemigo::maquinaEstados()
    {
        switch (estado)
        {
        case 0:
            patrullar();
            //Si el player se acerca sospecha
            if(distanciaPlayer<30){
                estado = 1;
            }
            //a veces se para a vigilar dependiendo de ciertas circunstancias
            break;

        case 1:
            /// ESCANEAR / SOSPECHAR ///
            if(primeraVez){
            reloj=tiempo.setMomento();
            primeraVez=false;
            }
            if (tiempoEscaneando < 3.0){
                escanear();
            }
            else if (tiempoEscaneando == 3.0){
                estado=3;
            }

            if (distanciaPlayer > 50){// o if (pierdo de vista al player) o
                primeraVez=true;
                //
                logica.Fuzzify(distanciaPlayer, logica.fm.vars[0]);
                logica.Fuzzify(sospecha, logica.fm.vars[1]);
                logica.InitializeRules();
                logica.CalculateFAM();
                float val = logica.Defuzzify();
                std::cout << "  " << val << std::endl;
                if (val <= 37.5)
                    estado = 0;
                else if (val <= 67.5){
                    puntoInteres=posicionProta;
                    estado=8;
                }
                else
                    estado = 3;
                //

            }

            //DISTANCIA PLAYER (CERCA,MEDIA,LEJOS)

            //VELOCIDAD PLAYER (0,1,2)  //////SI LA VELOCIDAD ES 0 EL RUIDO ES 0
                                        //////SI LA VELOCIDAD ES 1 o 2, EL RUIDO DEPENDE DE LA DISTANCIA (SIEMPRE)
                                                                        //RUIDO PLAYER (BAJO,MEDIO,ALTO)

            //NIVEL DE SOSPECHA (BAJO,MEDIO,ALTO) o velocidad de subida

           /* if(distanciaPlayer < 30)//El player ha entrado en el rango de sensores
            {
                /// AQUI AUMENTARA PROGRESIVAMENTE LA SOSPECHA
                //std::cout << "aumentando sospecha" << std::endl;

            }else{//El player ha salido del rango
                /// AQUI SE CAMBIA A UN ESTADO DEPENDIENDO DEL NIVEL DE SOSPECHA
                //std::cout << "escaneo terminado // interrumpido" << std::endl;
                estado = 0;

            }*/
            break;
        case 2: //VIGILAR
            if(primeraVez){
            reloj=tiempo.setMomento();
            primeraVez=false;
            }
            if (tiempoVigilando < 8.0){
            vigilar();
            }
            else{
                primeraVez=true;
                estado=0;
            }
            break;
        case 3: //COMBATE/ALARMA/DECISION MEDICO
                if(tipo == 0){
                    estado=6;
                    //si el prota esta a rango ataca
                    //sino persigue
                }
                else if(tipo == 1){
                    //mantiene poscion y suena
                    posicion = cuboEnemigo;
                    puntoInteres=posicionProta;
                    avisarCapsulas();
                }
                else if(tipo == 2){
                        if(hayAliado)
                            estado=4;
                        else
                            estado=5;
                   //si hay enemigo pedir ayuda, cuando le encuentre avisarle y curarle o perseguirle;
                   //si no hay huir, cuando haya huido volver a patrullar
                }
            break;
        case 4: //PEDIR AYUDA
            pedirAyuda();
            //fabs es para valor absoluto
            if( fabs(posicion.X - posicionAliado.X) < 5 && fabs(posicion.Z - posicionAliado.Z) < 5){
                mensajePendiente=true;
                mensajeEstado=6;
                estado=9;
            }
            //cuando lo encuentra, lo cura si es necesario y lo protege
            break;
        case 5: //HUIR
            break;
        case 6: //PERSEGUIR
            perseguir();
            if(distanciaPlayer>60){
                estado = 0;
            }
            //si esta a rango ataca
            //si lo pierde de vista, vuelve a la patrulla
            break;
        case 7: //ATACAR
            break;
        case 8: //INSPECCIONAR
            inspeccionar();
            if(posicion.getDistanceFrom(puntoInteres) == 0)
            {
                estado=0;
            }

            break;
        case 9: //PROTEGER
            proteger();
            break;
        case 10: //MUERTO
            break;
        default:
            estado = 11;
            break;

        }
        return estado;
    }

    void Enemigo::update(core::vector3df direccionProta, core::vector3df cuboProta, Time temps, Enemigo *aliados[3])
    {
        tiempo = temps;

        if(tipo==2){
        //habria que comprobar el tipo de aliado y si es guardia guardarnos las posiciones, en este caso sabemos que es el 0
        posicionAliado=aliados[0]->getPosicion();
        direccionHaciaAliado= (posicionAliado-posicion);
        hayAliado=true;
        }

        if(modelo)
        {
            avMovement = 15.f * tiempo.getTimeFactor();
            distanciaPlayer = posicion.getDistanceFrom(cuboProta);
            direccionHaciaProta=direccionProta;
            maquinaEstados();
            posicionProta=cuboProta;
        }
        if(mensajePendiente){
            //aqui pues deberiamos tener un destinario, de momento solo tenemos mensaje entre la medio y el guardia y por eso es asi
            aliados[0]->setEstado(mensajeEstado);
            mensajePendiente=false;
        }
    }

