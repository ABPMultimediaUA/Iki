#include "Suelo.h"
#include <Box2D/Box2D.h>

Suelo::Suelo()
{
   /* b2BodyDef limitesBodyDef;
    limitesBodyDef.position.Set(0.0f, 0.0f);

    iworld= World::Instance();
    body= iworld->getWorld()->CreateBody(&limitesBodyDef);

    b2EdgeShape limitesShape;
    b2FixtureDef fixtureDef;
    fixtureDef.shape= &limitesShape;

    limitesShape.Set(b2Vec2(0.0f, 0.0f), b2Vec2(300.0f, 0.0f));
    limitesBody->CreateFixture(&fixtureDef);*/
}

Suelo::~Suelo()
{
    //dtor
}
