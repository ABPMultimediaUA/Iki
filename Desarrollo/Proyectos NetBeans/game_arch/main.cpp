/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Juan
 *
 * Created on 9 de noviembre de 2016, 17:44
 */

#include <cstdlib>
#include <iostream>
#include "src/Game.h"

using namespace std;

int main() {

    cout << "TEST" << endl;
    
    Game* game = new Game;
    int quit = 1;
    
    while(quit){
        
        quit = game->update();
        game->render();

    }

    return 0;
}

