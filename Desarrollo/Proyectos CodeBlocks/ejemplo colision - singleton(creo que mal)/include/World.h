#ifndef WORLD_H
#define WORLD_H
#include "Singleton.h"
#include <Box2D/Box2D.h>

class World
{
    public:
        static World* Instance();
        void Update();
        void Render();
        World();
        virtual ~World();

    protected:

    private:
};

#endif // WORLD_H
