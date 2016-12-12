#include "..\include\Time.h"

   void Time::set(IrrlichtDevice *device)
   {
      m_device=device;
      reset();
   }

   void Time::reset() {
       m_Time = m_device->getTimer()->getTime();
       }
    u32 Time::getTime(){
        tiempo = m_device->getTimer()->getTime() / 1000.f;
        return tiempo;
    }
    f32 Time::getTimeFactor(){
        return m_TimeFactor;
    }
   void Time::setMomento(){
       momento=m_device->getTimer()->getTime() / 1000.f;
   }
   u32 Time::getMomento(){
       return momento;;
   }
   void Time::update()
      {
      /*m_DeltaTime = m_device->getTimer()->getTime() - m_Time;
      m_Time =+ m_DeltaTime;
      m_TimeFactor = m_DeltaTime * 0.001f;*/
      m_DeltaTime= m_device->getTimer()->getTime();
      m_TimeFactor = (f32)(m_DeltaTime - m_Time) / 1000.f;
      m_Time = m_DeltaTime;
      }
