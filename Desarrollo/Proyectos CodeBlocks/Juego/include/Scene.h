#ifndef SCENE_H
#define SCENE_H

#include "Structs.h"
#include "Fachada/Camera.h"
#include "Player.h"
#include "World.h"
#include "TriggerSystem.h"
#include "Map.h"

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
        TriggerSystem triggersystem;
        Player *player;
        Map* Mapa;

};

#endif // SCENE_H
