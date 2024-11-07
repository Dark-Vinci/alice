//
// Created by Ademola Olutomiwa Abraham on 07/11/2024.
//

#include "database.h";
#include "util.h";

#ifndef PASSWORDMANAGER_SERVICE_H
#define PASSWORDMANAGER_SERVICE_H

namespace Service {
    class User {
    private:
        DB::User database;
        Utils::Crypto crypto;
    public:
        DB::UserEntity create_account();
        void delete_user(string user_id);
        DB::UserEntity delete_user();
        DB::UserEntity update_user();
        vector<DB::UserEntity> get_all();
    };

    class Password{
    private:
        DB::Password database;
        Utils::Crypto crypto;
    public:
        DB::Pass create();
        string delete_(string user_id, string id);
        DB::Pass update(string id);
        DB::Pass get(string id, string user_id);
        vector<DB::Pass> get_all_user(string user_id);
    };
}

#endif //PASSWORDMANAGER_SERVICE_H
