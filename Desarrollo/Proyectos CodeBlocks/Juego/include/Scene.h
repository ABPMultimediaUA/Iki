#ifndef SCENE_H
#define SCENE_H

#include "Structs.h"
#include "TriggerSystem.h"

class Camera;
class Player;
class World;
class Map;
class Menu;

class Scene
{
    public:
        Scene();
        ~Scene();
        void inicializar_escena();
        void bucle_juego();

    protected:

    private:

        Camera *camara;
        World *world;
        TriggerSystem triggersystem;
        Player *player;
        Menu* menu_ingame;
        Map* Mapa;

};

#endif // SCENE_H
