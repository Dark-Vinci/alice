//
// Created by Ademola Olutomiwa Abraham on 07/11/2024.
//
#include <vector>
#include <string>
#include "controller.h"

using namespace std;

string Controller::App::create_user_account(string* token, string& username, string& password, bool is_admin) {
    DB::UserEntity user = DB::UserEntity(username, password, is_admin);

    DB::UserEntity* result = this->user_service.create(user);
    if (result == nullptr) {
        return UNABLE_TO_PERFORM_OPERATION;
    }

    if (token == nullptr) {
        return USER_CREATED + result->to_string();
    }

    return ADMIN_CREATED + result->to_string();
}

string Controller::App::login(string& username, string& password) {
    if (username.empty() || password.empty()) {
        return INVALID_INPUT;
    }

    string token = this->user_service.login(username, password);
    if (token.empty()) {
        return UNABLE_TO_PERFORM_OPERATION;
    }

    return LOGIN_TOKEN + token;
}

string Controller::App::delete_user(string &token, string*  user_id) {
    if (token.empty()) {
        return TOKEN_NOT_PROVIDED;
    }

    auto token_pair = this->extract_token(token);
    if (user_id == nullptr) {
        user_id = &token_pair.first;
    }

    auto result = this->user_service.delete_(*user_id, token_pair.second);
    if (result == nullptr) {
        return UNABLE_TO_PERFORM_OPERATION;
    }

    return result->to_string();
}

string Controller::App::get_user(string& token, string* user_id) {
    if (token.empty()) {
        return TOKEN_NOT_PROVIDED;
    }

    auto token_pair = this->extract_token(token);
    if (user_id == nullptr) {
        user_id = &token_pair.first;
    }

    auto result = this->user_service.get(*user_id);
    if (result == nullptr) {
        return RECORD_NOT_FOUND;
    }

    return result->to_string();
}

string Controller::App::update_user(string& token, string* user_id, string* username, string* password) {
    if (token.empty()) {
        return TOKEN_NOT_PROVIDED;
    }

    auto token_pair = this->extract_token(token);
    if (user_id == nullptr) {
        user_id = &token_pair.first;
    }

    auto user = this->user_service.get(*user_id);
    if (user == nullptr) {
        return RECORD_NOT_FOUND;
    }

    if (password != nullptr) {
        user->password = *password;
    }

    if (username != nullptr) {
        user->username = *username;
    }

    auto result = this->user_service.update(*user, token_pair.second, *user_id, password != nullptr);

    return "UPDATED" + result->to_string();
}

string Controller::App::create_password(string& token, string& typ, string* URL, string& username, string& password, string& name, string* developer) {
    if (token.empty()) {
        return TOKEN_NOT_PROVIDED;
    }

    auto token_pair = this->extract_token(token);

    if (typ == "WEB") {

    }

    return "USER PASSWORD";
}

string Controller::App::get_password(string& token, string& pass_id) {
    if (token.empty()) {
        return TOKEN_NOT_PROVIDED;
    }

    auto token_pair = this->extract_token(token);

    auto result = this->password_service.get(pass_id);
    if (result == nullptr) {
        return RECORD_NOT_FOUND;
    }

    if (result->id != token_pair.first && !token_pair.second) {
        return NOT_AUTHORIZED;
    }

    return result->to_string();
}

string Controller::App::delete_password(string& token, string& pass_id) {
    if (token.empty()) {
        return TOKEN_NOT_PROVIDED;
    }

    pair<string, bool> token_pair = this->extract_token(token);

    auto result = this->password_service.delete_(pass_id, token_pair.second, token_pair.first);
    if (result == nullptr) {
        return UNABLE_TO_PERFORM_OPERATION;
    }

    return "DELETED" + result->to_string();
}

string Controller::App::update_password(string& token, string& typ, string* user_id, string& id, string* URL, string* username, string* password, string* name, string* developer) {
    if (token.empty()) {
        return TOKEN_NOT_PROVIDED;
    }

    pair<string, bool> token_pair = this->extract_token(token);

    if (typ == "WEB") {
        DB::WebPass pass;

        pass.id = id;
        //todo:  created at should be looked into
        pass.updated_at = time(0);

        if (user_id != nullptr) {
            pass.user_id = *user_id;
        } else {
            pass.user_id = token_pair.first;
        }

        if (URL != nullptr) {
            pass.url = *URL;
        }

        if (username != nullptr) {
            pass.username = *username;
        }

        if (password != nullptr) {
            pass.password = *password;
        }

        if (name != nullptr) {
            pass.name = *name;
        }

        auto result = this->password_service.update(pass, token_pair.second, pass.user_id);

        if (result == nullptr) {
            return UNABLE_TO_PERFORM_OPERATION;
        }

        return result->to_string();
    } else if (typ == "DESKTOP") {
        DB::DesktopPass pass;

        pass.id = id;
        pass.updated_at = time(0);

        if (user_id != nullptr) {
            pass.user_id = *user_id;
        } else {
            pass.user_id = token_pair.first;
        }

        if (username != nullptr) {
            pass.username = *username;
        }

        if (password != nullptr) {
            pass.password = *password;
        }

        if (name != nullptr) {
            pass.name = *name;
        }

        auto result = this->password_service.update(pass, token_pair.second, pass.user_id);

        if (result == nullptr) {
            return UNABLE_TO_PERFORM_OPERATION;
        }

        return result->to_string();
    } else if (typ == "GAME") {
        DB::GamePass pass;

        pass.id = id;
        pass.updated_at = time(0);

        if (user_id != nullptr) {
            pass.user_id = *user_id;
        } else {
            pass.user_id = token_pair.first;
        }

        if (username != nullptr) {
            pass.username = *username;
        }

        if (password != nullptr) {
            pass.password = *password;
        }

        if (name != nullptr) {
            pass.name = *name;
        }

        auto result = this->password_service.update(pass, token_pair.second, pass.user_id);

        if (result == nullptr) {
            return UNABLE_TO_PERFORM_OPERATION;
        }

        return result->to_string();
    } else {
        return INVALID_OPERATION;
    }
}

string Controller::App::get_user_passwords(string& token, string& user_id) {
    if (token.empty()) {
        return TOKEN_NOT_PROVIDED;
    }

    pair<string, bool> token_pair = this->extract_token(token);

    vector<DB::Pass*> passwords = this->password_service.get_all_user(token_pair.first);
    if (passwords.empty()) {
        return NO_PASSWORD_FOR_USER;
    }

    string result;

    for (const DB::Pass* pass: passwords) {
        result += pass->to_string() + "\n";
    }

    return result;
}

string Controller::App::search_password(string& token, string& text){
    if (token.empty()) {
        return TOKEN_NOT_PROVIDED;
    }

    pair<string, bool> token_pair = this->extract_token(token);

    vector<DB::Pass*> passwords = this->password_service.get_all_user(token_pair.first);
    if (passwords.empty()) {
        return NO_PASSWORD_FOR_USER;
    }

    string result;

    for (const DB::Pass* pass: passwords) {
        string str = pass->to_string();

        if (str.find(text) != std::string::npos) {
            result += pass->to_string() + "\n";
        }
    }

    return result;
}
