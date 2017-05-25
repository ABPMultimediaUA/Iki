#ifndef SCENE_H
#define SCENE_H

#include "Structs.h"

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
        void cargarSonidos();
        void inicializar_escena(int);
        void bucle_juego(int);
        void cleanScene(int);
        bool wantsNextLevel(){ return nextLevel; }

    protected:

    private:
        Camera *camara;
        World *world;
        Player *player;
        Menu* menu_ingame;
        Map* Mapa;
        bool isGameActive, reintentar, nextLevel;

};

#endif // SCENE_H
