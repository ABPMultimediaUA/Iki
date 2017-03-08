#include "Player.h"
#include <Box2D/Box2D.h>



Player::Player()
{
    //ctor
}

Player::~Player()
{
    //dtor
}

void Player::inicializar(scene::ISceneManager* smgr,video::IVideoDriver* driver){
    tam= 2;
    vida=5;
    balas= 1;
    ismoving = false;
    smgr1=smgr;

    modelo = smgr->addCubeSceneNode(tam);
    modelo->setMaterialFlag(video::EMF_LIGHTING, false);
    modelo->setMaterialTexture( 0, driver->getTexture("texturas/metal.png") );
    modelo->setPosition(core::vector3df(170,0,50));

    b2BodyDef bodyDef;
    bodyDef.type= b2_dynamicBody;
    bodyDef.position.Set(170, 50);
    iworld= World::Instance();
    body= iworld->getWorld()->CreateBody(&bodyDef);

    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(tam/2, tam/2);
    body->CreateFixture(&bodyShape, 1.0f);

    cuboProta = modelo->getPosition();

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyShape;
    fixtureDef.friction = 100.f;
    fixtureDef.restitution  = 0.f;
    fixtureDef.density  = 100.f;
    body->CreateFixture(&fixtureDef);
}

core::vector3df Player::getPosicionProta(){
    return modelo->getPosition();
}

core::vector3df Player::getCuboProta(){
    return modelo->getPosition();
}

void Player::setPosition(core::vector3df vec){
    modelo->setPosition(vec);

}

b2Body* Player::getBody(){
    return body;
}


void Player::moverBody(core::vector3df vec){

    movx = vec.X;
    movy = vec.Z;
    double modulo = sqrt((movx*movx) + (movy*movy));
    if(modulo != 0){
        movx = (movx / modulo) * velocidad * 0.70;
        movy = (movy / modulo) * velocidad * 0.70;
    }

    body->SetLinearVelocity(b2Vec2(movx, movy));

}

void Player::setCuboProta(core::vector3df cb){
    cuboProta = cb;
}

scene::IMeshSceneNode* Player::getModelo(){
    return modelo;
}

float Player::getVida(){
    return vida;
}

int Player::getLaser(){
    return balas;
}
void Player::setNoMuerto(){

}
void Player::setLaser(int l){
    balas = l;
}

void Player::setVida(float v){
vida=v;
}

void Player::muerte(){
 smgr1->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(255, 255, 0, 0));
}
