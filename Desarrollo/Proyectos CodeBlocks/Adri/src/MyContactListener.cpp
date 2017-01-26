#include "MyContactListener.h"
#include <iostream>

#define PROTA 8
#define ENEMIGO 5



MyContactListener::MyContactListener()
{
    //ctor
}

MyContactListener::~MyContactListener()
{
    //dtor
}

void MyContactListener::BeginContact(b2Contact* contact) {

    void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

    if((unsigned long)bodyUserDataA == PROTA && (unsigned long)bodyUserDataB == ENEMIGO){
        std::cout << "Se chocan 1. \n";
    }
    else if((unsigned long)bodyUserDataA == ENEMIGO && (unsigned long)bodyUserDataB == PROTA){
        std::cout << "Se chocan 2. \n";
    }

/*
      //check if fixture A was a ball
      void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      if ( bodyUserData )
        static_cast<Ball*>( bodyUserData )->startContact();

      //check if fixture B was a ball
      bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
      if ( bodyUserData )
        static_cast<Ball*>( bodyUserData )->startContact();

    }

    void EndContact(b2Contact* contact) {

      //check if fixture A was a ball
      void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      if ( bodyUserData )
        static_cast<Ball*>( bodyUserData )->endContact();

      //check if fixture B was a ball
      bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
      if ( bodyUserData )
        static_cast<Ball*>( bodyUserData )->endContact();

    }*/
}

void MyContactListener::EndContact(b2Contact* contact){}
