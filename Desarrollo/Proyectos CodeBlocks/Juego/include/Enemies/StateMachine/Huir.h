#ifndef HUIR
#define HUIR

#include "Enemies/StateMachine/State.h"

class Enemy;

class Huir : public State<Enemy>
{
    public:
        //es SINGLETON
        static Huir* Instance();
        void Enter(Enemy* enemigo);
        void Execute(Enemy* enemigo);
        void Exit(Enemy* enemigo);
        bool OnMessage(Enemy*, const Mensaje&);

    protected:

    private:
        Huir(){};
        Huir(const Huir&);
        Huir& operator=(const Huir&);
};

#endif // HUIR
