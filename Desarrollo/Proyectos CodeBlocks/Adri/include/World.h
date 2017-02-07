#ifndef WORLD_H
#define WORLD_H
#include <Box2D/Box2D.h>
#include <iostream>
#include <MyContactListener.h>

class World
{
    static World* pinstance;

    public:
        static World* Instance();
        void Step(float DeltaTime);
        void Update();
        void Render();
        virtual ~World();
        b2World* getWorld();

    protected:
        World();

    private:
        b2World* world;
        b2Vec2 gravity;
        MyContactListener* contactListener;
};

#endif // WORLD_H