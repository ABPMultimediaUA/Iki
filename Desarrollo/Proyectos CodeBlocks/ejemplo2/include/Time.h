#ifndef TIME_H
#define TIME_H

#include <irrlicht.h>

using namespace irr;


class Time  {

 public:
   void set(IrrlichtDevice *device);
   void reset();
   void update();
   void setMomento();
   u32 getTime();
   f32 getTimeFactor();
   u32 getMomento();

 protected:

 private:
   u32 momento;
   u32 tiempo;
   u32 m_Time;
   u32 m_DeltaTime;
   irr::f32 m_TimeFactor;
   IrrlichtDevice *m_device;



};

#endif
