#ifndef TIME_H
#define TIME_H

#include <irrlicht.h>

using namespace irr;


class Time  {

 public:
   void set(IrrlichtDevice *device);
   void reset();
   void update();
   float setMomento();
   float getTime();
   f32 getTimeFactor();
   float getMomento();

 protected:

 private:
   float momento;
   float tiempo;
   u32 m_Time;
   u32 m_DeltaTime;
   irr::f32 m_TimeFactor;
   IrrlichtDevice *m_device;



};

#endif
