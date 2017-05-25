#include "TriggerFactory.h"

#include "TriggerRegion_Circle.h"
#include "TriggerRegion_Rectangle.h"

#include "Trigger_Puerta.h"
#include "Trigger_PuertaLlave.h"
#include "Trigger_Llave.h"
#include "Trigger_Engranaje.h"
#include "Trigger_Municion.h"
#include "Trigger_Aceite.h"
#include "Trigger_Torreta.h"
#include "Trigger_PuertaNivel.h"
#include "Trigger_Apisonadora.h"
#include "Trigger_Palanca.h"


#include "../Fachada/AnimatedMesh.h"
#include "../PhisicsWorld.h"
#include "Structs.h"

TriggerFactory::TriggerFactory()
{
    //ctor
}

TriggerFactory::~TriggerFactory()
{
    //dtor
}

Trigger *TriggerFactory::crearTrigger(int tipo, float z, float x, float r)
{
    Trigger* trigger;
    Structs::TPosicion centro(x,0,z);
    AnimatedMesh* modelo;


    if (tipo == 1){
        trigger = new Trigger_Apisonadora(x,z,r);
        //Region
        trigger->AddCircularRegion(centro,5.f);
        //modelo
        modelo = new AnimatedMesh("resources/Modelos/soporte.obj", {0,0,128,128}, centro, r);
        modelo->setTexture("resources/Texturas/soporte.png");
        trigger->setMesh(modelo);
        static_cast<Trigger_Apisonadora*>(trigger)->setPosicionPlancha();
    }
    else if (tipo == 2){
        trigger = new Trigger_Engranaje();
        //region
        trigger->AddCircularRegion(centro,1.f);
        //modelo;
        modelo = new AnimatedMesh("resources/Modelos/engranaje2.obj", {0,0,0,140}, centro, r);
        modelo->setTexture("resources/Texturas/engranaje2.png");
        modelo->setScale({2,2,2});
        modelo->setPosition({x, 0.5, z});
        //modelo->setRotationXYZ(90,90,1);
        trigger->setMesh(modelo);
    }
    else if (tipo == 3){
        trigger = new Trigger_Llave();
        //region
        trigger->AddCircularRegion(centro,1.f);
        //modelo;
        modelo = new AnimatedMesh("resources/Modelos/Tarjeta2.obj", {0,100,149,237}, centro, r);
        modelo->setTexture("resources/Texturas/Tarjeta2.png");
        modelo->setScale({2,2,2});
        modelo->setPosition({x, 0.5, z});
        //modelo->setRotationXYZ(180,180,180);
        trigger->setMesh(modelo);
    }
    else if (tipo == 4){
        trigger = new Trigger_Municion();
        //region
        trigger->AddCircularRegion(centro,1.f);
        //modelo;
        modelo = new AnimatedMesh("resources/Modelos/Municion.obj", {0,0,0,140}, centro, r);
        modelo->setTexture("resources/Texturas/muni.png");
        modelo->setPosition({x, 0.5, z});
        trigger->setMesh(modelo);
    }
    if (tipo == 5){
        trigger = new Trigger_Puerta(x,z,r);
        //Region
        trigger->AddCircularRegion(centro,3.5);
        //modelo
        modelo = new AnimatedMesh("resources/Modelos/puerta_marco.obj", {0,0,0,0}, centro, r);
        modelo->setVisible(false);
        trigger->setMesh(modelo);

    }
    else if (tipo == 6){
        trigger = new Trigger_PuertaLlave(x,z,r);
        //Region
        trigger->AddCircularRegion(centro,3.5);
        //modelo
        modelo = new AnimatedMesh("resources/Modelos/puerta_marco.obj", {0,0,0,0}, centro, r);
        trigger->setMesh(modelo);

    }
    else if (tipo == 7){
        trigger = new Trigger_Aceite();
        //region
        trigger->AddCircularRegion(centro,1.f);
        //modelo;
        modelo = new AnimatedMesh("resources/Modelos/lubricante.obj", {0,0,0,0}, centro, r);
        modelo->setTexture("resources/Texturas/lubricante.png");
        modelo->setPosition({x, 0.5, z});
        trigger->setMesh(modelo);
    }

    else if (tipo == 8){
        trigger = new Trigger_PuertaNivel();
        //Region
        trigger->AddCircularRegion(centro,3.5);
        //modelo
        modelo = new AnimatedMesh("resources/Modelos/valla_exterior.obj", {0,0,128,128}, centro, r);
        trigger->setMesh(modelo);
    }
    else if (tipo == 9){
        trigger = new Trigger_Torreta(x,z,r);
        //Region
        trigger->AddCircularRegion(centro,15);
        //modelo
        modelo = new AnimatedMesh("resources/Modelos/torreta.obj", {0,0,128,128}, centro, r);
        trigger->setMesh(modelo);
    }
    else if (tipo == 10){
        trigger = new Trigger_Palanca();
        //Region
        trigger->AddCircularRegion(centro,2);
        //modelo
        modelo = new AnimatedMesh("resources/Modelos/palanca.obj", {0,0,128,128}, centro, r);
        modelo->setTexture("resources/Texturas/palanca.png");
        modelo->setScale(3);
        trigger->setMesh(modelo);
    }

    return trigger;
}
