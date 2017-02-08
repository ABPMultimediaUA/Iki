#include "..\include\Time.h"

void Time::set(IrrlichtDevice *device)
{
    m_device=device;
    reset();
}

void Time::reset()
{
    m_Time = m_device->getTimer()->getTime();
}

f32 Time::getTimeFactor()
{
    return m_TimeFactor;
}
float Time::setMomento()
{
        //printf("entraaaa");
        momento = m_device->getTimer()->getTime() / 1000.f;
        //printf("momento: %0.2f \n", momento);
        return momento;
}
float Time::getMomento()
{
    return momento;
}
float Time::getTime()
{
    tiempo = m_device->getTimer()->getTime() / 1000.f;
    return tiempo;
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
