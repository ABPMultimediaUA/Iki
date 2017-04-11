#ifndef STATE
#define STATE
#include "Structs.h"
#include "SoundManager.h"

struct Mensaje;

template <class entity_type>
class State
{
    public:
        virtual void Enter(entity_type*)=0;
        virtual void Execute(entity_type*)=0;
        virtual void Exit(entity_type*)=0;
        virtual ~State(){};
        //this executes if the agent receives a message from the
        //message dispatcher
        virtual bool OnMessage(entity_type*, const Mensaje&)=0;


    protected:
        enum message_type
        {
            Msg_NeedHelp,
            Msg_NeedPosition
        };

    private:
};

#endif // STATE
