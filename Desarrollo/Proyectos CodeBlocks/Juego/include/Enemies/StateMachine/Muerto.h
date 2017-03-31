#ifndef MUERTO_H
#define MUERTO_H

#include "Enemies/StateMachine/State.h"

class Enemy;

class Muerto : public State<Enemy>
{
    public:
        //es SINGLETON
        static Muerto* Instance();
        void Enter(Enemy* enemigo);
        void Execute(Enemy* enemigo);
        void Exit(Enemy* enemigo);
        bool OnMessage(Enemy*, const Mensaje&);

    protected:

    private:
        Muerto(){};
        Muerto(const Muerto&);
        Muerto& operator=(const Muerto&);
};

#endif // MUERTO_H
