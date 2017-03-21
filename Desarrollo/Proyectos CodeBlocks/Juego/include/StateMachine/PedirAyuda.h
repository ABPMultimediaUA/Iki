#ifndef PEDIR_AYUDA
#define PEDIR_AYUDA

#include "StateMachine/State.h"

class Enemy;

class PedirAyuda : public State<Enemy>
{
    public:
        //es SINGLETON
        static PedirAyuda* Instance();
        void Enter(Enemy* enemigo);
        void Execute(Enemy* enemigo);
        void Exit(Enemy* enemigo);
        bool OnMessage(Enemy*, const Mensaje&);

    protected:

    private:
        PedirAyuda(){};
        PedirAyuda(const PedirAyuda&);
        PedirAyuda& operator=(const PedirAyuda&);
};

#endif // PEDIR_AYUDA
