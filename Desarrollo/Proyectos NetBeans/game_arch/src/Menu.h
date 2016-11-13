/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Menu.h
 * Author: Juan
 *
 * Created on 9 de noviembre de 2016, 21:15
 */

#ifndef MENU_H
#define MENU_H

#include <cstdlib>
#include <iostream>
using namespace std;

class Menu {
public:
    Menu();
    Menu(const Menu& orig);
    virtual ~Menu();
    
    //Update & Render
    int update();
    void render();
    
private:
    //Local variables
    int posX, posY;

};

#endif /* MENU_H */

