//
// Created by Ademola Olutomiwa Abraham on 07/11/2024.
//
#include <iostream>
#include "controller.h"

using namespace std;

#ifndef PASSWORDMANAGER_UI_H
#define PASSWORDMANAGER_UI_H

class Terminal{
private:
    Controller::App application;
public:
    Terminal() {
        cout << "--------INITIALIZING THE TERMINAL APPLICATION--------" << endl;
//        this->application = app;
    }

    void start();
};

#endif //PASSWORDMANAGER_UI_H
