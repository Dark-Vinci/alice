//
// Created by Ademola Olutomiwa Abraham on 07/11/2024.
//

#include "database.h"
#include "util.h"

#ifndef PASSWORDMANAGER_SERVICE_H
#define PASSWORDMANAGER_SERVICE_H

namespace Service {
    class User {
    private:
        DB::User database;
        Utils::Crypto crypto;
    public:
        DB::UserEntity* create(DB::UserEntity user);
        DB::UserEntity* delete_(string& user_id, bool is_admin);
        DB::UserEntity* update(DB::UserEntity updated, bool is_admin, string& user_id, bool password_changed);
        DB::UserEntity* get(string& user_id);
        DB::UserEntity* get_by_username(const string& username);
        string login(string& username, string& password);
    };

    class Password{
    private:
        DB::Password database;
        Utils::Crypto crypto;
    public:
        DB::Pass* create(DB::GamePass pass);
        DB::Pass* create(DB::WebPass pass);
        DB::Pass* create(DB::DesktopPass pass);

        DB::Pass* delete_(const string& pass_id, bool is_admin, const string& user_id);

        DB::Pass* update(DB::GamePass pass, bool is_admin, string& user_id);
        DB::Pass* update(DB::WebPass pass, bool is_admin, string& user_id);
        DB::Pass* update(DB::DesktopPass pass, bool is_admin, string& user_id);

        DB::WebPass* get_web(const string& id);
        DB::GamePass* get_game(const string& id);
        DB::DesktopPass* get_desktop(const string& id);

        DB::Pass* get(const string& id);
        vector<DB::Pass*> get_all_user(string& user_id);
    };
}

#endif //PASSWORDMANAGER_SERVICE_H
