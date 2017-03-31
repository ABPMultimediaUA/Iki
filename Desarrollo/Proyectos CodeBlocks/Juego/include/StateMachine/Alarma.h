#ifndef ALARMA_H
#define ALARMA_H

#include "StateMachine/State.h"

class Enemy;

class Alarma : public State<Enemy>
{
    public:
        //es SINGLETON
        static Alarma* Instance();
        void Enter(Enemy* enemigo);
        void Execute(Enemy* enemigo);
        void Exit(Enemy* enemigo);
        bool OnMessage(Enemy*, const Mensaje&);

    protected:

    private:
        Alarma(){};
        Alarma(const Alarma&);
        Alarma& operator=(const Alarma&);
};

#endif // ALARMA_H
