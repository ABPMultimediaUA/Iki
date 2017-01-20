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
    vida=200;
    balas= 1;
    smgr1=smgr;
    escalado= core::vector3df(1,0,1);

    esfera= smgr->addCubeSceneNode(2);
    esfera->setMaterialFlag(video::EMF_LIGHTING, false);
    esfera->setScale(escalado);
    esfera->setPosition(core::vector3df(45,0,0));

    modelo = smgr->addCubeSceneNode(tam);
    modelo->setMaterialFlag(video::EMF_LIGHTING, false);
    modelo->setMaterialTexture( 0, driver->getTexture("texturas/metal.png") );
    //modelo->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    modelo->setPosition(core::vector3df(45,0,0));

    b2BodyDef bodyDef;
    bodyDef.type= b2_dynamicBody;
    bodyDef.position.Set(45, 0);
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
    esfera->setPosition(core::vector3df(vec.X, vec.Y, vec.Z));
}

b2Body* Player::getBody(){
    return body;
}

void Player::setPosicionBody(float ang){
    //body->SetTransform(b2Vec2(cuboProta.X, cuboProta.Z), ang);
    /*std::cout << "cubo X: "<<cuboProta.Z<<" \n";
    std::cout << "cubo Z: "<<cuboProta.Z<<" \n";
    std::cout << "body X: "<<body->GetPosition().x  <<" \n";
    std::cout << "body Z: "<<body->GetPosition().y  <<" \n";
    std::cout << "-------------- \n";*/
}

bool Player::cogerObjeto(core::vector3df vec, scene::ISceneManager* smgr){
    bool golpeado = false;
    if(vec.getLength() <= 8){
        smgr->getMeshManipulator()->setVertexColors(esfera->getMesh(),video::SColor(0, 128, 128, 0));
        body->SetLinearVelocity(b2Vec2(0, 0));
        golpeado = true;
    }else{
        movx = vec.X;
        movy = vec.Z;
        double modulo = sqrt((movx*movx) + (movy*movy));
        if(modulo != 0){
            movx = (movx / modulo) * velocidad;
            movy = (movy / modulo) * velocidad;
        }

        smgr->getMeshManipulator()->setVertexColors(esfera->getMesh(),video::SColor(0, 0, 0, 0));
        body->SetLinearVelocity(b2Vec2(movx, movy));
    }
    return golpeado;
}

bool Player::atacar(core::vector3df vec, scene::ISceneManager* smgr){
    bool golpeado = false;
    if(vec.getLength() <= 10){
        //smgr->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(0, 128, 128, 0));
        body->SetLinearVelocity(b2Vec2(0, 0));
        golpeado = true;
    }else{
        movx = vec.X;
        movy = vec.Z;
        double modulo = sqrt((movx*movx) + (movy*movy));
        if(modulo != 0){
            movx = (movx / modulo) * MOV_SPEED;
            movy = (movy / modulo) * MOV_SPEED;
        }

       // smgr->getMeshManipulator()->setVertexColors(esfera->getMesh(),video::SColor(0, 0, 0, 0));
        body->SetLinearVelocity(b2Vec2(movx, movy));
    }
    return golpeado;
}

void Player::moverBody(core::vector3df vec){
    //body->ApplyLinearImpulse(b2Vec2(0, 5.0), b2Vec2(vec.X, vec.Z), true);
    movx = vec.X;
    movy = vec.Z;
    double modulo = sqrt((movx*movx) + (movy*movy));
    if(modulo != 0){
        movx = (movx / modulo) * velocidad * 0.70;
        movy = (movy / modulo) * velocidad * 0.70;
    }

    body->SetLinearVelocity(b2Vec2(movx, movy));
    //body->ApplyForce(b2Vec2(movx, movy), b2Vec2(movx, movy), true);
    //std::cout << "body X: "<<body->GetPosition().x  <<" \n";
    //std::cout << "body Z: "<<body->GetPosition().y  <<" \n";

    //body->ApplyLinearImpulse(b2Vec2(0.1, 0.1), body->GetPosition());
    /*if(vec.X != body->GetPosition().x){
       //body->ApplyForce( b2Vec2(force,0), body->GetWorldCenter() );
    }
    if(vec.Y != body->GetPosition().y){
        //body->SetLinearVelocity(b2Vec2(0.0, 15.0));
    }*/
}

void Player::setCuboProta(core::vector3df cb){
    cuboProta = cb;
}

scene::IMeshSceneNode* Player::getModelo(){
    return modelo;
}
scene::IMeshSceneNode* Player::getEsfera(){
    return esfera;
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
