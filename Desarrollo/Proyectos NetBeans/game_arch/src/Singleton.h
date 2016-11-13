/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Singleton.h
 * Author: Juan
 *
 * Created on 9 de noviembre de 2016, 19:27
 */

#ifndef SINGLETON_H
#define SINGLETON_H

class Singleton {
public:
    //Singleton
    static Singleton* Instance();
    
    Singleton();
    Singleton(const Singleton& orig);
    virtual ~Singleton();
private:
    static Singleton* pinstance;
};

#endif /* SINGLETON_H */

