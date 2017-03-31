#ifndef INVESTIGAR_H
#define INVESTIGAR_H

#include "Enemies/StateMachine/State.h"

class Enemy;

class Investigar : public State<Enemy>
{
    public:
        //es SINGLETON
        static Investigar* Instance();
        void Enter(Enemy* enemigo);
        void Execute(Enemy* enemigo);
        void Exit(Enemy* enemigo);
        bool OnMessage(Enemy*, const Mensaje&);

    protected:

    private:
        Investigar(){};
        Investigar(const Investigar&);
        Investigar& operator=(const Investigar&);
};

#endif // INVESTIGAR_H
