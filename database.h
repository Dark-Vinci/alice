//
// Created by Ademola Olutomiwa Abraham on 07/11/2024.
//

#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

#ifndef PASSWORDMANAGER_DATABASE_H
#define PASSWORDMANAGER_DATABASE_H

namespace DB {

    class UserEntity {
    private:
        string first_name;
        string last_name;
        string password;
        time_t created_at;
        time_t update_at;
        time_t* deleted_at;
        bool is_admin;
    public:
        string id;

    public:
        UserEntity();

        const string to_string() {
            string result;

            result += "FirstName:" + first_name + ",";
            result += "LastName:" + last_name + ",";
            result += "Password:" + password + ",";
            result += "CreatedAt" + std::to_string(created_at) + ",";
            result += "UpdatedAt" + std::to_string(update_at) + ",";

            if (deleted_at != nullptr) {
                result += "DeletedAt:" + std::to_string(*deleted_at) + ",";
            }

            result += "IsAdmin:" + std::to_string(is_admin);

            return result;
        }

        static UserEntity from_string(string& user_string) {
//            return ;
        }
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
    private:
        string file_name;
    public:
        UserEntity* create(UserEntity& user);
        UserEntity* delete_user(const string& user_id);
        UserEntity* update(const string& user_id, UserEntity& updated);
        UserEntity* get(const string& user_id);
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
