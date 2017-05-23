#include "FuzzyQuery.h"
#include "Investigar.h"
#include "Enemies/Guardia.h"
#include "Fachada/GraphicsFacade.h"
#include "PhisicsWorld.h"
#include "Fachada/MeshSceneNode.h"
#include "SoundManager.h"

Guardia::~Guardia(){
    delete aniMesh;
    body->GetWorld()->DestroyBody(body);
    delete modeloAtaque;
    ruta = nullptr;
    pRuta = nullptr;
    Mapa = nullptr;
    delete G_stateMachine;
    actualState = nullptr;
    oldState = nullptr;
    globalState = nullptr;
    grafo = nullptr;
    path = nullptr;
    delete memory;
}
void Guardia::inicializar_enemigo(Map* m)
{
    //De momento todos tienen el mismo body y cosas en comun asi que las inicializo para los tres en init
    init(m);
    tipo = 1;
    vida = 4;
    Structs::TColor color = {255,255,255,0};
    aniMesh = new AnimatedMesh("resources/Modelos/guardiahumilde.obj", color,posicion, 90);
    aniMesh->setTexture("resources/Texturas/palguardia.png");
    aniMesh->setScale(3);
    aniMesh->setRotation(90);
    ataquePreparado = false;
    solounaveh = false;
    atacando = false;
    input2.maxFraction  =   1.0f;
}
void Guardia::perseguir(){

    if (isEnemySeeing(posicionProta)){

        calcularAngulo(posicionProta);
        toProtaPosition = posicionProta - posicion;
        toProtaPosition.Normalize();
        mirandoHacia = toProtaPosition;

        FuzzyQuery query;
        float disancia = posicion.Distance(posicionProta);
        float vel = query.Query(disancia, bateria, 1);
        //if (bateria >= 0) bateria-=vel/250;
        //std::cout << bateria << "%   " << vel/25 << std::endl;

        posicion = posicion + toProtaPosition*(avMovement*vel/25);

        //MoverEnemigo(toProtaPosition);
        setPosition();
    }else{
        guessing = true;
        //toProtaPosition = posicion;
        //this->GetFSM()->ChangeState(Investigar::Instance());
    }
}
void Guardia::ataque(){
    moverBody(quietoParado);
    if(!ataquePreparado)
        { cargarAtaque(); }
    else
        { ejecutarAtaque(); }
}
void Guardia::cargarAtaque(){
        atacando = true;
        ataquePreparado = true;
        sonidoataque = true;

        FuzzyQuery query;
        float vidaj = EntityMgr->getEntityByID(0)->getVida();
        float pot = query.Query(vidaj, bateria, 2);


        if (bateria - pot < 5){
            atacando = false;
            ataquePreparado = false;
            bateria += 5;
            //std::cout << bateria << std::endl;
        }else{
            //std::cout << bateria << "%   " << vidaj << "   " << pot << "/10" << std::endl;
            bateria -= pot/2;
        }

        modeloAtaque->setScale({1,1,1});

        vectorAtaque = posicionProta - posicion;
        anguloAtaque = atan2f((vectorAtaque.Z) , -(vectorAtaque.X)) * 180.f / PI;

        input2.p1.Set(posicion.X, posicion.Z);  //  Punto   inicial del rayo
        input2.p2.Set(posicion.X+((vectorAtaque.X/vectorAtaque.Length())* 7.5), posicion.Z+((vectorAtaque.Z/vectorAtaque.Length())* 5));

        distanciaAtaque = sqrt(pow(input2.p2.x - input2.p1.x, 2) + pow(input2.p2.y - input2.p1.y, 2));
        posicionAtaque = {(input2.p2.x + input2.p1.x)/2, 1 , (input2.p2.y + input2.p1.y)/2};

        //bnmodeloAtaque->setRotation(0);
        modeloAtaque->setPosition(posicion);
        modeloAtaque->setRotationXYZ(0,anguloAtaque,0);
        resetTime();
}
void Guardia::ejecutarAtaque(){

        if(tiempoEnEstado > 0.6 && EntityMgr->getEntityByID(0)->getVida() > 0)
        {
            if (sonidoataque) { sonidoataque=false; SoundMgr->playSonido("AccionesRobots/conoelectrico");}

            modeloAtaque->setVisible(true);

            if(distanciaPlayer <= distanciaAtaque && !solounaveh) // y si no te veo;
            {
                vectorProta = posicionProta - posicion;
                float anguloProta = atan2f((vectorProta.Z) , -(vectorProta.X)) * 180.f / PI;
                //std::cout << "angulo ataque: "<< anguloAtaque <<" anguloProta: "<<anguloProta<<std::endl;
                if(anguloAtaque < 0)
                    anguloAtaque+360;
                if(anguloProta < 0)
                    anguloProta+360;
                if(abs(anguloAtaque - anguloProta) < 45){
                    //EntityMgr->getEntityByID(0)->quitarVida();
                    EntityMgr->getEntityByID(0)->setVida(EntityMgr->getEntityByID(0)->getVida()-20);
                    solounaveh = true;
                }else{

                }
            }

            if(tiempoEnEstado > 1.0){
                calcularAngulo(posicionProta);
                mirandoHacia= toProtaPosition;
                setPosition();
                modeloAtaque->setVisible(false);
                solounaveh = false;
                atacando = false;
                ataquePreparado = false;

            }
        }
}
