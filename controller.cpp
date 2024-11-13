//
// Created by Ademola Olutomiwa Abraham on 07/11/2024.
//
#include <vector>
#include <string>
#include <sstream>

#include "controller.h"

using namespace std;

//Controller::App::extract_token: extracts the token and return the is_admin and the user_id fields as pair
pair<string, bool> Controller::App::extract_token(string& str) {
    // token validation
    if (str.empty()) {
        return {"", false};
    }

    stringstream ss(str);
    string token;
    bool is_admin;
    string encrypted_id;

    // split the token by ',' since the format is [false, gsjkwchbnwediwek]
    auto sp = Utils::split(str, ',');

    for (const auto & st : sp) {
        if (st == "true") {
            is_admin = true;
        } else if (st == "false") {
            is_admin = false;
        } else {
            encrypted_id = st;
        }
    }

    // decode the encrypted token
    encrypted_id = this->crypto.decode(encrypted_id);

    return {encrypted_id, is_admin};
}

//Controller::App::create_user_account: creates new user account(admin, new user)
string Controller::App::create_user_account(string* token, string& username, string& password, bool is_admin) {
    DB::UserEntity user = DB::UserEntity(username, password, is_admin);

    // try to create the user
    DB::UserEntity* result = this->user_service.create(user);
    // failure creating the new user
    if (result == nullptr) {
        return UNABLE_TO_PERFORM_OPERATION;
    }

    string ret;

    if (token == nullptr) {
        ret =  USER_CREATED + result->to_string();
    } else {
        ret = ADMIN_CREATED + result->to_string();
    }

    return ret;
}

// Controller::App::login: login to user account
string Controller::App::login(string& username, string& password) {
    // input validation
    if (username.empty() || password.empty()) {
        return INVALID_INPUT;
    }

    // login function
    string token = this->user_service.login(username, password);
    if (token.empty()) {
        return UNABLE_TO_PERFORM_OPERATION;
    }

    return LOGIN_TOKEN + token;
}

// Controller::App::delete_user: to delete a user account
string Controller::App::delete_user(string &token, string*  user_id) {
    // input validation
    if (token.empty()) {
        return TOKEN_NOT_PROVIDED;
    }

    // extract the user id and the is_admin property
    auto token_pair = this->extract_token(token);
    if (token_pair.first.empty()) {
        return INVALID_TOKEN;
    }

    // case where the caller is not an admin
    if (user_id == nullptr) {
        user_id = &token_pair.first;
    }

    // initiate the delete function
    auto result = this->user_service.delete_(*user_id, token_pair.second);
    // failure
    if (result == nullptr) {
        return UNABLE_TO_PERFORM_OPERATION;
    }

    string return_str = result->to_string();

    delete result;

    return return_str;
}

// Controller::App::get_user: to get a user by self or admin
string Controller::App::get_user(string& token, string* user_id) {
    // input validation
    if (token.empty()) {
        return TOKEN_NOT_PROVIDED;
    }

    // extract the is_admin and the user_id value from the token
    auto token_pair = this->extract_token(token);
    if (token_pair.first.empty()) {
        return INVALID_TOKEN;
    }

    // case where the caller is not an admin
    if (user_id == nullptr) {
        user_id = &token_pair.first;
    }

    // fetch the user details
    auto result = this->user_service.get(*user_id);
    if (result == nullptr) {
        return RECORD_NOT_FOUND;
    }

    // blind the password for user details protection
    result->password = "**********";

    string result_str = result->to_string();

    return result_str;
}

//Controller::App::update_user: update a user details
string Controller::App::update_user(string& token, string* user_id, string* username, string* password) {
    // input validation
    if (token.empty()) {
        return TOKEN_NOT_PROVIDED;
    }

    // extract the is_admin and user_id from the login token
    auto token_pair = this->extract_token(token);
    if (token_pair.first.empty()) {
        return INVALID_TOKEN;
    }

    if (user_id == nullptr) {
        user_id = &token_pair.first;
    }

    // get user by id first
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

    // update the user
    auto result = this->user_service.update(*user, token_pair.second, *user_id, password != nullptr);
    // failure
    if (result == nullptr) {
        return UNABLE_TO_PERFORM_OPERATION;
    }

    string result_str = "UPDATED: " + result->to_string();

    return result_str;
}

//Controller::App::create_password create the password (WEB, GAME, DESKTOP)
string Controller::App::create_password(string& token, string& typ, string* URL, string& username, string& password, string& name, string* developer, string* user_id) {
    // token validation
    if (token.empty()) {
        return TOKEN_NOT_PROVIDED;
    }

    // extract the user_id and is_admin from the token
    auto token_pair = this->extract_token(token);
    if (token_pair.first.empty()) {
        return INVALID_TOKEN;
    }

    // if admin is creating for the user
    if (user_id == nullptr) {
        user_id = &token_pair.first;
    }

    string result;

    if (typ == "WEB") {
        // input validation
        if (URL == nullptr) {
            return INVALID_INPUT;
        }

        DB::WebPass web;

        web.password = password;
        web.name = name;
        web.user_id = *user_id;
        web.url = *URL;
        web.username = username;

        // try to create the instanciated web password
        auto pass = this->password_service.create(web);
        // failure
        if (pass == nullptr) {
            return UNABLE_TO_PERFORM_OPERATION;
        }

        result = pass->to_string();
    } else if (typ == "DESKTOP") {
        // instanciate the dektop password
        DB::DesktopPass desktop;
        desktop.user_id = *user_id;
        desktop.username = username;
        desktop.password = password;
        desktop.name = name;

        // try to create the password
        auto pass = this->password_service.create(desktop);

        // failure creating the password
        if (pass == nullptr) {
            return UNABLE_TO_PERFORM_OPERATION;
        }

        result = pass->to_string();
    } else if (typ == "GAME") {
        // input validation
        if (developer == nullptr) {
            return INVALID_INPUT;
        }

        // instanciate the game password
        DB::GamePass game;
        game.user_id = *user_id;
        game.username = username;
        game.password = password;
        game.developer = *developer;
        game.name = name;

        // try create the instanciated password
        auto pass = this->password_service.create(game);

        // failure
        if (pass == nullptr) {
            return UNABLE_TO_PERFORM_OPERATION;
        }

        result = pass->to_string();
    } else {
        result = INVALID_OPERATION;
    }

    return result;
}

// Controller::App::get_password: get password by id
string Controller::App::get_password(string& token, string& pass_id) {
    // input validation
    if (token.empty()) {
        return TOKEN_NOT_PROVIDED;
    }

    // input validation
    if (pass_id.empty()) {
        return INVALID_INPUT;
    }

    // extract is_admin and user_id
    auto token_pair = this->extract_token(token);
    if (token_pair.first.empty()) {
        return INVALID_TOKEN;
    }

    // get the password
    auto result = this->password_service.get(pass_id);
    if (result == nullptr) {
        return RECORD_NOT_FOUND;
    }

    // check if the password blongs to the user or the user is an admin
    if (result->user_id != token_pair.first && !token_pair.second) {
        return NOT_AUTHORIZED;
    }

    string result_str = result->to_string();
    delete result;

    return result_str;
}

// Controller::App::delete_password: help delete a password by id
string Controller::App::delete_password(string& token, string& pass_id) {
    // input validation
    if (token.empty()) {
        return TOKEN_NOT_PROVIDED;
    }

    // input validation
    if (pass_id.empty()) {
        return INVALID_INPUT;
    }

    // extract the is_admin and the user_id property from the token
    pair<string, bool> token_pair = this->extract_token(token);
    if (token_pair.first.empty()) {
        return INVALID_TOKEN;
    }

    // try to perform the deleting action
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

// Controller::App::get_user_passwords: gets all user created passwords
string Controller::App::get_user_passwords(string& token, string* user_id) {
    // input validation
    if (token.empty()) {
        return TOKEN_NOT_PROVIDED;
    }

    // extract the is_admin and user_id from the token
    pair<string, bool> token_pair = this->extract_token(token);
    if (token_pair.first.empty()) {
        return INVALID_TOKEN;
    }

    // an admin wants to check a user list of passwords
    if (user_id != nullptr) {
        token_pair.first = *user_id;
    }

    // get all the passwords for the user with the provided id
    vector<DB::Pass*> passwords = this->password_service.get_all_user(token_pair.first);
    if (passwords.empty()) {
        return NO_PASSWORD_FOR_USER;
    }

    string result;

    // get the stringified value of the password
    for (const DB::Pass* pass: passwords) {
        result += pass->to_string() + "\n";
        delete pass;
    }

    passwords.clear();

    return result;
}

// Controller::App::search_password: search the list of user created passwords
string Controller::App::search_password(string& token, string& text){
    // input validation
    if (token.empty()) {
        return TOKEN_NOT_PROVIDED;
    }

    // input validation
    if (text.empty()) {
        return UNABLE_TO_PERFORM_OPERATION;
    }

    // extract the is_admin property and the user id from the login token
    pair<string, bool> token_pair = this->extract_token(token);
    if (token_pair.first.empty()) {
        return INVALID_TOKEN;
    }

    // Get the user passwords
    vector<DB::Pass*> passwords = this->password_service.get_all_user(token_pair.first);
    if (passwords.empty()) {
        return NO_PASSWORD_FOR_USER;
    }

    string result;

    // filter with the provided text
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
