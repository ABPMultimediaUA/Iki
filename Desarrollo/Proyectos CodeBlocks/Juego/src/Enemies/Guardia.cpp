#include "FuzzyLogic/FuzzyModule.h"


float testFL(float x, float y)
{
    FuzzyModule fm;

    ///Create FLV
    FuzzyVariable& GdSospecha = fm.CreateFLV("GradoDeSospecha");
    FuzzyVariable& DistanciaJ = fm.CreateFLV("DistanciaJugador");
    FuzzyVariable& Bateria    = fm.CreateFLV("Bateria");
    FuzzyVariable& VidaJ      = fm.CreateFLV("VidaJugador");
    FuzzyVariable& NivelInvs  = fm.CreateFLV("NivelDeInvestigacion");
    FuzzyVariable& Velocidad  = fm.CreateFLV("Velocidad");
    FuzzyVariable& Potencia   = fm.CreateFLV("Potencia");


    ///AddSetsToFLV
    FzSet GdSospecha_Low   = GdSospecha.AddLeftShoulderSet("Sospecha_Low",0,25,45);
    FzSet GdSospecha_Med   = GdSospecha.AddTriangularSet("Sospecha_Med",25,45,70);
    FzSet GdSospecha_High  = GdSospecha.AddRightShoulderSet("Sospecha_Med",45,70,100);

    FzSet DistanciaJ_Low  = DistanciaJ.AddLeftShoulderSet("Distancia_Low",0,5,10);
    FzSet DistanciaJ_Med  = DistanciaJ.AddTriangularSet("Distancia_Med",5,15,20);
    FzSet DistanciaJ_High = DistanciaJ.AddRightShoulderSet("Distancia_High",20,25,30);

    FzSet Bateria_Low  = Bateria.AddLeftShoulderSet("Bateria_Low",0,25,50);
    FzSet Bateria_Med  = Bateria.AddTriangularSet("Bateria_Med",25,50,75);
    FzSet Bateria_High = Bateria.AddRightShoulderSet("Bateria_High",50,75,100);

    FzSet VidaJ_Low  = VidaJ.AddLeftShoulderSet("VidaJ_Low",0,1,3);
    FzSet VidaJ_Med  = VidaJ.AddTriangularSet("VidaJ_Med",1,3,4);
    FzSet VidaJ_High = VidaJ.AddRightShoulderSet("VidaJ_High",3,4,5);

    FzSet NivelInvs_Low  = NivelInvs.AddLeftShoulderSet("Invs_Low",0,0,1);
    FzSet NivelInvs_Med  = NivelInvs.AddTriangularSet("Invs_Med",0,1,2);
    FzSet NivelInvs_High = NivelInvs.AddRightShoulderSet("Invs_High",1,2,2);

    FzSet Velocidad_Low  = Velocidad.AddLeftShoulderSet("Velocidad_Low",0,35,45);
    FzSet Velocidad_Med  = Velocidad.AddTriangularSet("Velocidad_Med",35,45,70);
    FzSet Velocidad_High = Velocidad.AddRightShoulderSet("Velocidad_High",45,70,100);

    FzSet Potencia_Low  = Potencia.AddLeftShoulderSet("Potencia_Low",0,3,4);
    FzSet Potencia_Med  = Potencia.AddTriangularSet("Potencia_Med",3,4,7);
    FzSet Potencia_High = Potencia.AddRightShoulderSet("Potencia_High",4,7,10);


    ///AddRules Using Sets
    fm.AddRule(GdSospecha_Low  , NivelInvs_Low);
    fm.AddRule(GdSospecha_Med  , NivelInvs_Med);
    fm.AddRule(GdSospecha_High , NivelInvs_High);
    fm.AddRule(DistanciaJ_Low  , NivelInvs_High);
    fm.AddRule(DistanciaJ_Med  , NivelInvs_Med);
    fm.AddRule(DistanciaJ_High , NivelInvs_Low);

    fm.AddRule(Bateria_Low     , Velocidad_Low);
    fm.AddRule(Bateria_Med     , Velocidad_Med);
    fm.AddRule(Bateria_High    , Velocidad_High);
    fm.AddRule(DistanciaJ_Low  , Velocidad_Low);
    fm.AddRule(DistanciaJ_Med  , Velocidad_Med);
    fm.AddRule(DistanciaJ_High , Velocidad_High);

    fm.AddRule(Bateria_Low , Potencia_Low);
    fm.AddRule(Bateria_Med , Potencia_Med);
    fm.AddRule(Bateria_High, Potencia_High);
    fm.AddRule(VidaJ_Low   , Potencia_Low);
    fm.AddRule(VidaJ_Med   , Potencia_Med);
    fm.AddRule(VidaJ_High  , Potencia_High);


    ///Test

    fm.Fuzzify("DistanciaJugador", x);
    fm.Fuzzify("Bateria", y);

    float fl = fm.DeFuzzify("Velocidad");

    return fl;
}



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
    input2.maxFraction  =   1.0f;
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

    float disancia = posicion.Distance(posicionProta);
    float vel = testFL(disancia, bateria);
    if (bateria >= 1) bateria-=0.5;

    //std::cout << bateria << std::endl;
    //std::cout << vel/25 << std::endl;

    toProtaPosition.Normalize();
    posicion = posicion + toProtaPosition*(avMovement*vel/25);
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


        input2.p1.Set(posicion.X, posicion.Z);  //  Punto   inicial del rayo
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
                calcularAngulo(posicionProta);
                setPosition();
                modeloAtaque->setVisible(false);
                solounaveh = false;
                atacando = false;
                ataquePreparado = false;
            }
        }
}
