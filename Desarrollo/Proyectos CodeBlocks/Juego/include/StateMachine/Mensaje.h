#ifndef MENSAJE
#define MENSAJE

#include <iostream>
#include <math.h>

struct Mensaje
{
  float       TiempoEnvio;
  int          Emisor;
  int          Receptor;
  int          Msg;
  void*        Info;


  Mensaje():TiempoEnvio(-1),
                  Emisor(-1),
                  Receptor(-1),
                  Msg(-1)
  {}


  Mensaje(float time,
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


const float SmallestDelay = 0.25;


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

template <class T>
inline T DereferenceToType(void* p)
{
  return *(T*)(p);
}

#endif // MENSAJE
