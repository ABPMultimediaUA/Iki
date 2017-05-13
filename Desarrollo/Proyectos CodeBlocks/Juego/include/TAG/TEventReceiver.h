#ifndef TEVENTRECEIVER_H
#define TEVENTRECEIVER_H

#include <SFML/Window.hpp>

class TEventReceiver
{
    public:
        TEventReceiver();
        virtual ~TEventReceiver();

        sf::Event getEvent(){return m_event;};
        sf::Event getEvent(){};

    protected:

    private:
        sf::Event m_event;
        m_event.
};

#endif // TEVENTRECEIVER_H
