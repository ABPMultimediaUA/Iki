#ifndef CURAR_H
#define REVIVIR_H

#include "Enemies/StateMachine/State.h"

class Enemy;

class Revivir : public State<Enemy>
{
    public:
        //es SINGLETON
        static Revivir* Instance();
        void Enter(Enemy* enemigo);
        void Execute(Enemy* enemigo);
        void Exit(Enemy* enemigo);
        bool OnMessage(Enemy*, const Mensaje&);

    protected:

    private:
        Revivir(){};
        Revivir(const Revivir&);
        Revivir& operator=(const Revivir&);
};

#endif // REVIVIR_H
