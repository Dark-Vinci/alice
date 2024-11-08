//
// Created by Ademola Olutomiwa Abraham on 07/11/2024.
//

#include <vector>
#include <string>
#include <iostream>
#include "service.h"
#include "database.h"

using namespace std;

// USER SERVICE IMPLEMENTATION
DB::UserEntity Service::User::update_user() {}

DB::UserEntity Service::User::delete_user() {}

vector<DB::UserEntity> Service::User::get_all() {}

void Service::User::delete_user(string user_id) {}

DB::UserEntity Service::User::create_account() {}

// PASSWORD SERVICE IMPLEMENTATION
DB::Pass* Service::Password::update(DB::GamePass pass, bool is_admin, string& user_id) {
    if (pass.id.empty()) {
        return nullptr;
    }

    auto fetch = this->database.get(pass.id);

    if (fetch == nullptr) {
        return nullptr;
    }

    if (!is_admin && fetch->user_id != pass.user_id) {
        cout << "ONLY ADMINS CAN DELETE FOR ANOTHER USER" << endl;
        return nullptr;
    }

    auto result = this->database.update(pass);

    return result;
}

DB::Pass* Service::Password::update(DB::WebPass pass, bool is_admin, string& user_id) {
    if (pass.id.empty()) {
        return nullptr;
    }

    auto fetch = this->database.get(pass.id);

    if (fetch == nullptr) {
        return nullptr;
    }

    if (!is_admin && fetch->user_id != user_id) {
        cout << "ONLY ADMINS CAN DELETE FOR ANOTHER USER" << endl;
        return nullptr;
    }

    auto result = this->database.update(pass);

    return result;
}

DB::Pass* Service::Password::update(DB::DesktopPass pass, bool is_admin, string& user_id) {
    if (pass.id.empty()) {
        return nullptr;
    }

    auto fetch = this->database.get(pass.id);

    if (fetch == nullptr) {
        return nullptr;
    }

    if (!is_admin && fetch->user_id != user_id) {
        cout << "ONLY ADMINS CAN DELETE FOR ANOTHER USER" << endl;
        return nullptr;
    }

    auto result = this->database.update(pass);

    return result;
}

DB::Pass* Service::Password::get(const string& id) {
    if (id.empty()) {
        return nullptr;
    }

    auto result = this->database.get(id);

    return result;
}

vector<DB::Pass*> Service::Password::get_all_user(string& user_id) {
    if (user_id.empty()) {
        cout << "USER ID IS INVALID" << endl;
        return {};
    }

    auto result = this->get_all_user(user_id);

    return result;
}

DB::Pass* Service::Password::delete_(const string& pass_id, const bool is_admin, const string& user_id) {
    if (pass_id.empty()) {
        return nullptr;
    }

    auto pass = this->database.get(pass_id);

    if (pass == nullptr) {
        cout << "PASSWORD DOESN;T EXIST" << endl;
        return nullptr;
    }

    if (pass->id != user_id) {
        cout << "INVALID ACTION" << endl;
        return nullptr;
    }

    auto result = this->database.delete_password(pass_id);

    return result;
}

DB::Pass* Service::Password::create(DB::GamePass pass, bool is_admin, string& user_id) {
    if (pass.password.empty()) {
        pass.password = this->crypto.generate_random_password(10);
    }

    pass.password = this->crypto.encode(pass.password);

    auto result = this->database.create(pass);

    if (result == nullptr) {
        cout << "NOT CREATED" << endl;
        return nullptr;
    }

    return result;
}

DB::Pass* Service::Password::create(DB::WebPass pass, bool is_admin, string& user_id) {
    if (pass.password.empty()) {
        pass.password = this->crypto.generate_random_password(10);
    }

    pass.password = this->crypto.encode(pass.password);

    auto result = this->database.create(pass);

    if (result == nullptr) {
        cout << "NOT CREATED" << endl;
        return nullptr;
    }

    return result;
}

DB::Pass* Service::Password::create(DB::DesktopPass pass, bool is_admin, string& user_id) {
    if (pass.password.empty()) {
        pass.password = this->crypto.generate_random_password(10);
    }

    pass.password = this->crypto.encode(pass.password);

    auto result = this->database.create(pass);

    if (result == nullptr) {
        cout << "NOT CREATED" << endl;
        return nullptr;
    }

    return result;
}
