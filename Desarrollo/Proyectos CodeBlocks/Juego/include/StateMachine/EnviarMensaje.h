#ifndef ENVIAR_MENSAJE
#define ENVIAR_MENSAJE
#pragma warning (disable:4786)

#include <set>
#include <string>


#include "Mensaje.h"
/*
Esta clase crea los mensajes los cuales son enviados inmediatamente
o se almacenan en la una cola para enviarlos pasados un tiempo
*/

class GameEntity;


//to make life easier...
#define EnviarMsg EnviarMensaje::Instance()

//to make code easier to read
const double SEND_MSG_IMMEDIATELY = 0.0;
const int    NO_ADDITIONAL_INFO   = 0;
const int    SENDER_ID_IRRELEVANT = -1;


class EnviarMensaje
{
private:

  //Set es un contenedor asociativo que contiene un conjunto ordenado de objetos unicos de tipo Key.
  //La clasificacion se realiza mediante la tecla de funcion de comparacion compara.
  //Cola de prioridad
  std::set<Mensaje> PriorityQ;

  //Este metodo llama a la funcion miembro de manejo de mensajes de la
  //entidad, receptor, con el mensaje recien creado
  void Descargar(GameEntity* receptor, const Mensaje& msg);

  EnviarMensaje(){}

  //copy ctor and assignment should be private
  EnviarMensaje(const EnviarMensaje&);
  EnviarMensaje& operator=(const EnviarMensaje&);

public:
  //Es SINGLETON
  static EnviarMensaje* Instance();

  //send a message to another agent. Receiving agent is referenced by ID.
  void Envio(double      tiempoEnvio,
                   int         emisor,
                   int         receptor,
                   int         msg,
                   void*       info);

  //send out any delayed messages. This method is called each time through
  //the main game loop.
  void EnvioMensajePendiente();
};


#endif

