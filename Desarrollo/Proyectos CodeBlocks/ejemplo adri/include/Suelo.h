#ifndef SUELO_H
#define SUELO_H
#include <Box2D/Box2D.h>

class Suelo
{
    public:
        Suelo();
        virtual ~Suelo();

    protected:

    private:
        b2Body *body;
        class World* iworld;
};

#endif // SUELO_H
