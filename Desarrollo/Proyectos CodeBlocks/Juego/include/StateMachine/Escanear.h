#ifndef ESCANEAR_H
#define ESCANEAR_H

#include "StateMachine/State.h"

class Enemy;

class Escanear : public State<Enemy>
{
    public:
        //es SINGLETON
        static Escanear* Instance();
        void Enter(Enemy* enemigo);
        void Execute(Enemy* enemigo);
        void Exit(Enemy* enemigo);
        bool OnMessage(Enemy*, const Mensaje&);

    protected:

    private:
        Escanear(){};
        Escanear(const Escanear&);
        Escanear& operator=(const Escanear&);
};

#endif // ESCANEAR_H
