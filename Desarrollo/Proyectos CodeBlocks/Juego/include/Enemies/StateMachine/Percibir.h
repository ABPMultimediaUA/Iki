#ifndef PERCIBIR_H
#define PERCIBIR_H

#include "Enemies/StateMachine/State.h"


class Enemy;
class GameEntity;
class Mensaje;

class Percibir : public State<Enemy>
{
public:
    //es SINGLETON
    static Percibir* Instance();
    void Enter(Enemy* enemigo);
    void Execute(Enemy* enemigo);
    void Exit(Enemy* enemigo);
    bool OnMessage(Enemy*, const Mensaje&){};

private:
    Percibir(){};
    Percibir(const Percibir&);
    Percibir& operator=(const Percibir&);
    std::vector<GameEntity*> entities;
    bool enter;
};

#endif // PERCIBIR_H
