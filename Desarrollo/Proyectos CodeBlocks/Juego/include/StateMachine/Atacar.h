#ifndef ATACAR_H
#define ATACAR_H

#include "StateMachine/State.h"

class Enemy;

class Atacar : public State<Enemy>
{
    public:
        //es SINGLETON
        static Atacar* Instance();
        void Enter(Enemy* enemigo);
        void Execute(Enemy* enemigo);
        void Exit(Enemy* enemigo);
        bool OnMessage(Enemy*, const Mensaje&);

    protected:

    private:
        Atacar(){};
        Atacar(const Atacar&);
        Atacar& operator=(const Atacar&);
};

#endif // ATACAR_H
