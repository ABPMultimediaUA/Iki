#include "TriggerFactory.h"

#include "TriggerRegion_Circle.h"
#include "TriggerRegion_Rectangle.h"

#include "Trigger_Puerta.h"
#include "Trigger_Municion.h"


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
    if (tipo == 2){
        Trigger_Puerta* trigger = new Trigger_Puerta();
        //Region
        Structs::TPosicion centro(x,0,z);
        float radio = 3.5;
        trigger->AddCircularTriggerRegion(centro,radio);
        //modelo
        AnimatedMesh* modelo = new AnimatedMesh("Modelos/puertita.obj", {0,0,0,0}, centro, r);
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

        return trigger;
    }

    if (tipo == 4){
        Trigger_Municion* trigger = new Trigger_Municion();
        //region
        Structs::TPosicion centro(x,0,z);
        float radio = 1.f;
        trigger->AddCircularTriggerRegion(centro,radio);
        //modelo;
        AnimatedMesh* modelo = new AnimatedMesh("Modelos/objeto.obj", {0,0,0,0}, centro, r);
        trigger->setMesh(modelo);

        return trigger;
    }

}
