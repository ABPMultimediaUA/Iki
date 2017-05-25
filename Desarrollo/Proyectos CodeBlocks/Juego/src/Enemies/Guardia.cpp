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
    aniMesh->setScale(3.5);
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
        //std::cout << bateria << "%   " << vel << std::endl;

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

        if (!cargarBateria){
            if (bateria - pot*2 >= 0){
                bateria -= pot*2;
                //std::cout << bateria << "%   " << vidaj << "   " << pot << "/10" << std::endl;

            }else{
                cargarBateria=true;
                atacando = false;
                ataquePreparado = false;
            }
        }else{
            atacando = false;
            ataquePreparado = false;
            f32 tiempo = GraphicsFacade::getInstance().getTimer()->getTime()/1000.f;
            if (tiempo - bateriaT > 0.05){
                //std::cout << bateria << std::endl;
                bateriaT = tiempo;
                if (bateria < 100) bateria += 1;
                if (bateria == 100) cargarBateria=false;
            }
        }

        tiempoCarga = pot / 10.0;
        danyo = pot*2;

        float s = pot/10.0 * 2;
        modeloAtaque->setScale({s+0.25,1,1});

        vectorAtaque = posicionProta - posicion;
        anguloAtaque = atan2f((vectorAtaque.Z) , -(vectorAtaque.X)) * 180.f / PI;

        input2.p1.Set(posicion.X, posicion.Z);  //  Punto   inicial del rayo
        input2.p2.Set(posicion.X+((vectorAtaque.X/vectorAtaque.Length())* (7.5 + pot)), posicion.Z+((vectorAtaque.Z/vectorAtaque.Length())* 5));

        distanciaAtaque = sqrt(pow(input2.p2.x - input2.p1.x, 2) + pow(input2.p2.y - input2.p1.y, 2));
        posicionAtaque = {(input2.p2.x + input2.p1.x)/2, 1 , (input2.p2.y + input2.p1.y)/2};

        //bnmodeloAtaque->setRotation(0);
        modeloAtaque->setPosition(posicion);
        modeloAtaque->setRotationXYZ(0,anguloAtaque,0);
        resetTime();
}
void Guardia::ejecutarAtaque(){

        if(tiempoEnEstado > tiempoCarga && EntityMgr->getEntityByID(0)->getVida() > 0)
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
                    std::cout << "me da  " << danyo << std::endl;
                    EntityMgr->getEntityByID(0)->quitarVida(danyo);
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
