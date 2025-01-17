#include "Player_Animado.h"
#include <Box2D/Box2D.h>


using namespace irr;

Player_Animado::Player_Animado()
{
    //ctor
}

Player_Animado::~Player_Animado()
{
    //dtor
}

void Player_Animado::inicializar(scene::ISceneManager* smgr,video::IVideoDriver* driver){
    tam= 6;
    escalado1= core::vector3df(0.04f,0.04f,0.04f);
    escalado2= core::vector3df(1,0.01f,1);

    esfera= smgr->addCubeSceneNode(6);
    esfera->setMaterialFlag(video::EMF_LIGHTING, false); //Meter en el interfaz
    esfera->setScale(escalado2);
    esfera->setPosition(core::vector3df(0,0,10));


    //modelo = smgr->addCubeSceneNode(tam);
    mesh = smgr->getMesh("media/tank.md2");
    modelo= smgr->addAnimatedMeshSceneNode(mesh);
    modelo->setScale(escalado1);

    //modelo->setMaterialFlag(video::EMF_LIGHTING, false);
    //modelo->setMaterialTexture( 0, driver->getTexture("texturas/metal.png") );
   // modelo->setMaterialType( video::EMT_SOLID );
    modelo->setPosition(core::vector3df(0,0,-10));

    b2BodyDef bodyDef;
    bodyDef.type= b2_dynamicBody;
    bodyDef.position.Set(0, -10);
    iworld= World::Instance();
    body= iworld->getWorld()->CreateBody(&bodyDef);

    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(tam/2, tam/2);
    body->CreateFixture(&bodyShape, 1.0f);

    cuboProta = modelo->getPosition();

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyShape;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution  = 0.9f;
    fixtureDef.density  = 1.f;
    body->CreateFixture(&fixtureDef);
}

core::vector3df Player_Animado::getPosicionProta(){
    return modelo->getPosition();
}

void Player_Animado::setRotarProta(core::vector3df vecu){
    esfera->setRotation(vecu);
    modelo->setRotation(vecu);
}

void Player_Animado::setPosition(core::vector3df vec){
    modelo->setPosition(vec);
    esfera->setPosition(core::vector3df(vec.X, vec.Y, vec.Z));
}

b2Body* Player_Animado::getBody(){
    return body;
}

void Player_Animado::setPosicionBody(float ang){
    //body->SetTransform(b2Vec2(cuboProta.X, cuboProta.Z), ang);
    /*std::cout << "cubo X: "<<cuboProta.Z<<" \n";
    std::cout << "cubo Z: "<<cuboProta.Z<<" \n";
    std::cout << "body X: "<<body->GetPosition().x  <<" \n";
    std::cout << "body Z: "<<body->GetPosition().y  <<" \n";
    std::cout << "-------------- \n";*/
}

void Player_Animado::moverBody(core::vector3df vec){
    //body->ApplyLinearImpulse(b2Vec2(0, 5.0), b2Vec2(vec.X, vec.Z), true);
    movx = vec.X;
    movy = vec.Z;
    double modulo = sqrt((movx*movx) + (movy*movy));
    if(modulo != 0){
        movx = (movx / modulo) * MOV_SPEED;
        movy = (movy / modulo) * MOV_SPEED;
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

void Player_Animado::setCuboProta(core::vector3df cb){
    cuboProta = cb;
}

irr::scene::IAnimatedMesh* Player_Animado::getModelo(){
    return mesh;
}
