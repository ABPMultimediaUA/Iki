#include "Enemies/StateMachine/EnviarMensaje.h"
#include "GameEntity.h"
#include "PhisicsWorld.h"
#include "EntityManager.h"


using std::set;

EnviarMensaje* EnviarMensaje::Instance()
{
  static EnviarMensaje instance;

  return &instance;
}

void EnviarMensaje::Descargar(GameEntity* receptor, const Mensaje& mensaje)
{
    if(!receptor->HandleMessage(mensaje)){
        std::cout<<"No se ha podido enviar el mensaje"<<std::endl;
    }
}

void EnviarMensaje::Envio(  double       delay,
                            int          sender,
                            int          receiver,
                            int          msg,
                            void*        AdditionalInfo )
{

    //get a pointer to the receiver
    GameEntity* receptor = EntityMgr->getEntityByID(receiver);

    //make sure the receiver is valid
    if (receptor == NULL)
    {
        return;
    }

    //create the Mensaje
    Mensaje Mensaje(0, sender, receiver, msg, AdditionalInfo);

    //if there is no delay, route Mensaje immediately
    if (delay <= 0.0)
    {
        //send the Mensaje to the recipient
        Descargar(receptor, Mensaje);
    }

    //else calculate the time when the Mensaje should be dispatched
    else
    {

        double CurrentTime = PhisicsWorld::getInstance()->getTimeStamp();

        Mensaje.TiempoEnvio = CurrentTime + delay;

        //and put it in the queue
        PriorityQ.insert(Mensaje);
    }
}


void EnviarMensaje::EnvioMensajePendiente()
{
  //first get current time
  double CurrentTime = PhisicsWorld::getInstance()->getTimeStamp();

  //now peek at the queue to see if any telegrams need dispatching.
  //remove all telegrams from the front of the queue that have gone
  //past their sell by date
  while( !PriorityQ.empty() &&
	     (PriorityQ.begin()->TiempoEnvio < CurrentTime) &&
         (PriorityQ.begin()->TiempoEnvio > 0) )
  {
    //read the Mensaje from the front of the queue
    const Mensaje& Mensaje = *PriorityQ.begin();

    //find the recipient
    GameEntity* receptor = EntityMgr->getEntityByID(Mensaje.Receptor);

    //send the Mensaje to the recipient
    Descargar(receptor, Mensaje);

	//remove it from the queue
    PriorityQ.erase(PriorityQ.begin());
  }
}



