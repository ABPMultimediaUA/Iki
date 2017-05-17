#ifndef TRIGGER_TORRETA_H
#define TRIGGER_TORRETA_H

#include <Trigger.h>


class Trigger_Torreta : public Trigger
{
    public:
        Trigger_Torreta(float x, float y, float z);
        virtual ~Trigger_Torreta();

        void Try(GameEntity*);
        void Update();

        void triggerDisparado();
        void calcularAngulo(Structs::TPosicion);
        void disparo();

    protected:

    private:
        bool fired;
        MeshSceneNode* modeloDisparo;
};

#endif // TRIGGER_TORRETA_H
