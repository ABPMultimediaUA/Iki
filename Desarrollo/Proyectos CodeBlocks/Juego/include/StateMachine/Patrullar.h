#ifndef PATRULLAR
#define PATRULLAR

#include "Enemies/StateMachine/State.h"


class Enemy;
class Mensaje;

class Patrullar : public State<Enemy>
{
public:
    //es SINGLETON
    static Patrullar* Instance();
    void Enter(Enemy* enemigo);
    void Execute(Enemy* enemigo);
    void Exit(Enemy* enemigo);
    bool OnMessage(Enemy*, const Mensaje&);

private:
    Patrullar(){};
    Patrullar(const Patrullar&);
    Patrullar& operator=(const Patrullar&);
};

#endif // PATRULLAR
