#include "Player.h"
#include "Fachada/GraphicsFacade.h"
#include "PhisicsWorld.h"
#include "Enemies/Path/PathFinding.h"
#include "Enemies/Path/PathPlanner.h"
#include "MapComponent.h"
#include "PhisicsWorld.h"
#include "Muerto.h"
#include "GUI/HUD.h"


Player::Player()
{
    rayo = new Player_Ray();
}

Player::~Player()
{
    delete rayo;
    delete aniMesh;
    body->GetWorld()->DestroyBody(body);
}

void Player::inicializar_player(Map* m, int nivel){

    velocidad = 2;
    id = 0;
    vida = 100;
    EntityMgr->registrarEntity(this);

    Mapa = m;
    grafo = Mapa->getGrafo();
    //path = new PathFinding(grafo,this);
    path2 = new PathPlanner(grafo,this);

    Structs::TPosicion posicionInicial;

    if(nivel == 1) posicionInicial = {170,0,50};
    if(nivel == 2) {posicionInicial = {190,0,50}; mousePosition = {190,0,50};}
    Structs::TColor color = {121,85,61,0};

    puntero = new MeshSceneNode("resources/Modelos/puntero.obj");
    puntero->setTexture("resources/Texturas/tarjetaTex.png");
    puntero->setVisible(false);
    puntero->setScale({5,5,5});

    //aniMesh = new AnimatedMesh("resources/Modelos/Prota2.obj", color, posicionInicial, 0);

    animacionAndar = new Animaciones("resources/Animaciones/andar_OBJ_Seq/andar.00",color,posicionInicial,90,31,48, "resources/Texturas/Protatextura.png",2.f,1);
    modelos = animacionAndar->getModelosAnimacion(1);

    animacionSigilo = new Animaciones("resources/Animaciones/sigilo_OBJ_Seq/sigilo.00",color,posicionInicial,90,57,34, "resources/Texturas/Protatextura.png",2.f,2);
    modelosSigilo = animacionSigilo->getModelosAnimacion(2);

    aniMesh = new AnimatedMesh("resources/Animaciones/andar_OBJ_Seq/andar0000.obj", color, posicionInicial, 0);
    aniMesh->setTexture("resources/Texturas/Protatextura.png");
    aniMesh->setScale(2.4);
    aniMesh->setPosition({posicionInicial.X,4,posicionInicial.Z});
    //aniMesh->setVisible(true);


    posicion = posicionInicial;


    radio = 1.0;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    if(nivel == 1) bodyDef.position.Set(170, 50);
    if(nivel == 2) bodyDef.position.Set(190, 50);

    body = PhisicsWorld::getInstance()->getWorld()->CreateBody(&bodyDef);

    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(1,1);
    body->CreateFixture(&bodyShape, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyShape;
    fixtureDef.density  = 1.f;
    fixtureDef.friction = 1.f;
    fixtureDef.restitution  = 0.f;
    body->CreateFixture(&fixtureDef);
    //Para los ray!
    input.maxFraction	=	1.0f;
    input2.maxFraction  =   1.0f;

    ruido = new Trigger_Ruido();
    ruido->AddCircularRegion(posicion, 20);
    isMoving = false;
    nivel_acabado = false;
    reintentar = false;

    HUD::getInstance()->inicializar_HUD();
}
void Player::MoverPlayer(Structs::TPosicion p1,Structs::TPosicion p2){
    angulo = atan2f((p1.Z-posicion.Z) ,
                          -(p1.X-posicion.X)) * 180.f / irr::core::PI;
    body->SetTransform(body->GetPosition(), angulo);
    moverBody(p2);
    posicion = {body->GetPosition().x, 0, body->GetPosition().y};

    //aniMesh2->setPosition(posicion);
    //aniMesh2->setRotation(body->GetAngle());
}
void Player::runAnimacion(int numeroAnimacion){
    tiempoJuego = PhisicsWorld::getInstance()->getTimeStamp()/1000.f;
    tiempoAnimacion = tiempoJuego - tiempoAnimacion;
    aniMesh->setVisible(false);
    if(numeroAnimacion == 1){//Andar
        animacionSigilo->getActual()->setVisible(false);
        animacionAndar->setActual(modelos[j]);
        animacionAndar->setPosition(posicion);
        animacionAndar->setRotation(body->GetAngle());
    if( tiempoAnimacion > 0.025f){
        j++;
        tiempoAnimacion = tiempoJuego;
    }
    if(j>=modelos.size())
        j=0;

    }
    if(numeroAnimacion == 2){//Sigilo
        animacionAndar->getActual()->setVisible(false);
        animacionSigilo->setActual(modelosSigilo[h]);
        animacionSigilo->setPosition(posicion);
        animacionSigilo->setRotation(body->GetAngle());
    if( tiempoAnimacion > 0.02f){
        h++;
        tiempoAnimacion = tiempoJuego;
    }
    if(h>=modelosSigilo.size())
        h=0;
    }

}
void Player::meshQuietoParado(){
    animacionAndar->getActual()->setVisible(false);
    animacionSigilo->getActual()->setVisible(false);
    aniMesh->setVisible(true);
    aniMesh->setPosition({posicion.X+2,4,posicion.Z});
    aniMesh->setRotation(angulo+90);
}
void Player::moverBody(Structs::TPosicion vec){
    vec.Normalize();
    float movx = vec.X * velocidad;
    float movy = vec.Z * velocidad;

    if (vec == quietoParado){
        isMoving = false;
        speed = 0; //El speed es para los sonidos
        meshQuietoParado();
    }
    else{
        isMoving = true;
         ///COMPRUEBO SI TENGO SHIFT OPRIMIDO
        if(MyEventReceiver::getInstance().isKeyDown(KEY_LSHIFT)){
            //std::cout<<"shift oprimidooo"<<std::endl;
            speed = 1;
            velocidad = 1;
            HUD::getInstance()->sigiloUsed();
            runAnimacion(2);
        }
        else {
            speed = 2;
            velocidad = 2;
            HUD::getInstance()->sigiloNotUsed();
            runAnimacion(1);
        }

         if(velocidad > 2.f){
            comprobarVelocidad();
            speed = 3;
        }
    }
    body->SetLinearVelocity(b2Vec2(movx, movy));
}

void Player::comprobarVelocidad(){
    if(GraphicsFacade::getInstance().getTimer()->getTime()/1000.f - tiempo_con_mas_speed > 2.f){
        velocidad = 2;
        tiempo_con_mas_speed = GraphicsFacade::getInstance().getTimer()->getTime()/1000.f;
    }
}

bool Player::getMoving(){
    return isMoving;
}

void Player::TriggerRuido(){
    if (isMoving){
        ruido->activar();
        ruido->MoveRegion(this->posicion);
    }else{
        ruido->desactivar();
    }
}

void Player::sonidosMovimiento()
{
    switch(speed){
        case 0:
            SoundMgr->soundStop("Player/andarsigiloso");
            SoundMgr->soundStop("Player/pasosnormales");
            SoundMgr->soundStop("Player/articulacion2");
            SoundMgr->soundStop("Player/correr");
        break;
        case 1:
            SoundMgr->soundStop("Player/pasosnormales");
            SoundMgr->soundStop("Player/articulacion2");
            SoundMgr->soundStop("Player/correr");
            if (!SoundMgr->isPlaying("Player/andarsigiloso")){
                 SoundMgr->playSonido("Player/andarsigiloso");
            }
        break;
        case 2:
            SoundMgr->soundStop("Player/andarsigiloso");
            SoundMgr->soundStop("Player/correr");
            if (!SoundMgr->isPlaying("Player/pasosnormales")){
                 SoundMgr->playSonido("Player/pasosnormales");
            }
            if (!SoundMgr->isPlaying("Player/articulacion2")){
                 SoundMgr->playSonido("Player/articulacion2");
            }
        break;
        case 3:
            SoundMgr->soundStop("Player/andarsigiloso");
            SoundMgr->soundStop("Player/pasosnormales");
            SoundMgr->soundStop("Player/articulacion2");
            if(!SoundMgr->isPlaying("Player/correr")){
                 SoundMgr->playSonido("Player/correr");
            }
        break;
    }
}

void Player::CogerMunicion()
{
    rayo->cogerBalas();
    HUD::getInstance()->activateMunicion();
}
bool Player::isPathObstructured(Structs::TPosicion destino){
    input.p1.Set(this->getBody()->GetPosition().x, this->getBody()->GetPosition().y);	//	Punto	inicial	del	rayo (la posicion del prota)
    input.p2.Set(destino.X, destino.Z);	//	Punto final del	rayo (la posicion que le paso)

    ///colision con paredes
    for (int i = 0; i < Mapa->getMuros().size(); i++) {
        if (Mapa->getMuros().at(i)->getBody()->GetFixtureList()->RayCast(&output,input,0)){
            return true;
        }
    }

    return false;
}
bool Player::canWalkBetween(Structs::TPosicion desde, Structs::TPosicion hasta){

     input2.p1.Set(desde.X, desde.Z);	//	Punto	inicial	del	rayo
     input2.p2.Set(hasta.X, hasta.Z);	//	Punto	final	del	rayo

     ///colision con paredes
    for (int i = 0; i < Mapa->getMuros().size(); i++) {
        if (Mapa->getMuros().at(i)->getBody()->GetFixtureList()->RayCast(&output2,input2,0)){
            return false;
        }
    }

    return true;
}

bool Player::imSeeingThisEnemy(Enemy* enemy){

    Structs::TPosicion p;
    if(p.isSecondInFOVOfFirst(posicion,mirarHacia,enemy->getPosition(),90*PI/180) && !isPathObstructured(enemy->getPosition()))
        return true;
    else
        return false;
}

void Player::calcularMirarHacia(Structs::TPosicion mousePos){

    mirarHacia = mousePos - getPosition();
}

void Player::CogerVida(){
    vida+=20;
    if (vida > 100) vida = 100;
}

void Player::CogerLlave(){
    llaves++;
    HUD::getInstance()->activateTarjeta();
}

void Player::UsarLlave(){
    llaves--;
    HUD::getInstance()->desactivateTarjeta();
}

void Player::NecesitoLlave(){
    HUD::getInstance()->activateNotTarjeta();
}

void Player::subirVelocidad(){
    velocidad *= 2;
    tiempo_con_mas_speed = GraphicsFacade::getInstance().getTimer()->getTime()/1000.f;
    HUD::getInstance()->activateAceite();
}

bool Player::mostrarMensajePalanca(){
    HUD::getInstance()->activatePalanca();
    if(MyEventReceiver::getInstance().isKeyDown(KEY_KEY_E)){
        return true;
    }
    return false;
}

void Player::desmostrarMensajePalanca(){
    HUD::getInstance()->desactivatePalanca();
}

void Player::calcularAngulo(Structs::TPosicion p1){
    angulo = atan2f((p1.Z-posicion.Z) ,
                -(p1.X-posicion.X)) * 180.f / irr::core::PI;
}

void Player::UpdateRayo(Camera* camara){
    rayo->borrar_rayo();

    if(rayo->getBalas() > 0 && GraphicsFacade::getInstance().getTimer()->getTime()/1000.f - rayo->getVidaRayo() > 1.5){
        HUD::getInstance()->rayoNotUsed();
    }
    if(MyEventReceiver::getInstance().isKeyDown(KEY_KEY_W)){
        if(rayo->getBalas() > 0){
            if(GraphicsFacade::getInstance().getTimer()->getTime()/1000.f - rayo->getVidaRayo() > 1.5){

                HUD::getInstance()->rayoUsed();
                GraphicsFacade::getInstance().cambiarRay(camara);
                GraphicsFacade::getInstance().interseccionRayPlano(mousePosition);
                angulo = atan2f((mousePosition.Z-posicion.Z) , -(mousePosition.X-posicion.X)) * 180.f / irr::core::PI;
                body->SetTransform(body->GetPosition(), angulo);

                posicion = {body->GetPosition().x, 0, body->GetPosition().y};
                //aniMesh->setPosition(posicion);
                //aniMesh->setRotation(body->GetAngle());
                //std::cout << angulo << std::endl;
                animacionAndar->setRotation(angulo);
                moverBody(quietoParado);
                listaEjes.clear();


                rayo->lanzar_rayo(posicion);
                SoundMgr->playSonido("Player/disparoprota");
            }
        }
        else{
            if (!SoundMgr->isPlaying("Player/error"))
                SoundMgr->playSonido("Player/error");
            HUD::getInstance()->activateNotMunicion();
        }
    }
}

void Player::UpdateAtaque(){
    if(MyEventReceiver::getInstance().isKeyDown(KEY_KEY_Q)){

        moverBody(quietoParado);
        listaEjes.clear();

        std::vector<Enemy*> enemies = EntityManager::Instance()->getEnemigos();
        for(size_t i = 0; i < enemies.size(); i++){
            if(enemies[i]->getPosition().Distance(this->getPosition()) < 8.f){
                if(imSeeingThisEnemy(enemies[i])){
                    if(enemies[i]->getAngulo() - 30 < angulo + 30 && enemies[i]->getAngulo() + 30 > angulo - 30){
                        SoundMgr->playSonido("Player/metal1");
                        enemies[i]->setVida(0);
                        enemies[i]->GetFSM()->ChangeState(Muerto::Instance());
                    }
                    else{
                        enemies[i]->quitarVida();
                    }
                }
               }
        }
    }
}

void Player::UpdateMov(Camera* camara){
    if(MyEventReceiver::getInstance().GetMouseState().RightButtonDown){

        GraphicsFacade::getInstance().cambiarRay(camara);
        //listaNodos.clear();
        listaEjes.clear();
        GraphicsFacade::getInstance().interseccionRayPlano(mousePosition);
        calcularMirarHacia(mousePosition);
        puntero->setPosition(mousePosition);
        puntero->setVisible(true);
        //path->crearPath(posicion,mousePosition,listaNodos);
        path2->crearPath(mousePosition,listaEjes);
        //path2->SmoothPathEdgesQuick(listaEjes);
        //it=listaNodos.begin();
        it2=listaEjes.begin();
    }

    if(!listaEjes.empty() && it2 != listaEjes.end())
        toNextNodo = (*it2).getDestination() - posicion;
    else
        toNextNodo=quietoParado;

    if(toNextNodo.Length() <= 1) //CUANDO LLEGA AL NODO
    {
        moverBody(quietoParado);
        if(!listaEjes.empty() && it2 != listaEjes.end()) //SI AUN NO ES EL ULTIMO NODO
            it2++;
        else{
            puntero->setVisible(false);
        }
    }
    else
    { //CUANDO AUN NO HA LLEGADO A UN NODO
        MoverPlayer((*it2).getDestination(),toNextNodo);
    }
}

void Player::update(Camera* camara){
    if(vida == 0){
        SoundMgr->stopAll();
        HUD::getInstance()->GameOver();
        if(MyEventReceiver::getInstance().GetMouseState().LeftButtonDown){
            reintentar = HUD::getInstance()->comprobarReintentar();
        }
    }else{
        deltaTime = PhisicsWorld::getInstance()->getDeltaTime()/1000.f;
        avMovement = deltaTime * 600;

        TriggerRuido();
        sonidosMovimiento();

        UpdateAtaque();
        UpdateRayo(camara);
        UpdateMov(camara);
    }
}
