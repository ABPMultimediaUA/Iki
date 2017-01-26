#ifndef MYCONTACTLISTENER_H
#define MYCONTACTLISTENER_H
#include <Box2D/Box2D.h>


class MyContactListener: public b2ContactListener
{
    public:
        MyContactListener();
        virtual ~MyContactListener();
        virtual void BeginContact(b2Contact* contact);
        virtual void EndContact(b2Contact* contact);
        b2Fixture* GetFixtureA();
        b2Fixture* GetFixtureB();

    protected:

    private:
        b2Fixture* fixtureA;
        b2Fixture* fixtureB;
        b2Body* body1;
        b2Body* body2;
        bool m_contacting;
};

#endif // MYCONTACTLISTENER_H
