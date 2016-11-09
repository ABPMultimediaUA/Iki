/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.cpp
 * Author: Juan
 * 
 * Created on 9 de noviembre de 2016, 18:42
 */

#include "Game.h"
#include "State.h"

Game::Game() {
    state = State::Instance();
    
}

Game::Game(const Game& orig) {
}

Game::~Game() {
}

/*
 *
 */

//Update
int Game::update(){
    return state->update();
    
}

//Render
void Game::render(){
    state->render();
    
}

