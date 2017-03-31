#include "EnviarMensaje.h"
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

    GameEntity* receptor = EntityMgr->getEntityByID(receiver);
    if (receptor == NULL)
    {
        return;
    }

    Mensaje Mensaje(0, sender, receiver, msg, AdditionalInfo);

    if (delay <= 0.0)
    {
        Descargar(receptor, Mensaje);
    }

    else
    {

        double CurrentTime = PhisicsWorld::getInstance()->getTimeStamp();
        Mensaje.TiempoEnvio = CurrentTime + delay;
        PriorityQ.insert(Mensaje);
    }
}


void EnviarMensaje::EnvioMensajePendiente()
{
  double CurrentTime = PhisicsWorld::getInstance()->getTimeStamp();

  while( !PriorityQ.empty() &&
	     (PriorityQ.begin()->TiempoEnvio < CurrentTime) &&
         (PriorityQ.begin()->TiempoEnvio > 0) )
  {
    const Mensaje& Mensaje = *PriorityQ.begin();

    GameEntity* receptor = EntityMgr->getEntityByID(Mensaje.Receptor);
    Descargar(receptor, Mensaje);
    PriorityQ.erase(PriorityQ.begin());
  }
}



