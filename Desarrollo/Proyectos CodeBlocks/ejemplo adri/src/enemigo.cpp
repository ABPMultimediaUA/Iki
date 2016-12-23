#include "Enemigo.h"
#include <Box2D/Box2D.h>



Enemigo::Enemigo()
{
    //ctor
}

Enemigo::~Enemigo()
{
    //dtor
}

void Enemigo::inicialiazar(int t, int ID,scene::ISceneManager* smgr, core::vector3df p){
/*
    tam= 5;

    mura1 = smgr->getGeometryCreator()->createCubeMesh(core::vector3df(50.f, 10.f, 10.f));
    muro1 = smgr->addMeshSceneNode(mura1);
    smgr->getMeshManipulator()->setVertexColors(muro1->getMesh(),video::SColor(0, 0, 0, 0));
    //modelo->setMaterialFlag(video::EMF_LIGHTING, false);
    //modelo->setMaterialTexture( 0, driver->getTexture("texturas/metal.png") );
    //modelo->setMaterialType( video::EMT_SOLID );
    muro1->setPosition(core::vector3df(0,0,20));


    b2BodyDef bodyDef;
    bodyDef.type= b2_staticBody;
    bodyDef.position.Set(0, 20);
    iworld= World::Instance();
    body2= iworld->getWorld()->CreateBody(&bodyDef);

    b2PolygonShape bodyShape;
    bodyShape.SetAsBox((50/2)+0.5, (10/2)+0.5);
    body2->CreateFixture(&bodyShape, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyShape;
    fixtureDef.friction = 10.5f;
    fixtureDef.restitution  = 0.9f;
    fixtureDef.density  = 10.f;
    body2->CreateFixture(&fixtureDef);
*/
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

        smgr1 = smgr;

       /* tam= 4;
        mura1 = smgr->getGeometryCreator()->createCubeMesh(core::vector3df(1.f, 3.f, 1.f));
        modelo = smgr->addMeshSceneNode(mura1);
        smgr->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(0, 0, 0, 0));
        modelo->setPosition(core::vector3df(0,0,20));
        cuboEnemigo = modelo->getPosition();*/

        b2BodyDef bodyDef;
        bodyDef.type= b2_staticBody;
        bodyDef.position.Set(40, -10);
        iworld= World::Instance();
        body2= iworld->getWorld()->CreateBody(&bodyDef);

        b2PolygonShape bodyShape;
        bodyShape.SetAsBox((50/2)+0.5, (10/2)+0.5);
        body2->CreateFixture(&bodyShape, 1.0f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &bodyShape;
        fixtureDef.friction = 10.5f;
        fixtureDef.restitution  = 0.9f;
        fixtureDef.density  = 10.f;
        body2->CreateFixture(&fixtureDef);
}


    /*
    void Enemigo::setPosition(core::vector3df vec){
        modelo->setPosition(core::vector3df(vec.X, 0, vec.Z));
    }*/

    b2Body* Enemigo::getBody(){
        return body2;
    }

    void Enemigo::setCuboEnemigo(core::vector3df cb){
        cuboEnemigo = cb;
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
    void Enemigo::proteger(){ //GIRAR ALREDEDOR DEL ALIADO
        cuboEnemigo += direccionHaciaAliado.normalize() * avMovement;
        posicion = cuboEnemigo;
    }
    void Enemigo::escanear(){
        time=tiempo.getTime();
        tiempoEscaneando=(time-reloj);
            if (tiempoEscaneando < 3.0){
                if(tiempoEscaneando*100 % 5 == 0){
                    /// ESTO ESTA MUY RARO
                    if (sospecha < 99)
                        //sospecha+=1*tiempo.getTimeFactor();
                        sospecha+=0.05*tiempo.getTimeFactor();
                    std::cout << sospecha << std::endl;
                }
            }
            else /*if (tiempoEscaneando > 3.0)*/{
                estado=3;
            }
            if (distanciaPlayer > 80){// o if (pierdo de vista al player) o
                primeraVez=true;
                //
                logica.Fuzzify(distanciaPlayer, logica.fm.vars[0]);
                logica.Fuzzify(sospecha, logica.fm.vars[1]);
                logica.InitializeRules();
                logica.CalculateFAM();
                float val = logica.Defuzzify();
                std::cout << "  " << val << std::endl;

                if (val <= 37.5){
                    estado = 0;
                   // sospecha=0.0;
                }
                else if (val <= 45.5){
                   // sospecha=25.0;
                    puntoInteres=posicionProta;
                    estado=8;
                }
                else{
                   // sospecha = 40.0;
                    estado = 3;
                }
                //
            }

    }
    void Enemigo::matar(){
        modelo->remove();
        muerto=true;
    }
    void Enemigo::avisarCapsulas(){
    }
    void Enemigo::atacar(){

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
        smgr1->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(70, 70, 70, 0));
            patrullar();
            //Si el player se acerca sospecha
            if(distanciaPlayer<80){ // 75
                estado = 1;
            }
            //a veces se para a vigilar dependiendo de ciertas circunstancias
            break;

        case 1:
            /// ESCANEAR / SOSPECHAR ///
            smgr1->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(128, 128, 128, 0));


            if(primeraVez){
                reloj=tiempo.setMomento();
                primeraVez=false;
            }
            escanear();

            break;
        case 2: //VIGILAR
            smgr1->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(0, 0, 0, 0));
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
            smgr1->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(0, 0, 255, 0));
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
            smgr1->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(255, 0, 0, 0));
            sospecha = 0.0;
            perseguir();
            if(distanciaPlayer>80){
                puntoInteres = posicionProta;
                estado = 8;
            }
            if(distanciaPlayer<5){
                estado=7;
            }
            //si esta a rango ataca
            //si lo pierde de vista, vuelve a la patrulla
            break;
        case 7: //ATACAR
            if(distanciaPlayer<5){
                smgr1->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(50, 20, 50, 0));
                atacar();
            }
            else{
                estado=6;
            }
            break;
        case 8: //INSPECCIONAR
            smgr1->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(255, 255, 0, 0));
            inspeccionar();
            if (distanciaPlayer<=80){
                estado = 3;
            }
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

    void Enemigo::update(core::vector3df cuboProta, Time temps, Enemigo *aliados[3])
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
            direccionHaciaProta=cuboProta-posicion;
            maquinaEstados();
            posicionProta=cuboProta;
        }
        if(mensajePendiente){
            //aqui pues deberiamos tener un destinario, de momento solo tenemos mensaje entre la medio y el guardia y por eso es asi
            aliados[0]->setEstado(mensajeEstado);
            mensajePendiente=false;
        }
    }
