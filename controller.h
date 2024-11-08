//
// Created by Ademola Olutomiwa Abraham on 07/11/2024.
//

#ifndef PASSWORDMANAGER_CONTROLLER_H
#define PASSWORDMANAGER_CONTROLLER_H

#include "service.h"

namespace Controller {
    class App {
    private:
        string NOT_AUTHORIZED = "NOT AUTHORIZED";
        string RECORD_NOT_FOUND = "RECORD NOT FOUND";
        string TOKEN_NOT_PROVIDED = "NO TOKEN PROVIDED";
        string UNABLE_TO_PERFORM_OPERATION = "UNABLE_TO_PERFORM_OPERATION";
        string NO_PASSWORD_FOR_USER = "NO PASSWORD FOR USER";
        string INVALID_OPERATION = "INVALID OPERATION";
        Service::User user_service;
        Service::Password password_service;
        pair<string, bool> extract_token(string& str);

    public:
        string create_user_account();
        string get_user(string& token, string* user_id);
        string delete_user(string& token, string* user_id);
        string update_user();
        string login();

        string create_password(string& token, string* URL, string& username, string& password, string& name, string* developer);
        string update_password(string& token, string& typ, string* user_id, string& id, string* URL, string* username, string* password, string* name, string* developer);
        string delete_password(string& token, string& pass_id);
        string get_user_passwords(string& token, string& user_id);
        string get_password(string& token, string& pass_id);
        string search_password(string& token, string& text);
    };
}

#endif //PASSWORDMANAGER_CONTROLLER_H
