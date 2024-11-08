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
        DB::UserEntity* create();
        DB::UserEntity* delete_();
        DB::UserEntity* update();
        DB::UserEntity* get(string& user_id);
    };

    class Password{
    private:
        DB::Password database;
        Utils::Crypto crypto;
    public:
        //overload for desktop
//        DB::Pass* create(string& name, string& username, string& password, string& user_id, string& token);
//        // overload for game
//        DB::Pass* create(string& name,string& username, string& developer, string& password, string& user_id, string token);
//        //    overload for web
//        DB::Pass* create(string name, string& username, string& URL, string& password, string& user_id, string& token);

        DB::Pass* create(DB::GamePass pass, string& is_admin, string& user_id);
        DB::Pass* create(DB::WebPass pass, string& is_admin, string& user_id);
        DB::Pass* create(DB::DesktopPass pass, string& is_admin, string& user_id);

        DB::Pass* delete_(string& pass_id, string& is_admin, string& user_id);

        DB::Pass* update(DB::GamePass pass, string& is_admin, string& user_id);
        DB::Pass* update(DB::WebPass pass, string& is_admin, string& user_id);
        DB::Pass* update(DB::DesktopPass pass, string& is_admin, string& user_id);

        DB::Pass* get(string id);
        vector<DB::Pass*> get_all_user(string& user_id);
    };
}

#endif //PASSWORDMANAGER_SERVICE_H
