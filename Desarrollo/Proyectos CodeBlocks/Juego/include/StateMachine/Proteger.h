#ifndef PROTEGER
#define PROTEGER

#include "StateMachine/State.h"

class Enemy;

class Proteger : public State<Enemy>
{
    public:
        //es SINGLETON
        static Proteger* Instance();
        void Enter(Enemy* enemigo);
        void Execute(Enemy* enemigo);
        void Exit(Enemy* enemigo);
        bool OnMessage(Enemy*, const Mensaje&);

    protected:

    private:
        Proteger(){};
        Proteger(const Proteger&);
        Proteger& operator=(const Proteger&);
};

#endif // PROTEGER
