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
    void print_options();

private:
    // LIST OF INPUT VALUE
    string TOKEN = "TOKEN: ";
    string PASSWORD = "PASSWORD: ";
    string USERNAME = "USERNAME: ";
    string USER_ID = "USER ID: ";
    string PASSWORD_ID = "PASSWORD ID: ";
    string DEVELOPER = "DEVELOPER: ";
    string URL = "URL: ";
    string NAME = "NAME: ";
    string TYPE = "TYPE: ";
    string TEXT = "TEXT: ";
    string ID = "ID: ";
    string IS_ADMIN = "IS_ADMIN: ";
public:
    Terminal() {
        cout << "---------------------------------------------------INITIALIZING THE TERMINAL APPLICATION---------------------------------------------------" << endl;
    }

    // application loop;
    void start();
};

#endif //PASSWORDMANAGER_UI_H
