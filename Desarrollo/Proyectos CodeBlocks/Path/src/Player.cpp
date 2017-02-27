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
    rayo2=smgr1->getGeometryCreator()->createCubeMesh(core::vector3df(10.f, 0.5f, 0.5f));
    modelo2 = smgr1->addMeshSceneNode(rayo2);
    escalado= core::vector3df(1,0,1);

    esfera= smgr->addCubeSceneNode(2);
    esfera->setMaterialFlag(video::EMF_LIGHTING, false);
    esfera->setScale(escalado);
    esfera->setPosition(core::vector3df(170,0,50));

    modelo = smgr->addCubeSceneNode(tam);
    modelo->setMaterialFlag(video::EMF_LIGHTING, false);
    modelo->setMaterialTexture( 0, driver->getTexture("texturas/metal.png") );
    //modelo->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
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
    input.maxFraction	=	1.0f;
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
void Player::setMuro(Map* Mapa){
        mapa = Mapa;
}
bool Player::isPathObstructured(vector3df destino){

    input.p1.Set(this->getBody()->GetPosition().x, this->getBody()->GetPosition().y);	//	Punto	inicial	del	rayo (la posicion del prota)
    input.p2.Set(destino.X, destino.Z);	//	Punto final del	rayo (la posicion que le paso)

    distancia = sqrt(pow(input.p2.x-input.p1.x, 2)+pow(input.p2.y-input.p1.y, 2));
    angulo = atan2f((input.p2.y-input.p1.y) , -(input.p2.x-input.p1.x)) * 180.f / irr::core::PI;
    modelo2->setScale(core::vector3df(distancia/10, 0.5f, 0.5f));
    modelo2->setPosition(core::vector3df((input.p2.x+input.p1.x)/2,0,(input.p2.y+input.p1.y)/2));
    modelo2->setRotation(core::vector3df(0,angulo,0));


    ///colision con puertas
    if (mapa->puertas->at(0)->body->GetFixtureList()->RayCast(&output,input,0)){
        return true;
    }
    else if (mapa->puertas->at(1)->body->GetFixtureList()->RayCast(&output,input,0)){
        return true;
    }
    ///colision con paredes
    for (int i = 0; i < mapa->muros->size(); i++) {
            if (mapa->muros->at(i)->body->GetFixtureList()->RayCast(&output,input,0)){
                return true;
            }

    }

    return false;
}
