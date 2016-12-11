#ifndef TIME_H
#define TIME_H

#include <irrlicht.h>

using namespace irr;


class Time  {

 public:
   void set(IrrlichtDevice *device);
   void reset();
   void update();
   u32 getTime();

 protected:

 private:
   int m_Time;
   int m_DeltaTime;
   irr::f32 m_TimeFactor;
   IrrlichtDevice *m_device;



};

#endif
