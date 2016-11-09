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
    std::cin >> input;
    
    switch(input){
        case 0:
            std::cout << "Closing" << std::endl;
            break;
        case 1:
            std::cout << "State changed to : " << input << std::endl;
            break;
        case 2:
            std::cout << "State changed to : " << input << std::endl;
            break;
        case 3:
            std::cout << "State changed to : " << input << std::endl;
            break;
        default:
            std::cout << "Could not change state : " << input << std::endl;
            break;
            
    }
    
    
    return input;
}

//Render
void State::render(){
    
}