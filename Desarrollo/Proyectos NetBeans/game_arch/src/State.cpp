/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State.cpp
 * Author: Juan
 * 
 * Created on 9 de noviembre de 2016, 19:16
 */

#include "State.h"
State* State::pinstance = 0;

State::State() {
    istate = 1;
    
    menu = new Menu();
}

State::State(const State& orig) {
}

State::~State() {
}

/*
 *
 */

//Singleton
State* State::Instance(){
    if (pinstance == 0){
        pinstance = new State();
    }
    return pinstance;
}

//Update
int State::update(){
        
    switch(istate){
        case 0:
            cout << "Closing" << endl;
            return 0;
        case 1:
            istate = menu->update();
            break;
        case 2:
            //istate = ingame->update();
            break;
        case 3:
            //istate = cinematic->update();
            break;
        default:
            cout << "Could not change state : " << istate << endl;
            break;
    }
    
    return istate;
}

//Render
void State::render(){
    
    switch(istate){
        /*case 0:
            std::cout << "Closing" << std::endl;
            return 0;*/
        case 1:
            //menu->render();
            break;
        case 2:
            //ingame->render();
            break;
        case 3:
            //cinematic->render();
            break;
        default:
            //
            break;
    }  
}