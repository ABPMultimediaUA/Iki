#ifndef STATEMACHINE
#define STATEMACHINE

#include <irrlicht.h>
#include "Enemies/StateMachine/State.h"
class Enemy;

template <class entity_type>

class StateMachine
{
    private:
        entity_type* propietario;
        State<entity_type>* actualState;
        State<entity_type>* previoState;
        //this state logic is called every time the FSM is updated
        State<entity_type>* globalState;

    public:
        StateMachine(entity_type* owner):propietario(owner),
        actualState(NULL),
        previoState(NULL),
        globalState(NULL)
        {}
        void SetCurrentState(State<entity_type>* s){actualState = s;}
        void SetGlobalState(State<entity_type>* s) {globalState = s;}
        void SetPreviousState(State<entity_type>* s){previoState = s;}
        //call this to update the FSM
        void Update()const
        {
            if (globalState) globalState->Execute(propietario);
            if (actualState) actualState->Execute(propietario);
        }
        void ChangeState(State<entity_type>* pNewState){
            assert(pNewState && "<StateMachine::ChangeState>: trying to change to a null state");
            previoState = actualState;
            actualState->Exit(propietario);
            actualState = pNewState;
            actualState->Enter(propietario);
        }
        void RevertToPreviousState()
        {
        ChangeState(previoState);
        }
        State<entity_type>* CurrentState() const{return actualState;}
        State<entity_type>* GlobalState() const{return globalState;}
        State<entity_type>* PreviousState() const{return previoState;}
        bool wasInState(const State<entity_type>& st)const{
            if (typeid(*previoState) == typeid(st))
                return true;
            return false;
        }
        bool isInState(const State<entity_type>& st)const{
            if (typeid(*actualState) == typeid(st))
                return true;
            return false;
        }
        bool  HandleMessage(const Mensaje& msg)const
        {

            if (actualState && actualState->OnMessage(propietario, msg))
            {
                return true;
            }

            if (globalState && globalState->OnMessage(propietario, msg))
            {
                return true;
            }

            return false;
        }

    protected:




};

#endif // STATEMACHINE
