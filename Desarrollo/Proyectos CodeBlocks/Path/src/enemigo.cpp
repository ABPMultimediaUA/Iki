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
        id=ID;
        tam= 2;
        estado = 4;
        vida=3;
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
        input.maxFraction	=	1.0f;
        input2.maxFraction	=	1.0f;

}

   void Enemigo::setPosition(core::vector3df vec){
        modelo->setPosition(vec);
        posicion = modelo->getPosition();
    }

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
    int Enemigo::getTipo(){
        return tipo;
    }
    int Enemigo::getID(){
        return id;
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

    void Enemigo::setPosicion(){
            body2->SetTransform(b2Vec2(cuboEnemigo.X, cuboEnemigo.Z), 0);
            modelo->setPosition(vector3df(body2->GetPosition().x, 0, body2->GetPosition().y));
            posicion = modelo->getPosition();

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
            if(cuboEnemigo.getDistanceFrom(pRuta->getPunto()) >0.1){

                //rotar el body tambien
                cuboEnemigo += posicionInicial.normalize()*avMovement;
                //std::cout << "Distancia: " << cuboEnemigo.getDistanceFrom(pRuta->getPunto()) << std::endl;
                //std::cout << "Punto (X,Z): " << posicionInicial.X << "," << posicionInicial.Z << std::endl;

            }
            else{
                cuboEnemigo=pRuta->getPunto();
                pRuta = pRuta->getNext();
                posicionInicial = pRuta->getPunto() - cuboEnemigo;
                angulo = atan2f((posicionInicial.Z) ,-(posicionInicial.X)) * 180.f /PI;
                if(rotacion+angulo>360){
                    rotacion=rotacion-360;
                }
                modelo->setRotation(vector3df(0,rotacion+angulo,0));
                rotacion=modelo->getRotation().Y;
                //std::cout << "Angulo: " << angulo  << std::endl;
                //std::cout << "Rotacion: " << rotacion  << std::endl;
            }
        posicion = cuboEnemigo;
    }

    bool Enemigo::comprobarPunto(b2Vec2 v){
        bool si = false;
        si = body2->GetFixtureList()->TestPoint(v);

        return si;
    }

    void Enemigo::quitarVida(){
        if(vida>0)
        --vida;
        //std::cout << vida;
        if(vida <= 0){
            matar();
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
                }
                if(cuboEnemigo.getDistanceFrom(puntoInteres) <= 0.1){
                    cuboEnemigo = puntoInteres;
                }
         posicion = cuboEnemigo;
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
        posicion = cuboEnemigo;
    }

    void Enemigo::perseguir(){
        cuboEnemigo += direccionHaciaProta.normalize() * avMovement * 2.0;
        posicion = cuboEnemigo;

    }

    void Enemigo::proteger(){ //GIRAR ALREDEDOR DEL ALIADO
        if(fabs(posicion.X - aliado->getPosicion().X) > 2 && fabs(posicion.Z - aliado->getPosicion().Z) > 2){
            cuboEnemigo += direccionHaciaAliado.normalize() * avMovement* 2.0;
        }
        posicion = cuboEnemigo;
    }

    void Enemigo::escanear(){
        time=tiempo.getTime();
        tiempoEscaneando=(time-reloj);
            //if(tiempoEscaneando < 3.0 && sospecha < 99 && distanciaPlayer<80 && !getMuro()&& seeWhereIgo()){
            if(tiempoEscaneando < 3.0 && sospecha < 25 && distanciaPlayer<28 && !getMuro()){
                        //sospecha+=1*tiempo.getTimeFactor();
                        if (player->velocidad == 4.5f )
                            sospecha+=10*tiempo.getTimeFactor();
                        else
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
               // std::cout << "  " << val << std::endl;

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
            posicion = cuboEnemigo;
    }
    void Enemigo::matar(){
        //modelo->remove();
        muerto=true;
        estado=10;
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
            //Si el player se acerca mucho aunque este en sigilo
            if (distanciaPlayer < 4){
                    estado=1;
            }
            //Si el player se acerca sospecha

            else if(distanciaPlayer>=4 && distanciaPlayer<28){
                //std::cout << seeWhereIgo() <<"\n";
                if (!getMuro())
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
                posicionInicial = pRuta->getPunto()- cuboEnemigo;
                estado=0;

            }
            break;
        case 3: //COMBATE/ALARMA/DECISION MEDICO
            smgr1->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(0, 0, 255, 0));
                if(tipo == 0){
                    estado=6;
                }
        case 4://PRUEBAA
            smgr1->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(255, 100, 100, 0));
            if(distanciaPlayer<50){
                estado = 11;
            }
            break;
        case 6: //PERSEGUIR
            smgr1->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(255, 0, 0, 0));
            sospecha = 0.0;
            perseguir();
            if(distanciaPlayer>40){
                puntoInteres = posicionProta;
                estado = 8;
            }
            if(distanciaPlayer<2){
                estado=7;
            }
            //si esta a rango ataca
            //si lo pierde de vista, vuelve a la patrulla
            break;
        case 7: //ATACAR
            if(distanciaPlayer<2){
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
            if (distanciaPlayer<=28){
                if (!getMuro())
                    estado = 3;
            }
            if(posicion.getDistanceFrom(puntoInteres) == 0)
            {
                estado=2;
            }

            break;
        case 10: //MUERTO
            break;
        case 11: ///PRUEBA
            smgr1->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(0, 255, 0, 0));
            break;
        case 12: ///PRUEBA
            smgr1->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(0, 0, 255, 0));
            if(distanciaPlayer>=50){
                estado=4;
            }
            break;
        default:
            estado = 13;
            break;

        }
    }
        return estado;
    }

    void Enemigo::update(core::vector3df cuboProta, Time temps, Enemigo *aliados[7])
    {
        //std::cout << "PosiconAliado(x,y)" << posicionAliado.X<<","<<posicionAliado.Z << std::endl;
        tiempo = temps;
        if(modelo)
        {
            avMovement = 9.5f * tiempo.getTimeFactor();
            distanciaPlayer = posicion.getDistanceFrom(cuboProta);
            direccionHaciaProta=cuboProta-posicion;
            maquinaEstados();
            posicionProta=cuboProta;
        }
    }
    void Enemigo::moverBody(core::vector3df vec){

    double modulo = sqrt((vec.X*vec.X) + (vec.Z*vec.Z));
    if(modulo != 0){
        vec.X = (vec.X / modulo) * velocidad * 0.70;
        vec.Z = (vec.Z / modulo) * velocidad * 0.70;
    }

    body2->SetLinearVelocity(b2Vec2(vec.X, vec.Z));
}


    void Enemigo::setMuro(Map* murito, Player *prota){
        player= prota;
        morito = murito;
    }

    bool Enemigo::getMuro(){
        input.p1.Set(this->getBody()->GetPosition().x, this->getBody()->GetPosition().y);	//	Punto	inicial	del	rayo
        input.p2.Set(player->getBody()->GetPosition().x, player->getBody()->GetPosition().y);	//	Punto	final	del	rayo

        if (morito->puertas->at(0)->body->GetFixtureList()->RayCast(&output,	input,	0))
            return true;
        else if (morito->puertas->at(1)->body->GetFixtureList()->RayCast(&output,	input,	0))
            return true;

            for (int i = 0; i < morito->muros->size(); i++) {
                if (morito->muros->at(i)->body->GetFixtureList()->RayCast(&output,	input,	0))
                    return true;

            }

       return false;
    }
    bool Enemigo::isPathObstructured(vector3df destino){
        input2.p1.Set(this->getBody()->GetPosition().x, this->getBody()->GetPosition().y);	//	Punto	inicial	del	rayo
        input2.p2.Set(destino.X, destino.Y);	//	Punto	final	del	rayo

        if (morito->puertas->at(0)->body->GetFixtureList()->RayCast(&output2,	input2,	0))
            return true;
        else if (morito->puertas->at(1)->body->GetFixtureList()->RayCast(&output2,	input2,	0))
            return true;

            for (int i = 0; i < morito->muros->size(); i++) {
                if (morito->muros->at(i)->body->GetFixtureList()->RayCast(&output2,	input2,	0))
                    return true;
	}
       return false;
    }
    bool Enemigo::canWalkBetween(vector3df desde, vector3df hasta){

     input.p1.Set(desde.X, hasta.Z);	//	Punto	inicial	del	rayo
     input.p2.Set(hasta.X, hasta.Z);	//	Punto	final	del	rayo

        if (morito->puertas->at(0)->body->GetFixtureList()->RayCast(&output,	input,	0))
            return true;
        else if (morito->puertas->at(1)->body->GetFixtureList()->RayCast(&output,	input,	0))
            return true;

            for (int i = 0; i < morito->muros->size(); i++) {
                if (morito->muros->at(i)->body->GetFixtureList()->RayCast(&output,	input,	0))
                    return true;

	}

       return false;
    }
