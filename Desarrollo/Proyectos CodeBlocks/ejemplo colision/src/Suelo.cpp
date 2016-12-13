#include "Suelo.h"

Suelo::Suelo()
{
    //ctor
}

Suelo::~Suelo()
{
    //dtor
}
/*
///SUELO
    b2BodyDef limitesBodyDef;
    limitesBodyDef.position.Set(0.0f, 0.0f);

    b2Body* limitesBody = world->CreateBody(&limitesBodyDef);
    b2EdgeShape limitesShape;
    b2FixtureDef fixtureDef;
    fixtureDef.shape= &limitesShape;

    limitesShape.Set(b2Vec2(0.0f, 0.0f), b2Vec2(300.0f, 0.0f));
    limitesBody->CreateFixture(&fixtureDef);
*/
