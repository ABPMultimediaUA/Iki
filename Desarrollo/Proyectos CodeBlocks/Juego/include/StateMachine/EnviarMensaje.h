#ifndef ENVIAR_MENSAJE
#define ENVIAR_MENSAJE
#pragma warning (disable:4786)

#include <set>
#include <string>


#include "Mensaje.h"
/*

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

  //a std::set is used as the container for the delayed messages
  //because of the benefit of automatic sorting and avoidance
  //of duplicates. Messages are sorted by their dispatch time.
  std::set<Mensaje> PriorityQ;

  //this method is utilized by DispatchMsg or DispatchDelayedMessages.
  //This method calls the message handling member function of the receiving
  //entity, Receptor, with the newly created telegram
  void Descargar(GameEntity* Receptor, const Mensaje& msg);

  EnviarMensaje(){}

  //copy ctor and assignment should be private
  EnviarMensaje(const EnviarMensaje&);
  EnviarMensaje& operator=(const EnviarMensaje&);

public:

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


*/
#endif

