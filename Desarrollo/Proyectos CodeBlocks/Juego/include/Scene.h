#ifndef SCENE_H
#define SCENE_H

#include "Structs.h"
#include "Camera.h"
#include "Player.h"
#include "World.h"
#include "TriggerSystem.h"

class Scene
{
    public:
        Scene();
        virtual ~Scene();
        void inicializar_escena();
        void bucle_juego();

    protected:

    private:

        Camera *camara;
        World *world;
        TriggerSystem *triggersystem;
        Player *player;
        Structs::TPosicion mousePosition;
        f32 TimeStamp;
        f32 DeltaTime;
};

#endif // SCENE_H
