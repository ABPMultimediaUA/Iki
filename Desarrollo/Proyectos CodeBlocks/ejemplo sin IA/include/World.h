#ifndef WORLD_H
#define WORLD_H
#include <Box2D/Box2D.h>
#include <iostream>

class World
{
    static World* pinstance;

    public:
        static World* Instance();
        void Step(float DeltaTime);
        void Update();
        void Render();
        void destruye(b2Body *b);
        virtual ~World();
        b2World* getWorld();

    protected:
        World();

    private:
        b2World* world;
        b2Vec2 gravity;
};

#endif // WORLD_H
