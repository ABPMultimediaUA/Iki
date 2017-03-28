#ifndef STATEMACHINE
#define STATEMACHINE

#include <irrlicht.h>
#include "Enemies/StateMachine/State.h"
class Enemy;

template <class entity_type>

class StateMachine
{
    private:
        //a pointer to the agent that owns this instance
        entity_type* propietario;
        State<entity_type>* actualState;
        //a record of the last state the agent was in
        State<entity_type>* previoState;
        //this state logic is called every time the FSM is updated
        State<entity_type>* globalState;

    public:
        StateMachine(entity_type* owner):propietario(owner),
        actualState(NULL),
        previoState(NULL),
        globalState(NULL)
        {}
        //use these methods to initialize the FSM
        void SetCurrentState(State<entity_type>* s){actualState = s;}
        void SetGlobalState(State<entity_type>* s) {globalState = s;}
        void SetPreviousState(State<entity_type>* s){previoState = s;}
        //call this to update the FSM
        void Update()const
        {
            //if a global state exists, call its execute method
            if (globalState) globalState->Execute(propietario);
            //same for the current state
            if (actualState) actualState->Execute(propietario);
        }
        //change to a new state
        void ChangeState(State<entity_type>* pNewState){
            assert(pNewState && "<StateMachine::ChangeState>: trying to change to a null state");
            //keep a record of the previous state
            previoState = actualState;
            //call the exit method of the existing state
            actualState->Exit(propietario);
            //change state to the new state
            actualState = pNewState;
            //call the entry method of the new state
            actualState->Enter(propietario);
        }
        //change state back to the previous state
        void RevertToPreviousState()
        {
        ChangeState(previoState);
        }
        //accessors
        State<entity_type>* CurrentState() const{return actualState;}
        State<entity_type>* GlobalState() const{return globalState;}
        State<entity_type>* PreviousState() const{return previoState;}
        //returns true if the current state’s type is equal to the type of the class passed as a parameter.
        bool isInState(const State<entity_type>& st)const{
            if (typeid(*actualState) == typeid(st))
                return true;
            return false;
        }
        bool  HandleMessage(const Mensaje& msg)const
        {
            //first see if the current state is valid and that it can handle
            //the message
            if (actualState && actualState->OnMessage(propietario, msg))
            {
                return true;
            }

            //if not, and if a global state has been implemented, send
            //the message to the global state
            if (globalState && globalState->OnMessage(propietario, msg))
            {
                return true;
            }

            return false;
        }

    protected:




};

#endif // STATEMACHINE
