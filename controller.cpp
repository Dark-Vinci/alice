//
// Created by Ademola Olutomiwa Abraham on 07/11/2024.
//
#include <vector>
#include <string>
#include <sstream>
#include "controller.h"

using namespace std;

pair<string, bool> Controller::App::extract_token(string& str) {
    cout << "extract_token" +str << endl;
    if (str.empty()) {
        cout << "TOKEN" << endl;
        return {"", false};
    }

    stringstream ss(str);
    string token;
    bool is_admin;
    string encrypted_id;

    cout << "GOT HERE" << endl;

    auto sp = Utils::split(str, ',');

    cout << sp[0] << endl;
    cout << sp[1] << endl;

    for (const auto & st : sp) {
        if (st == "true") {
            is_admin = true;
        } else if (st == "false") {
            is_admin = false;
        } else {
            encrypted_id = st;
        }
    }

    cout << "EMCRYPTED" + encrypted_id << endl;

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

//    cout << "wan" + result->to_string() << endl;

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

    cout << token << endl;
    auto token_pair = this->extract_token(token);
    cout << "FIRST -> " + token_pair.first << endl;
    cout << " SECOND->" + token_pair.second << endl;
    if (token_pair.first.empty()) {
        return INVALID_TOKEN;
    }

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
    if (token_pair.first.empty()) {
        return INVALID_TOKEN;
    }

    if (user_id == nullptr) {
        user_id = &token_pair.first;
    }

    auto result = this->user_service.get(*user_id);
    if (result == nullptr) {
        return RECORD_NOT_FOUND;
    }

    result->password = "**********";

    string result_str = result->to_string();

    return result_str;
}

string Controller::App::update_user(string& token, string* user_id, string* username, string* password) {
    if (token.empty()) {
        return TOKEN_NOT_PROVIDED;
    }

    auto token_pair = this->extract_token(token);
    if (token_pair.first.empty()) {
        return INVALID_TOKEN;
    }

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

    string result_str = "UPDATED: " + result->to_string();

    return result_str;
}

string Controller::App::create_password(string& token, string& typ, string* URL, string& username, string& password, string& name, string* developer, string* user_id) {
    if (token.empty()) {
        return TOKEN_NOT_PROVIDED;
    }

    auto token_pair = this->extract_token(token);
    if (token_pair.first.empty()) {
        return INVALID_TOKEN;
    }

    if (user_id == nullptr) {
        user_id = &token_pair.first;
    }

    string result;

    if (typ == "WEB") {
        if (URL == nullptr) {
            return INVALID_INPUT;
        }

        DB::WebPass web;

        web.password = password;
        web.name = name;
        web.user_id = *user_id;
        web.url = *URL;
        web.username = username;

        auto pass = this->password_service.create(web);

        if (pass == nullptr) {
            return UNABLE_TO_PERFORM_OPERATION;
        }

        result = pass->to_string();
    } else if (typ == "DESKTOP") {
        DB::DesktopPass desktop;
        desktop.user_id = *user_id;
        desktop.username = username;
        desktop.password = password;
        desktop.name = name;

        auto pass = this->password_service.create(desktop);

        if (pass == nullptr) {
            return UNABLE_TO_PERFORM_OPERATION;
        }

        result = pass->to_string();
    } else if (typ == "GAME") {
        if (developer == nullptr) {
            return INVALID_INPUT;
        }

        DB::GamePass game;
        game.user_id = *user_id;
        game.username = username;
        game.password = password;
        game.developer = *developer;
        game.name = name;

        auto pass = this->password_service.create(game);

        if (pass == nullptr) {
            return UNABLE_TO_PERFORM_OPERATION;
        }

        result = pass->to_string();
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
    if (token_pair.first.empty()) {
        return INVALID_TOKEN;
    }

    auto result = this->password_service.get(pass_id);
    if (result == nullptr) {
        return RECORD_NOT_FOUND;
    }

//    cout << "RESULT USER ID: " + result->user_id << endl;
//    cout << "RESULT TOKEN: " + token_pair.first << endl;

    if (result->user_id != token_pair.first && !token_pair.second) {
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
    if (token_pair.first.empty()) {
        return INVALID_TOKEN;
    }

//    cout << "TOKEN ID: " + token_pair.first << endl;

    auto result = this->password_service.delete_(pass_id, token_pair.second, token_pair.first);
    if (result == nullptr) {
        return UNABLE_TO_PERFORM_OPERATION;
    }

    string result_str = "DELETED: " + result->to_string();
    delete result;

    return result_str;
}

string Controller::App::update_password(string& token, string& typ, string* user_id, string& id, string* URL, string* username, string* password, string* name, string* developer) {
    if (token.empty()) {
        return TOKEN_NOT_PROVIDED;
    }

    pair<string, bool> token_pair = this->extract_token(token);
    if (token_pair.first.empty()) {
        return INVALID_TOKEN;
    }

    cout << "ABEG OOOOO2" << endl;

    string result_str = INVALID_OPERATION;

    if (typ == "WEB") {
        cout << "ABEG OOOOO" << endl;
        auto old = this->password_service.get_web(id);
        if (old == nullptr) {
            return UNABLE_TO_PERFORM_OPERATION;
        }

        cout << "ABEG OOOOO999" << endl;

        old->updated_at = time(0);

        if (URL != nullptr) {
            old->url = *URL;
        }

        if (username != nullptr) {
            old->username = *username;
        }

        if (password != nullptr) {
            old->password = this->crypto.encode(*password);
        }

        if (name != nullptr) {
            old->name = *name;
        }

        cout << "ABEG OOOOO4" << endl;
        auto result = this->password_service.update(*old, token_pair.second, old->user_id);

        cout << "ABEG OOOOO3" << endl;
        if (result == nullptr) {
            return UNABLE_TO_PERFORM_OPERATION;
        }

        result_str = result->to_string();
    } else if (typ == "DESKTOP") {
        auto old = this->password_service.get_desktop(id);
        if (old == nullptr) {
            return UNABLE_TO_PERFORM_OPERATION;
        }

        old->updated_at = time(0);

        if (username != nullptr) {
            old->username = *username;
        }

        if (password != nullptr) {
            old->password = this->crypto.encode(*password);
        }

        if (name != nullptr) {
            old->name = *name;
        }

        auto result = this->password_service.update(*old, token_pair.second, old->user_id);
        if (result == nullptr) {
            return UNABLE_TO_PERFORM_OPERATION;
        }

        result_str = result->to_string();
    } else if (typ == "GAME") {
        auto old = this->password_service.get_game(id);
        if (old == nullptr) {
            return UNABLE_TO_PERFORM_OPERATION;
        }

        old->updated_at = time(0);

        if (username != nullptr) {
            old->username = *username;
        }

        if (password != nullptr) {
            old->password = this->crypto.encode(*password);;
        }

        if (name != nullptr) {
            old->name = *name;
        }

        if (developer != nullptr) {
            old->developer = *developer;
        }

        auto result = this->password_service.update(*old, token_pair.second, old->user_id);
        if (result == nullptr) {
            return UNABLE_TO_PERFORM_OPERATION;
        }

        result_str = result->to_string();
    }

    return result_str;
}

string Controller::App::get_user_passwords(string& token, string& user_id) {
    if (token.empty()) {
        return TOKEN_NOT_PROVIDED;
    }

    pair<string, bool> token_pair = this->extract_token(token);
    if (token_pair.first.empty()) {
        return INVALID_TOKEN;
    }

    cout << "USER TOKEN" + token_pair.first << endl;

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
    if (token_pair.first.empty()) {
        return INVALID_TOKEN;
    }

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
