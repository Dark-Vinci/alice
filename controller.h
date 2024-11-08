//
// Created by Ademola Olutomiwa Abraham on 07/11/2024.
//

#ifndef PASSWORDMANAGER_CONTROLLER_H
#define PASSWORDMANAGER_CONTROLLER_H

#include "service.h"

namespace Controller {
    class App {
    private:
        Service::User user_service;
        Service::Password password_service;

    public:
        string create_user_account();
        string get_user();
        string delete_user();
        string update_user();
        string login();

        string create_password();
        string update_password();
        string delete_password();
        string get_user_passwords();
        string get_password();
    };
}

#endif //PASSWORDMANAGER_CONTROLLER_H
