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

        string create_password(string& token, string* URL, string& username, string& password, string& name, string* developer);
        string update_password(string& token, string* URL, string* username, string* password, string* name, string* developer);
        string delete_password(string& token, string& pass_id);
        string get_user_passwords(string& token, string& user_id);
        string get_password(string& token, string& pass_id);
        string search_password(string& token, string& text);
    };
}

#endif //PASSWORDMANAGER_CONTROLLER_H
