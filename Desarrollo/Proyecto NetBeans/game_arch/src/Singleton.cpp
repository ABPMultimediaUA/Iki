/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Singleton.cpp
 * Author: Juan
 * 
 * Created on 9 de noviembre de 2016, 19:27
 */

#include "Singleton.h"

Singleton* Singleton::pinstance = 0;

Singleton* Singleton::Instance()
{
    if (pinstance == 0)
    {
        pinstance = new Singleton;
    }
    return pinstance;
}

/*
 *
 */

Singleton::Singleton() {
}

Singleton::Singleton(const Singleton& orig) {
}

Singleton::~Singleton() {
}

