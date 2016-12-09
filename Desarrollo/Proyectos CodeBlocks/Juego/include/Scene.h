#ifndef SCENE_H
#define SCENE_H

#include "GameEntity.h"
#include "World.h"

class Scene
{
    public:
        Scene();
        virtual ~Scene();
        void inicializar_escena();
        void update_escena();

    protected:

    private:

        World *world;
        GameEntity *entity_man;
};

#endif // SCENE_H
