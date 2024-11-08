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
DB::UserEntity* Service::User::update(DB::UserEntity updated, bool is_admin, string& user_id, bool password_changed) {
    if (updated.id.empty()) {
        return nullptr;
    }

    auto user = this->database.get(updated.id);

    if (user == nullptr) {
        return nullptr;
    }

    if (user->id != user_id && !is_admin) {
        cout << "ACTION NOT PERMITTED" << endl;
        return nullptr;
    }

    if (password_changed) {
        updated.password = this->crypto.hash(updated.password);
    }

    return this->database.update(updated.id, updated);
}

DB::UserEntity* Service::User::get(string& user_id) {
    if (user_id.empty()) {
        return nullptr;
    }

    auto user = this->database.get(user_id);

    if (user != nullptr) {
        user->password = "*************";
    }

    return user;
}

DB::UserEntity* Service::User::delete_(string& user_id, bool is_admin) {
    if (user_id.empty()) {
        return nullptr;
    }

    auto user = this->database.get(user_id);

    if (user == nullptr) {
        return nullptr;
    }

    auto result = this->database.delete_user(user_id);

    return result;
}

DB::UserEntity* Service::User::create(DB::UserEntity user) {
    user.id = this->crypto.generate_id();
    user.password = this->crypto.hash(user.password);

    auto result = this->database.create(user);

    return result;
}

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

    if (result != nullptr) {
        result->password = this->crypto.decode(result->password);
    }

    return result;
}

vector<DB::Pass*> Service::Password::get_all_user(string& user_id) {
    if (user_id.empty()) {
        cout << "USER ID IS INVALID" << endl;
        return {};
    }

    auto result = this->database.get_all(user_id);

    return result;
}

DB::Pass* Service::Password::delete_(const string& pass_id, bool is_admin, const string& user_id) {
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
