#ifndef VIGILAR_H
#define VIGILAR_H

#include "Enemies/StateMachine/State.h"

class Enemy;

class Vigilar : public State<Enemy>
{
    public:
            //this is a singleton
        static Vigilar* Instance();
        void Enter(Enemy* enemigo);
        void Execute(Enemy* enemigo);
        void Exit(Enemy* enemigo);
        bool OnMessage(Enemy*, const Mensaje&);

    protected:

    private:
        Vigilar(){};
        //copy ctor and assignment should be private
        Vigilar(const Vigilar&);
        Vigilar& operator=(const Vigilar&);
};

#endif // VIGILAR_H
