#include "TriggerFactory.h"

#include "TriggerRegion_Circle.h"
#include "TriggerRegion_Rectangle.h"

#include "Trigger_Puerta.h"
#include "Trigger_PuertaLlave.h"
#include "Trigger_Llave.h"
#include "Trigger_Municion.h"
#include "Trigger_Aceite.h"
#include "Trigger_Torreta.h"


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
        trigger->setMesh(modelo);
    }
    else if (tipo == 4){
        trigger = new Trigger_Municion();
        //region
        trigger->AddCircularRegion(centro,1.f);
        //modelo;
        modelo = new AnimatedMesh("resources/Modelos/Municion.obj", {0,0,0,140}, centro, r);
        trigger->setMesh(modelo);
    }
    else if (tipo == 5){
        trigger = new Trigger_Puerta();
        //Region
        trigger->AddCircularRegion(centro,3.5);
        //modelo
        modelo = new AnimatedMesh("resources/Modelos/puertita.obj", {0,0,0,0}, centro, r);
        trigger->setMesh(modelo);
        //b2body
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        b2PolygonShape bodyShape;
        bodyDef.position.Set(x,z);
        trigger->setBody(bodyDef);
        if (r==90)
            bodyShape.SetAsBox(5.f,1.f);
        else
            bodyShape.SetAsBox(1.f,5.f);
        trigger->getBody()->CreateFixture(&bodyShape, 1.f);
    }
    else if (tipo == 6){
        trigger = new Trigger_PuertaLlave();
        //Region
        trigger->AddCircularRegion(centro,3.5);
        //modelo
        modelo = new AnimatedMesh("resources/Modelos/puertita.obj", {0,0,0,0}, centro, r);
        trigger->setMesh(modelo);
        //b2body
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        b2PolygonShape bodyShape;
        bodyDef.position.Set(x,z);
        trigger->setBody(bodyDef);
        if (r==90)
            bodyShape.SetAsBox(5.f,1.f);
        else
            bodyShape.SetAsBox(1.f,5.f);
        trigger->getBody()->CreateFixture(&bodyShape, 1.f);
    }
    else if (tipo == 7){
        trigger = new Trigger_Aceite();
        //region
        trigger->AddCircularRegion(centro,1.f);
        //modelo;
        modelo = new AnimatedMesh("resources/Modelos/lubricante.obj", {0,0,0,0}, centro, r);
        trigger->setMesh(modelo);
    }
    else if (tipo == 8){
        trigger = new Trigger_Torreta();
        //Region
        trigger->AddCircularRegion(centro,7);
        //modelo
        modelo = new AnimatedMesh("resources/Modelos/torreta.obj", {0,0,128,128}, centro, 270);
        trigger->setMesh(modelo);
        //b2body
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        b2PolygonShape bodyShape;
        bodyDef.position.Set(x,z);
        trigger->setBody(bodyDef);
        bodyShape.SetAsBox(1.f,1.f);
        trigger->getBody()->CreateFixture(&bodyShape, 1.f);
    }

    /*else if (tipo == 7){
        trigger = new Trigger_Torreta();
        //Region
        trigger->AddCircularRegion(centro,7);
        //modelo
        modelo = new AnimatedMesh("resources/Modelos/objeto.obj", {0,0,0,0}, centro, r);
        trigger->setMesh(modelo);
        //b2body
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        b2PolygonShape bodyShape;
        bodyDef.position.Set(x,z);
        trigger->setBody(bodyDef);
        bodyShape.SetAsBox(1.f,1.f);
        trigger->getBody()->CreateFixture(&bodyShape, 1.f);
    }*/

    return trigger;
}
