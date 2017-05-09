#include "Enemies/Guardia.h"
#include "Fachada/GraphicsFacade.h"
#include "PhisicsWorld.h"
#include "Fachada/MeshSceneNode.h"
#include "SoundManager.h"

void Guardia::inicializar_enemigo(Map* m)
{
    //De momento todos tienen el mismo body y cosas en comun asi que las inicializo para los tres en init
    init(m);
    tipo = 1;
    vida = 4;
    Structs::TColor color = {255,255,255,0};
    aniMesh = new AnimatedMesh("resources/Modelos/Enemigo.obj", color,posicion, 90);
    aniMesh->setScale(3);
    //modelo->cambiarColor(color);
    ataquePreparado = false;
    solounaveh = false;
    atacando = false;
    input2.maxFraction	=	1.0f;
    modeloAtaque = new MeshSceneNode(medidaAtaque,posicionAtaque,colorAtaque);
    modeloAtaque->setVisible(false);

}
void Guardia::investigar(){
    andarPath(2,posicionInteres);
    setPosition();

}
void Guardia::perseguir(){
    //moverBody(quietoParado);
    toProtaPosition = posicionProta - posicion;
    mirandoHacia = toProtaPosition;
    //toProtaPosition.Normalize();
    //posicion = posicion + toProtaPosition*(avMovement*2);
    calcularAngulo(posicionProta);
    MoverEnemigo(toProtaPosition);
    //setPosition();
}
void Guardia::ataque(){
    moverBody(quietoParado);
    if(!ataquePreparado)
    {
        cargarAtaque();
    }
    else{
        ejecutarAtaque();
    }
}
void Guardia::cargarAtaque(){
        atacando = true;

        vectorAtaque = posicionProta - posicion;
        anguloAtaque = atan2f((vectorAtaque.Z) , -(vectorAtaque.X)) * 180.f / PI;


        input2.p1.Set(posicion.X, posicion.Z);	//	Punto	inicial	del	rayo
        input2.p2.Set(posicion.X+((vectorAtaque.X/vectorAtaque.Length())*10), posicion.Z+((vectorAtaque.Z/vectorAtaque.Length())*10));

        distanciaAtaque = sqrt(pow(input2.p2.x - input2.p1.x, 2) + pow(input2.p2.y - input2.p1.y, 2));

        posicionAtaque = {(input2.p2.x + input2.p1.x)/2, 0 , (input2.p2.y + input2.p1.y)/2};

        modeloAtaque->setPosition(posicionAtaque);
        modeloAtaque->setRotation(anguloAtaque);
        ataquePreparado = true;
        resetTime();
}
void Guardia::ejecutarAtaque(){

        if(tiempoEnEstado > 0.8 && EntityMgr->getEntityByID(0)->getVida() > 0)
        {
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
                    EntityMgr->getEntityByID(0)->quitarVida();;
                    solounaveh = true;
                    SoundMgr->playSonido("AccionesRobots/conoelectrico");
                }else{
                    //SoundMgr->playSonido("AccionesRobots/conoelectrico2");
                }
            }

            if(tiempoEnEstado > 1.2){
                modeloAtaque->setVisible(false);
                solounaveh = false;
                atacando = false;
                ataquePreparado = false;
            }
        }
}
