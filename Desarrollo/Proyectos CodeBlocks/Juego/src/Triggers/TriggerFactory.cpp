#include "TriggerFactory.h"

#include "TriggerRegion_Circle.h"
#include "TriggerRegion_Rectangle.h"

#include "Trigger_Puerta.h"
#include "Trigger_PuertaLlave.h"
#include "Trigger_Llave.h"
#include "Trigger_Municion.h"
#include "Trigger_Aceite.h"
#include "Trigger_Torreta.h"
#include "Trigger_PuertaNivel.h"


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


    if (tipo == 3){
        trigger = new Trigger_Llave();
        //region
        trigger->AddCircularRegion(centro,1.f);
        //modelo;
        modelo = new AnimatedMesh("resources/Modelos/Tarjeta.obj", {0,100,149,237}, centro, r);
        modelo->setTexture("resources/Texturas/tarjetaTex.png");
        modelo->setPosition({x, 0.5, z});
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
        modelo = new AnimatedMesh("resources/Modelos/puertita.obj", {0,0,0,0}, centro, r);
        trigger->setMesh(modelo);

    }
    else if (tipo == 6){
        trigger = new Trigger_PuertaLlave(x,z,r);
        //Region
        trigger->AddCircularRegion(centro,3.5);
        //modelo
        modelo = new AnimatedMesh("resources/Modelos/puertita.obj", {0,0,0,0}, centro, r);
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
        trigger->AddCircularRegion(centro,10);
        //modelo
        modelo = new AnimatedMesh("resources/Modelos/torreta.obj", {0,0,128,128}, centro, r);
        trigger->setMesh(modelo);
    }

    return trigger;
}
