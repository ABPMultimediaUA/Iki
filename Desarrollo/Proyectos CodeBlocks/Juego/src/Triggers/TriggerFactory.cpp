#include "TriggerFactory.h"

#include "TriggerRegion_Circle.h"
#include "TriggerRegion_Rectangle.h"

#include "Trigger_Puerta.h"


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
        const char* cadena = "";
        Structs::TColor color = {0,0,0,0};

        Trigger_Puerta* trigger = new Trigger_Puerta;

        Structs::TPosicion tl = {x+3,0,z-3};
        Structs::TPosicion br = {x-3,0,z+3};

        trigger->AddRectangularTriggerRegion(tl,br);

        Structs::TPosicion pos = {x,0,z};
        cadena = "Modelos/puertita.obj";
        AnimatedMesh* modelo = new AnimatedMesh(cadena, color, pos, r);
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


}
