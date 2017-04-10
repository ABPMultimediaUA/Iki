#ifndef ESCUCHAR_H
#define ESCUCHAR_H

#include <State.h>

class Enemy;
class Mensaje;

class Escuchar : public State<Enemy>
{
    public:
        static Escuchar* Instance();
        void Enter(Enemy* enemigo);
        void Execute(Enemy* enemigo);
        void Exit(Enemy* enemigo);
        bool OnMessage(Enemy*, const Mensaje&);

    private:
        Escuchar(){};
        Escuchar(const Escuchar&);
        Escuchar& operator=(const Escuchar&);

};

#endif // ESCUCHAR_H
