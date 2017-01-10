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

void Enemigo::inicialiazar(int t, int ID,scene::ISceneManager* smgr, core::vector3df p, PatrolRoute pr){

    pRuta = pr.getInicial();

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
        input.maxFraction	=	1.0f;
        tam= 5;
        estado = 0;
        vida=1;
        direccion = 0;
        tipo = t;
        sospecha = 0.0;
        creado= true;
        posicion = p; //Meter en interfaz
        puntoInteres = core::vector3df(0,0,0); //Meter en interfaz
        modelo = smgr->addCubeSceneNode(tam); //Meter en interfaz
        modelo->setMaterialFlag(video::EMF_LIGHTING, false); //Meter en el interfaz
        modelo->setPosition(posicion); //Meter en el interfaz
        modelo->setRotation(vector3df(0,0,0));

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
        bodyDef.type= b2_dynamicBody;
        bodyDef.position.Set(posicion.X, posicion.Z);
        iworld= World::Instance();
        body2= iworld->getWorld()->CreateBody(&bodyDef);

        b2PolygonShape bodyShape;
        bodyShape.SetAsBox(tam/2, tam/2);
        body2->CreateFixture(&bodyShape, 1.0f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &bodyShape;
        fixtureDef.friction = 10.5f;
        fixtureDef.restitution  = 0.9f;
        fixtureDef.density  = 10.f;
        body2->CreateFixture(&fixtureDef);

        cuboEnemigo = vector3df(body2->GetPosition().x, 0, body2->GetPosition().y);
        posicionInicial = pRuta->getPunto() - cuboEnemigo;
        angulo = atan2f((posicionInicial.Z) ,-(posicionInicial.X)) * 180.f /PI;
        modelo->setRotation(vector3df(0,angulo,0));
        rotacion=modelo->getRotation().Y;

}

void Enemigo::inicialiazar2(scene::ISceneManager* smgr){
    tam= 4;
    vida = 150;

    mura1 = smgr->getGeometryCreator()->createCubeMesh(core::vector3df(8.f, 8.f, 8.f));
    modelo = smgr->addMeshSceneNode(mura1);

    modelo->setPosition(core::vector3df(180,0,255));
    modelo->setRotation(core::vector3df(0,-45,0));

    b2BodyDef bodyDef;
    bodyDef.type= b2_staticBody;
    bodyDef.position.Set(180, 255);
    iworld= World::Instance();
    body2= iworld->getWorld()->CreateBody(&bodyDef);

    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(tam/2, tam/2);
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

    bool Enemigo::getCreado(){
        return creado;
    }

    core::vector3df Enemigo::getPosicion() //Meter en interfaz
    {
        return posicion;
    }

    core::vector3df Enemigo::getPunto() //Meter en interfaz
    {
        return puntoInteres;
    }

    //Asi se mueve con BODY

    void Enemigo::setPosicion(core::vector3df vec, core::vector3df prot){
        if(muerto){
            body2->SetTransform(b2Vec2(-1000, -1000), 0);
            modelo->setPosition(vector3df(body2->GetPosition().x, 0, body2->GetPosition().y));
        }
        else{
            body2->SetTransform(b2Vec2(vec.X, vec.Z), 0);
            modelo->setPosition(vector3df(body2->GetPosition().x, 0, body2->GetPosition().y));
        }
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
        if(id == 0){
            if(cuboEnemigo.getDistanceFrom(pRuta->getPunto()) > 5.f){
                //rotar el body tambien
                cuboEnemigo += posicionInicial.normalize()*avMovement;
                //std::cout << "Distancia: " << cuboEnemigo.getDistanceFrom(pRuta->getPunto()) << std::endl;
                //std::cout << "Punto (X,Z): " << posicionInicial.X << "," << posicionInicial.Z << std::endl;

            }
            else{
                pRuta = pRuta->getNext();
                posicionInicial = pRuta->getPunto() - cuboEnemigo;
                angulo = atan2f((posicionInicial.Z) ,-(posicionInicial.X)) * 180.f /PI;
                modelo->setRotation(vector3df(0,rotacion+angulo,0));
                rotacion=modelo->getRotation().Y;
                std::cout << "Rotacion: " << rotacion  << std::endl;
                std::cout << "Angulo: " << angulo  << std::endl;
            }
        posicion = cuboEnemigo;
        }
    }

    bool Enemigo::comprobarPunto(b2Vec2 v){
        bool si = false;
        si = body2->GetFixtureList()->TestPoint(v);

        return si;
    }

    void Enemigo::quitarVida(){
        --vida;
        //std::cout << vida;
        if(vida <= 0){
            muerto = true;
            modelo->setPosition(core::vector3df(1000,0,0));
            body2->SetTransform(b2Vec2(1000,0),0);
        }
    }

    void Enemigo::setDanyado(bool b){
        danyado = b;
    }

    bool Enemigo::getDanyado(){
        return danyado;
    }

    bool Enemigo::getMuerto(){
        return muerto;
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
            modelo->setRotation(vector3df(0,rotacion+30,0));
        }
        else if(tiempoVigilando>= 3.0 && tiempoVigilando<= 6.0){
            modelo->setRotation(vector3df(0,rotacion-30,0));
        }
        else if(tiempoVigilando>6.0){
            modelo->setRotation(vector3df(0,rotacion,0));
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
        if(fabs(posicion.X - posicionAliado.X) > 2 && fabs(posicion.Z - posicionAliado.Z) > 2){
            cuboEnemigo += direccionHaciaAliado.normalize() * avMovement;
            posicion = cuboEnemigo;
        }
    }
    bool Enemigo::seeWhereIgo(){
        devolver=false;
        /*if()//mira a la izquierda
        {
            if(player->getPosicionProta().X > posicion.X){
                devolver=true;
            }
        }
        if()//mira a la dercha
        {
            if(player->getPosicionProta().X < posicion.X){
                devolver=true;
            }
        }*/
        if(rotacion==0)//mira hacia arriba
        {
            if(player->getPosicionProta().Z < posicion.Z){
                devolver=true;
            }
        }
        if(rotacion==90)//mira hacia abajo
        {
            if(player->getPosicionProta().Z > posicion.Z){
                devolver=true;
            }
        }
        return devolver;
    }
    void Enemigo::escanear(){
        time=tiempo.getTime();
        tiempoEscaneando=(time-reloj);
            if(tiempoEscaneando < 3.0 && sospecha < 99 && distanciaPlayer<80 && !getMuro()&& seeWhereIgo()){
            //if(tiempoEscaneando < 3.0 && sospecha < 99 && distanciaPlayer<80 && !getMuro()){
                    /// ESTO ESTA MUY RARO Y ES MU DURO
                        //sospecha+=1*tiempo.getTimeFactor();
                        sospecha+=30*tiempo.getTimeFactor();
                    //std::cout << sospecha << std::endl;
            }
            else { // Cuando termina de escanear
                primeraVez=true;
                //logica difusa
                logica.Fuzzify(distanciaPlayer, logica.fm.vars[0]);
                logica.Fuzzify(sospecha, logica.fm.vars[1]);
                logica.InitializeRules();
                logica.CalculateFAM();
                float val = logica.Defuzzify();
                std::cout << "  " << val << std::endl;

                if (val <= 25.0){
                    estado = 0;
                }
                else if (val <= 55){
                    puntoInteres=posicionProta;
                    estado=8;
                }
                else {
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
        if(muerto==false){
        switch (estado)
        {
        case 0:
        smgr1->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(70, 70, 70, 0));
            patrullar();
            //Si el player se acerca sospecha
            if(distanciaPlayer<80){ // 75

                    if (!getMuro()&& seeWhereIgo())
                        estado = 1;
            }
            //a veces se para a vigilar dependiendo de ciertas circunstancias
            break;

        case 1:
            /// ESCANEAR / SOSPECHAR ///
            smgr1->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(128, 128, 128, 0));


            if(primeraVez){
                //sospecha=0;
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
            rotacion=modelo->getRotation().Y;
            }
            if (tiempoVigilando < 8.0){
            vigilar();
            }
            else{
                primeraVez=true;
                tiempoVigilando=0.0;
                estado=0;
                posicionInicial = pRuta->getPunto() - cuboEnemigo;
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
            if(distanciaPlayer>120){
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
            smgr1->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(255, 255, 255, 0));
            inspeccionar();
            if (distanciaPlayer<=80){
                if (!getMuro())
                    estado = 3;
            }
            if(posicion.getDistanceFrom(puntoInteres) == 0)
            {
                estado=2;
            }

            break;
        case 9: //PROTEGER
            if(aliado->getEstado()==0){
                estado=0;
                posicionInicial = pRuta->getPunto() - cuboEnemigo;
            }
            proteger();
            break;
        case 10: //MUERTO
            break;
        default:
            estado = 11;
            break;

        }
    }
        return estado;
    }

    void Enemigo::update(core::vector3df cuboProta, Time temps, Enemigo *aliados[5])
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
            aliado=aliados[0];
        }
    }

    void Enemigo::setMuro(Muros* murito, Player *prota){
        player= prota;
        morito = murito;
    }

    bool Enemigo::getMuro(){
        input.p1.Set(this->getBody()->GetPosition().x, this->getBody()->GetPosition().y);	//	Punto	inicial	del	rayo
        input.p2.Set(player->getBody()->GetPosition().x, player->getBody()->GetPosition().y);	//	Punto	final	del	rayo

        if (morito->body->GetFixtureList()->RayCast(&output,	input,	0))return true;
        if (morito->body2->GetFixtureList()->RayCast(&output,	input,	0))return true;
        if (morito->body3->GetFixtureList()->RayCast(&output,	input,	0))return true;
        if (morito->body4->GetFixtureList()->RayCast(&output,	input,	0))return true;
        if (morito->body5->GetFixtureList()->RayCast(&output,	input,	0))return true;
        if (morito->body6->GetFixtureList()->RayCast(&output,	input,	0))return true;
        if (morito->body7->GetFixtureList()->RayCast(&output,	input,	0))return true;
        if (morito->body8->GetFixtureList()->RayCast(&output,	input,	0))return true;
        if (morito->body9->GetFixtureList()->RayCast(&output,	input,	0))return true;
        if (morito->body10->GetFixtureList()->RayCast(&output,	input,	0))return true;
        if (morito->body11->GetFixtureList()->RayCast(&output,	input,	0))return true;
        if (morito->body12->GetFixtureList()->RayCast(&output,	input,	0))return true;
        if (morito->body13->GetFixtureList()->RayCast(&output,	input,	0))return true;
        if (morito->body14->GetFixtureList()->RayCast(&output,	input,	0))return true;
        if (morito->body15->GetFixtureList()->RayCast(&output,	input,	0))return true;
        if (morito->body16->GetFixtureList()->RayCast(&output,	input,	0))return true;
        if (morito->body17->GetFixtureList()->RayCast(&output,	input,	0))return true;
        if (morito->body18->GetFixtureList()->RayCast(&output,	input,	0))return true;
        if (morito->body19->GetFixtureList()->RayCast(&output,	input,	0))return true;
        if (morito->body20->GetFixtureList()->RayCast(&output,	input,	0))return true;
        if (morito->body21->GetFixtureList()->RayCast(&output,	input,	0))return true;
        if (morito->body22->GetFixtureList()->RayCast(&output,	input,	0))return true;
        if (morito->body23->GetFixtureList()->RayCast(&output,	input,	0))return true;
        if (morito->body24->GetFixtureList()->RayCast(&output,	input,	0))return true;
        if (morito->body25->GetFixtureList()->RayCast(&output,	input,	0))return true;
        if (morito->body26->GetFixtureList()->RayCast(&output,	input,	0))return true;

       return false;
    }
