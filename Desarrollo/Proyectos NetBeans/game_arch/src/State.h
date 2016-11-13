/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State.h
 * Author: Juan
 *
 * Created on 9 de noviembre de 2016, 19:16
 */

#ifndef STATE_H
#define STATE_H

#include <cstdlib>
#include <iostream>
using namespace std;

#include "Singleton.h"
#include "Menu.h"

class State {
public:
    State();
    State(const State& orig);
    virtual ~State();

    //Singleton
    static State* Instance();
    
    //Update & Render
    int update();
    void render();
    
private:
    //Singleton
    static State* pinstance;
    
    //Local variables
    int istate;
    Menu* menu;

};

#endif /* STATE_H */

