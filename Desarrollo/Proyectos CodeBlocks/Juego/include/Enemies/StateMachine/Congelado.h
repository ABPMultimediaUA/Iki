#ifndef CONGELADO_H
#define CONGELADO_H

#include "Enemies/StateMachine/State.h"


class Enemy;
class Mensaje;

class Congelado : public State<Enemy>
{
public:
    //es SINGLETON
    static Congelado* Instance();
    void Enter(Enemy* enemigo);
    void Execute(Enemy* enemigo);
    void Exit(Enemy* enemigo);
    bool OnMessage(Enemy*, const Mensaje&){};

private:
    Congelado(){};
    Congelado(const Congelado&);
    Congelado& operator=(const Congelado&);
};

#endif // CONGELADO_H
