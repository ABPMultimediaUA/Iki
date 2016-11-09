/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Menu.cpp
 * Author: Juan
 * 
 * Created on 9 de noviembre de 2016, 21:15
 */

#include "Menu.h"

Menu::Menu() {
}

Menu::Menu(const Menu& orig) {
}

Menu::~Menu() {
}

/*
 *
 */

//Update
int Menu::update(){
    
    for (int i=1; i <= 4; i++){
        if (i == posX) cout << "-> " ;
        cout << "Line " << i << endl;
    }    
    cin >> posX;
    cout << endl;
    
    switch (posX){
        case 0:
            return 0;
        default:
            return 1;
    }
}

//Render
void Menu::render(){
   cout << endl;
}
