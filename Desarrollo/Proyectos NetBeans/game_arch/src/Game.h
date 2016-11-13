/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.h
 * Author: Juan
 *
 * Created on 9 de noviembre de 2016, 18:42
 */

#ifndef GAME_H
#define GAME_H

class Game {
public:
    Game();
    Game(const Game& orig);
    virtual ~Game();

    //Update & Render
    int update();
    void render();
    
private:
    class State* state;

};

#endif /* GAME_H */

