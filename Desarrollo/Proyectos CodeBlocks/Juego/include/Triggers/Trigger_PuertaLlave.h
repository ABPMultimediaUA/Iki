#ifndef TRIGGER_PUERTALLAVE_H
#define TRIGGER_PUERTALLAVE_H

#include <Trigger.h>


class Trigger_PuertaLlave : public Trigger
{
    public:
        Trigger_PuertaLlave(float x, float z, float r);
        virtual ~Trigger_PuertaLlave();

        void Try(GameEntity*);
        void Update();

        void triggerDisparado();
        bool isPuerta(){return true;}
        bool isPuertaAbierta() {return abierta;}

    protected:

    private:
        f32 aniTime, time2=0;
        MeshSceneNode* puerta;
        bool fired = false;
        bool fired2 = false;
        bool abierta = false;
        float mx,mz,ma;
};

#endif // TRIGGER_PUERTALLAVE_H
