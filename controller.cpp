//
// Created by Ademola Olutomiwa Abraham on 07/11/2024.
//
#include <vector>
#include <string>
#include <sstream>
#include "controller.h"

using namespace std;

pair<string, bool> Controller::App::extract_token(string& str) {
    if (str.empty()) {
        return {"", false};
    }

    stringstream ss(str);
    string token;
    bool is_admin;
    string encrypted_id;

    while (getline(ss, token, ',')) {
        if (token == "true") {
            is_admin = true;
        } else if (token == "false") {
            is_admin = false;
        } else {
            token = encrypted_id;
        }
    }

    encrypted_id = this->crypto.decode(encrypted_id);

    return {encrypted_id, is_admin};
}

string Controller::App::create_user_account(string* token, string& username, string& password, bool is_admin) {
    DB::UserEntity user = DB::UserEntity(username, password, is_admin);

    DB::UserEntity* result = this->user_service.create(user);
    if (result == nullptr) {
        return UNABLE_TO_PERFORM_OPERATION;
    }

    string ret;

    if (token == nullptr) {
        ret =  USER_CREATED + result->to_string();
    } else {
        ret = ADMIN_CREATED + result->to_string();
    }

    delete result;

    return ret;
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

    string return_str = result->to_string();

    delete result;

    return return_str;
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

    string result_str = result->to_string();
    delete result;

    return result_str;
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
    if (result == nullptr) {
        return UNABLE_TO_PERFORM_OPERATION;
    }

    string result_str = "UPDATED" + result->to_string();
    delete result;

    return result_str;
}

string Controller::App::create_password(string& token, string& typ, string* URL, string& username, string& password, string& name, string* developer, string* user_id) {
    if (token.empty()) {
        return TOKEN_NOT_PROVIDED;
    }

    auto token_pair = this->extract_token(token);

    if (user_id == nullptr) {
        user_id = &token_pair.first;
    }

    string result;

    if (typ == "WEB") {
        if (URL == nullptr) {
            return INVALID_INPUT;
        }

        DB::WebPass web(username, password, name, user_id, *URL);

        auto pass = this->password_service.create(web);
        result = pass.to_string();
        delete pass;
    } else if (typ == "DESKTOP") {
        DB::DesktopPass desktop(username, password, name, user_id);

        auto pass = this->password_service.create(desktop);
        result = pass.to_string();
        delete pass;
    } else if (typ == "GAME") {
        if (developer == nullptr) {
            return INVALID_INPUT;
        }

        DB::GamePass game(username, password, name, user_id, *developer);
        auto pass = this->password_service.create(game);
        result = pass.to_string();
        delete pass;
    } else {
        result = INVALID_OPERATION;
    }

    return result;
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

    string result_str = result->to_string();
    delete result;

    return result_str;
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

    string result_str = "DELETED" + result->to_string();
    delete result;

    return result_str;
}

string Controller::App::update_password(string& token, string& typ, string* user_id, string& id, string* URL, string* username, string* password, string* name, string* developer) {
    if (token.empty()) {
        return TOKEN_NOT_PROVIDED;
    }

    pair<string, bool> token_pair = this->extract_token(token);

    string result_str = INVALID_OPERATION;

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

        result_str = result->to_string();

        delete result;
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

        result_str = result->to_string();

        delete result;
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

        result_str = result->to_string();

        delete result;
    }

    return result_str;
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
        delete pass;
    }

    passwords.clear();

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

        if (str.find(text) != string::npos) {
            result += pass->to_string() + "\n";
        }

        delete pass;
    }

    passwords.clear();

    return result;
}
