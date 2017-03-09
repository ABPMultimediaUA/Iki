#include "Enemy.h"
#include "Fachada/GraphicsFacade.h"
#include "PatrolPoint.h"
#include "PhisicsWorld.h"

void Enemy::patrullar()
{

   if(posaux.Distance(pRuta->getPunto()) >0.1) //AVANZAR
    {
        posinit.Normalize();
        posaux = posaux + posinit * avMovement;
    }
    else //CUANDO LLEGA A UN PUNTO PATRULLA
    {
        posaux = pRuta->getPunto();
        if(direccion == 0){
            if(pRuta->getNext() == pRuta->getPrev())
                direccion = 1;
            pRuta = pRuta->getNext();

        }else{
            if(pRuta->getNext() == pRuta->getPrev())
                direccion = 0;
            pRuta = pRuta->getPrev();
        }

        posinit = pRuta->getPunto() - posaux;

    }
    posicion = posaux;
    angulo = atan2f((pRuta->getPunto().Z-posicion.Z) ,-(pRuta->getPunto().X-posicion.X)) * 180.f /PI;
    setPosition(posicion);

}

void Enemy::vigilar(){

}



