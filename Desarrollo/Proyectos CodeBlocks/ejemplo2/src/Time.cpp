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
        return (u32)m_Time;
    }
   void Time::update()
      {
      m_DeltaTime = m_device->getTimer()->getTime() - m_Time;
      m_Time =+ m_DeltaTime;
      m_TimeFactor = m_DeltaTime * 0.001f;
      }
