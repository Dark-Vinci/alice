//
// Created by Ademola Olutomiwa Abraham on 07/11/2024.
//

#include <string>

using namespace std;

#ifndef PASSWORDMANAGER_DATABASE_H
#define PASSWORDMANAGER_DATABASE_H

namespace DB {
    class UserEntity {
    private:
        string first_name;
        string last_name;
        string password;
        string created_at;
        string update_at;
        string deleted_at;
        string is_admin;

    public:
        UserEntity(bool is_admin, string first_name);

        string get_first_name();
        string get_last_name();
        void set_last_name();
        void set_first_name();
    };

    class Pass {
    private:
        string password;
        time_t created_at;
        time_t update_at;
        time_t* deleted_at;
        string user_id;
    };

    class WebPass: Pass {
    public:
        string url;
    };

    class GamePass: Pass {
    public:
        string developer;
    };

    class DesktopPass: Pass {
    public:
    };

    class User{
    public:
        void create();
        void delete_user();
        void update();
        void get();
    };

    class Password{
    private:
        string file_name;
    public:
        void create();
        void update();
        void get();
        void get_all();
        void delete_password();
    };
}

#endif //PASSWORDMANAGER_DATABASE_H
