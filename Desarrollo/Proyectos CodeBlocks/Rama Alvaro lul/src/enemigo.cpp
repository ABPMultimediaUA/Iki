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

void Enemigo::inicialiazar(int t, int ID,scene::ISceneManager* smgr, core::vector3df p, PatrolRoute pr)
{

    pRuta = pr.getInicial();
    ruta = pr;
    id=ID;
    input.maxFraction	=	1.0f;
    tam = 2;
    lul = true;
    lul2 = true;
    lul3 = true;
    estado = 0;
    vida=3;
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
    tiempoPatrullando = 0.0;
    tiempoEscaneando = 0;
    avMovement = 0.0;
    primeraVez=true;
    primeraVez2=true;
    primeraVez3=true;
    time=0.0;
    mensajePendiente=false;
    muerto=false;
    hayAliado=false;

    smgr1 = smgr;


    rayo = smgr1->getGeometryCreator()->createCubeMesh(core::vector3df(10.f, 1.f, 1.f));
    modelo2 = smgr1->addMeshSceneNode(rayo);
    modelo2->setVisible(false);

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


}

void Enemigo::inicialiazar2(scene::ISceneManager* smgr, core::vector3df p)
{
    tam= 3;
    vida = 150;
    tipo=4;
    id=3;

    mura1 = smgr->getGeometryCreator()->createCubeMesh(core::vector3df(4.f, 2.f, 4.f));
    modelo = smgr->addMeshSceneNode(mura1);

    modelo->setPosition(p);
    modelo->setRotation(core::vector3df(0,-45,0));
    posicion=modelo->getPosition();
    angulo = -145;

    input.maxFraction	=	1.0f;

    b2BodyDef bodyDef;
    bodyDef.type= b2_staticBody;
    bodyDef.position.Set(p.X, p.Z);
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
}


b2Body* Enemigo::getBody()
{
    return body2;
}

void Enemigo::setCuboEnemigo(core::vector3df cb)
{
    cuboEnemigo = cb;
}

int Enemigo::getEstado()
{
    return estado;
}
int Enemigo::getTipo()
{
    return tipo;
}
int Enemigo::getID()
{
    return id;
}
bool Enemigo::getCreado()
{
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

void Enemigo::setPosicion()
{

    body2->SetTransform(b2Vec2(cuboEnemigo.X, cuboEnemigo.Z), angulo);
    modelo->setPosition(vector3df(body2->GetPosition().x, 0, body2->GetPosition().y));
    modelo->setRotation(core::vector3df(0,body2->GetAngle(),0));

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

scene::IMeshSceneNode* Enemigo::getModelo()
{
    return modelo;
}

core::vector3df Enemigo::getCuboEnemigo()
{
    return cuboEnemigo;
}

void Enemigo::patrullar()
{

    if(cuboEnemigo.getDistanceFrom(pRuta->getPunto()) >0.1)
    {

        cuboEnemigo += posicionInicial.normalize()*avMovement;

    }
    else
    {
        cuboEnemigo=pRuta->getPunto();
        pRuta = pRuta->getNext();
        posicionInicial = pRuta->getPunto() - cuboEnemigo;

    }
    posicion = cuboEnemigo;
    angulo = atan2f((pRuta->getPunto().Z-posicion.Z) ,-(pRuta->getPunto().X-posicion.X)) * 180.f /PI;

}

bool Enemigo::comprobarPunto(b2Vec2 v)
{
    bool si = false;
    si = body2->GetFixtureList()->TestPoint(v);

    return si;
}

void Enemigo::quitarVida()
{
    if(vida>0)
        --vida;

    if(vida <= 0)
    {
        matar();
    }
}

void Enemigo::setDanyado(bool b)
{
    danyado = b;
}

bool Enemigo::getDanyado()
{
    return danyado;
}

bool Enemigo::getMuerto()
{
    return muerto;
}

void Enemigo::inspeccionar()
{
    if(cuboEnemigo.getDistanceFrom(puntoInteres) != 0)
    {
        cuboEnemigo += ((puntoInteres) - (cuboEnemigo)).normalize() * avMovement;
    }
    if(cuboEnemigo.getDistanceFrom(puntoInteres) <= 0.1)
    {
        cuboEnemigo = puntoInteres;
    }
    posicion = cuboEnemigo;
    angulo = atan2f((puntoInteres.Z-posicion.Z) ,-(puntoInteres.X-posicion.X)) * 180.f /PI;
}
void Enemigo::vigilar()
{

    time=tiempo.getTime();
    tiempoVigilando=(time-reloj);

    if(tiempoVigilando < 1.5)
    {
        if(lul)
            angulo = angulo + 30;

        lul = false;
    }
    else if(tiempoVigilando>= 1.5 && tiempoVigilando<= 3.0)
    {
        if(lul2)
            angulo = angulo - 60;

        lul2 = false;
    }
    else if(tiempoVigilando>3.0)
    {
        if(lul3)
            angulo = angulo + 30;

        lul3 = false;
    }
    posicion = cuboEnemigo;
    if(!noteveo() || distanciaPlayer < 8 && player->sigilo == false && player->ismoving == true)
        estado = 3;
}

void Enemigo::curar(Enemigo aliado)
{

}
void Enemigo::perseguir()
{
    cuboEnemigo += direccionHaciaProta.normalize() * avMovement * 2.0;
    posicion = cuboEnemigo;
    angulo = atan2f((direccionHaciaProta.Z) ,
                    -(direccionHaciaProta.X)) * 180.f / irr::core::PI;


}
void Enemigo::pedirAyuda()
{
    cuboEnemigo += direccionHaciaAliado.normalize() * avMovement* 2.0;
    posicion = cuboEnemigo;
    angulo = atan2f((aliado->getPosicion().Z-posicion.Z) ,-(aliado->getPosicion().X-posicion.X)) * 180.f /PI;
}

void Enemigo::huir()
{
    cuboEnemigo += direccionHuir.normalize() * avMovement* 2.0;
    posicion = cuboEnemigo;
}
void Enemigo::proteger()  //GIRAR ALREDEDOR DEL ALIADO
{
    if(fabs(posicion.X - aliado->getPosicion().X) > 2 && fabs(posicion.Z - aliado->getPosicion().Z) > 2)
    {
        cuboEnemigo += direccionHaciaAliado.normalize() * avMovement* 2.0;
    }
    posicion = cuboEnemigo;
    angulo = atan2f((aliado->getPosicion().Z-posicion.Z) ,-(aliado->getPosicion().X-posicion.X)) * 180.f /PI;
}


void Enemigo::escanear()
{
    time=tiempo.getTime();
    tiempoEscaneando=(time-reloj);

    if(tiempoEscaneando < 3.0 && sospecha < 99 && distanciaPlayer<28 && !noteveo())
    {

        if (player->sigilo == true )
            sospecha+=10*tiempo.getTimeFactor();
        else
            sospecha+=30*tiempo.getTimeFactor();

    }
    else
    {
        primeraVez=true;
        //logica difusa
        logica.Fuzzify(distanciaPlayer, logica.fm.vars[0]);
        logica.Fuzzify(sospecha, logica.fm.vars[1]);
        logica.InitializeRules();
        logica.CalculateFAM();
        float val = logica.Defuzzify();


        if (val <= 25.0)
        {
            estado = 0;
        }
        else if (val <= 55)
        {
            puntoInteres=posicionProta;
            estado=8;
        }
        else
        {
            estado = 3;
        }

    }
    posicion = cuboEnemigo;
}
void Enemigo::matar()
{
    modelo->setVisible(false);
    modelo2->setVisible(false);
    body2->SetActive(false);
    muerto=true;
    estado=10;

    if(fabrica == true)
        this->inicialiazar(tipo,id,smgr1,vector3df(50 , 0 , 50), ruta);

}
void Enemigo::avisarCapsulas()
{

}
float Enemigo::getVida()
{
    return vida;
}

//Funcionamiento maquina de estados

int Enemigo::maquinaEstados()
{
    if(muerto==false)
    {
        switch (estado)
        {
        case 0:

            if(primeraVez2)
            {
                reloj=tiempo.setMomento();
                primeraVez2 = false;
            }
            time=tiempo.getTime();
            tiempoPatrullando=(time-reloj);
            smgr1->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(70, 70, 70, 0));
            patrullar();

            if (distanciaPlayer < 8 && player->sigilo == false && player->ismoving == true)
            {
                puntoInteres=posicionProta;
                estado=8;
            }
            //Si el player se acerca sospecha

            else if(distanciaPlayer>=4 && distanciaPlayer<28)
            {

                if (!noteveo())
                    estado = 1;

            }
            else if(tiempoPatrullando>11)
            {
                tiempoPatrullando = 0;
                primeraVez2 = true;
                if(rand() % 100 < 40)
                    estado = 2;
            }


            //a veces se para a vigilar dependiendo de ciertas circunstancias
            break;

        case 1:
            /// ESCANEAR / SOSPECHAR ///
            smgr1->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(128, 128, 128, 0));


            if(primeraVez)
            {
                //sospecha=0;
                reloj=tiempo.setMomento();
                primeraVez=false;
            }
            escanear();

            break;
        case 2: //VIGILAR
            smgr1->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(0, 0, 0, 0));
            if(primeraVez3)
            {
                reloj=tiempo.setMomento();
                primeraVez3=false;

            }
            if (tiempoVigilando < 4.5)
            {
                vigilar();
            }
            else
            {
                lul = true;
                lul2 = true;
                lul3 = true;
                primeraVez3=true;
                tiempoVigilando=0.0;
                posicionInicial = pRuta->getPunto()- cuboEnemigo;
                estado=0;

            }
            break;
        case 3: //COMBATE/ALARMA/DECISION MEDICO
            smgr1->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(0, 0, 255, 0));
            if(tipo == 0)
            {
                estado=6;
                //si el prota esta a rango ataca
                //sino persigue
            }
            else if(tipo == 1)
            {
                //mantiene poscion y suena
                posicion = cuboEnemigo;
                puntoInteres=posicionProta;
                avisarCapsulas();
            }
            else if(tipo == 2)
            {
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
            if( posicion.getDistanceFrom(aliado->getPosicion()) < 5)
            {
                estado=9;
                mensajeEstado=6;
                mensajePendiente=true;
            }
            //cuando lo encuentra, lo cura si es necesario y lo protege
            break;
        case 5: //HUIR
            if(cuboEnemigo.getDistanceFrom(posicionAliado) > 10)
            {
                huir();
            }
            break;
        case 6: //PERSEGUIR
            smgr1->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(255, 0, 0, 0));
            sospecha = 0.0;
            perseguir();
            if(distanciaPlayer>40)
            {
                puntoInteres = posicionProta;
                estado = 8;
            }
            if(distanciaPlayer<6)
            {
                estado=7;
            }
            //si esta a rango ataca
            //si lo pierde de vista, vuelve a la patrulla
            break;
        case 7: //ATACAR

            if(distanciaPlayer<6 && !prepara)
            {
                reloj=tiempo.setMomento();
                prepara = true;

                angulo = atan2f((direccionHaciaProta.Z) , -(direccionHaciaProta.X)) * 180.f / irr::core::PI;
                input2.p1.Set(this->getBody()->GetPosition().x, this->getBody()->GetPosition().y);	//	Punto	inicial	del	rayo

                //Pa que no sufrais con if's infinitos lul
                bodyauxiliar = player->getBody()->GetPosition()-this->getBody()->GetPosition();

                float modulo = sqrt((bodyauxiliar.x*bodyauxiliar.x) + (bodyauxiliar.y*bodyauxiliar.y));

                input2.p2.Set(this->getBody()->GetPosition().x+((bodyauxiliar.x/modulo)*10), this->getBody()->GetPosition().y+((bodyauxiliar.y/modulo)*10));

                distanciahuhu = sqrt(pow(input2.p2.x-input2.p1.x, 2)+pow(input2.p2.y-input2.p1.y, 2));
                modelo2->setScale(core::vector3df(distanciahuhu/10, 0.5f, 0.5f));
                modelo2->setPosition(core::vector3df((input2.p2.x+input2.p1.x)/2,0,(input2.p2.y+input2.p1.y)/2));
                modelo2->setRotation(core::vector3df(0,angulo,0));
            }
            if(prepara == true)
            {

                time=tiempo.getTime();
                tiempoataque=(time-reloj);

                if(tiempoataque > 1.1)
                {
                    smgr1->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(50, 20, 50, 0));
                    modelo2->setVisible(true);
                    if(distanciaPlayer<=distanciahuhu && !noteveo() && !solounaveh)
                    {
                        player->setVida(player->getVida()-1);
                        std::cout << player->getVida()<<"\n";
                        solounaveh = true;
                    }
                    if(tiempoataque > 1.6)
                    {
                        modelo2->setVisible(false);
                        tiempoataque = 0;
                        prepara = false;
                        solounaveh = false;
                    }
                }



            }
            else if(!prepara && distanciaPlayer >= 6)
            {
                estado=6;
            }
            break;
        case 8: //INSPECCIONAR
            smgr1->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(255, 255, 255, 0));
            inspeccionar();
            if (distanciaPlayer<=28)
            {
                if (!noteveo())
                    estado = 3;
            }
            if(posicion.getDistanceFrom(puntoInteres) == 0)
            {
                estado=2;
            }

            break;
        case 9: //PROTEGER
            proteger();
            if (aliado->getEstado()==10)
            {
                std::cout << "PosiconAliado(x,y)" << posicionAliado.X<<","<<posicionAliado.Z <<"entraaaaaa"<<std::endl;
                estado=5;
            }
            if(aliado->getEstado()==0)
            {
                estado=0;
                posicionInicial = pRuta->getPunto() - cuboEnemigo;
            }
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

void Enemigo::update(core::vector3df cuboProta, Time temps, Enemigo *aliados[7])
{

    tiempo = temps;
    if(modelo)
    {


        if(tipo==2) //SI ES MEDICO
        {
            direccionHuir = (aliados[5]->getPosicion()-posicion);
            //habria que comprobar el tipo de aliado y si es guardia guardarnos las posiciones, en este caso sabemos que es el 0
            for(i=0; i<7; i++)
            {
                if(aliados[i]->getTipo()==0 && aliados[i]->getEstado()==10)
                {
                    if(aliado->getID()==aliados[i]->getID())
                    {
                        hayAliado=false;
                    }
                }
                if(aliados[i]->getTipo()==0 && aliados[i]->getEstado()!=10 && (i==0 || i==6)) //Hay guardias y no estan muertos
                {
                    if(hayAliado && aliado->getID()!=i) //Si ya tiene asignado un aliado
                    {

                        if(posicion.getDistanceFrom(aliados[i]->getPosicion()) < posicion.getDistanceFrom(aliado->getPosicion()))
                        {
                            posicionAliado=aliados[i]->getPosicion();
                            direccionHaciaAliado= (posicionAliado-posicion);
                            aliado=aliados[i];
                        }
                    }
                    else if (hayAliado==false) //Si no tiene asignado un aliado
                    {
                        posicionAliado=aliados[i]->getPosicion();
                        direccionHaciaAliado= (posicionAliado-posicion);
                        aliado=aliados[i];
                        hayAliado=true;

                    }
                    else if(aliado->getID()==i)
                    {
                        aliado=aliados[i];
                        posicionAliado=aliado->getPosicion();
                        direccionHaciaAliado= (posicionAliado-posicion);
                    }

                }
                else
                {
                    posicionAliado=aliados[5]->getPosicion();
                }
            }
            if(mensajePendiente)
            {
                //aqui pues deberiamos tener un destinario, de momento solo tenemos mensaje entre la medio y el guardia y por eso es asi
                aliado->setEstado(mensajeEstado);
                mensajePendiente=false;
            }
        }

        avMovement = 9.5f * tiempo.getTimeFactor();
        distanciaPlayer = posicion.getDistanceFrom(cuboProta);
        direccionHaciaProta=cuboProta-posicion;
        maquinaEstados();
        posicionProta=cuboProta;
    }

}

void Enemigo::setMuro(Map* murito, Player *prota)
{
    player= prota;
    morito = murito;
}

bool Enemigo::noteveo()
{
    input.p1.Set(this->getBody()->GetPosition().x, this->getBody()->GetPosition().y);	//	Punto	inicial	del	rayo
    input.p2.Set(player->getBody()->GetPosition().x, player->getBody()->GetPosition().y);	//	Punto	final	del	rayo

    angulo7 = atan2f((input.p2.y-input.p1.y) , -(input.p2.x-input.p1.x)) * 180.f / irr::core::PI;

    if (morito->puertas->at(0)->body->GetFixtureList()->RayCast(&output,	input,	0))
        return true;
    else if (morito->puertas->at(1)->body->GetFixtureList()->RayCast(&output,	input,	0))
        return true;

    for (int i = 0; i < morito->muros->size(); i++)
    {
        if (morito->muros->at(i)->body->GetFixtureList()->RayCast(&output,	input,	0))
            return true;

    }
    if(tipo!=4)
    {
        if(angulo+180 <= angulo7 + 225 && angulo+180 >= angulo7 + 135)
            return false;
        else
            return true;
    }

    return false;






}
