#ifndef PATRULLAR
#define PATRULLAR

#include "StateMachine/State.h"

class Guardia;

//template <class entity_type>
class Patrullar : public State<Guardia>
{
public:
    //this is a singleton
    static Patrullar* Instance();
    void Enter(Guardia* guardia);
    void Execute(Guardia* guardia);
    void Exit(Guardia* guardia);
    bool OnMessage(Guardia*, const Telegram&);

private:
    Patrullar(){};
    //copy ctor and assignment should be private
    Patrullar(const Patrullar&);
    Patrullar& operator=(const Patrullar&);


};

#endif // PATRULLAR
