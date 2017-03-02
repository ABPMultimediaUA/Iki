#ifndef STATE
#define STATE
struct Telegram;

template <class entity_type>
class State
{
    public:
        virtual void Enter(entity_type*)=0;
        virtual void Execute(entity_type*)=0;
        virtual void Exit(entity_type*)=0;
        virtual ~State(){}
        //this executes if the agent receives a message from the
        //message dispatcher
        virtual bool OnMessage(entity_type*, const Telegram&)=0;


    protected:

    private:
};

#endif // STATE
