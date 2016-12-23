#ifndef SCENE_H
#define SCENE_H

#include "Player.h"
#include "World.h"

class Scene
{
    public:
        Scene();
        virtual ~Scene();
        void inicializar_escena(IrrlichtDevice*);
        void update_escena();
        void render();
        ICameraSceneNode *camera;

    protected:

    private:

        ISceneManager *smgr;
        World *world;
        Player *player;
};

#endif // SCENE_H
