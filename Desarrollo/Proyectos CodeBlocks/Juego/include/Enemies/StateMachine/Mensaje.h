#ifndef MENSAJE
#define MENSAJE

#include <iostream>
#include <math.h>

struct Mensaje
{
  int          Emisor;
  int          Receptor;
  //the message itself. These are all enumerated in the file
  //"MessageTypes.h"
  int          Msg;
  double       TiempoEnvio;
  void*        Info;


  Mensaje():TiempoEnvio(-1),
                  Emisor(-1),
                  Receptor(-1),
                  Msg(-1)
  {}


  Mensaje(double time,
           int    sender,
           int    receiver,
           int    msg,
           void*  info = NULL): TiempoEnvio(time),
                               Emisor(sender),
                               Receptor(receiver),
                               Msg(msg),
                               Info(info)
  {}

};


//these telegrams will be stored in a priority queue. Therefore the >
//operator needs to be overloaded so that the PQ can sort the telegrams
//by time priority. Note how the times must be smaller than
//SmallestDelay apart before two Telegrams are considered unique.
const double SmallestDelay = 0.25;


inline bool operator==(const Mensaje& t1, const Mensaje& t2)
{
  return ( fabs(t1.TiempoEnvio-t2.TiempoEnvio) < SmallestDelay) &&
          (t1.Emisor == t2.Emisor)        &&
          (t1.Receptor == t2.Receptor)    &&
          (t1.Msg == t2.Msg);
}

inline bool operator<(const Mensaje& t1, const Mensaje& t2)
{
  if (t1 == t2)
  {
    return false;
  }

  else
  {
    return  (t1.TiempoEnvio < t2.TiempoEnvio);
  }
}

inline std::ostream& operator<<(std::ostream& os, const Mensaje& t)
{
  os << "time: " << t.TiempoEnvio << "  Emisor: " << t.Emisor
     << "   Receptor: " << t.Receptor << "   Msg: " << t.Msg;

  return os;
}

//handy helper function for dereferencing the Info field of the Mensaje
//to the required type.
template <class T>
inline T DereferenceToType(void* p)
{
  return *(T*)(p);
}

#endif // MENSAJE
