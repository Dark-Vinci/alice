//
// Created by Ademola Olutomiwa Abraham on 07/11/2024.
//

#include <string>
#include <sstream>
#include <iostream>
#include "util.h"

using namespace std;

#ifndef PASSWORDMANAGER_DATABASE_H
#define PASSWORDMANAGER_DATABASE_H

namespace DB {
    class UserEntity {
    public:
        string password;
        string username;
        time_t created_at;
        time_t updated_at;
        bool is_admin;
        string id;

    public:
        UserEntity();

        UserEntity(string& username, string& password, bool is_admin) {
            this->username = username;
            this->password = password;
            this->created_at = time(0);
            this->updated_at = time(0);
            this->is_admin = is_admin;
        }

        string to_string();

        static UserEntity* from_string(string& str);
    };

    class Pass {
    public:
        string username;
        string name;
        string password;
        time_t created_at;
        time_t updated_at;
        string user_id;
        string id;

    public:
        Pass(){}

        Pass(string& username, string& password, string& name, string& user_id) {
            this->created_at = time(0);
            this->updated_at = time(0);
            this->password = password;
            this->username = username;
            this->user_id = user_id;
            this->name = name;
        }

        // Common function for all passes (could be overridden in derived classes)
        [[nodiscard]] virtual string to_string() const {
            stringstream ss;

            ss << "Pass->"
               << "username:" + username + ","
               << "user_id:" + user_id + ","
               << "password:" + password + ","
               << "created_at:" + std::to_string(created_at) + ","
               << "updated_at:" + std::to_string(updated_at) + ","
               << "id:" + id + ","
               << "name:" + name;

            return ss.str();
        }
    };

    class WebPass: public Pass {
    public:
        string url;

        WebPass();

        WebPass(string& username, string& password, string& name, string& user_id, string& url)
                : Pass(username, password, name, user_id), url(url) {};

        [[nodiscard]] string to_string() const override;

        static WebPass* from_string(string& str);
    };

    class GamePass: public Pass {
    public:
        string developer;

        GamePass();

        GamePass(string& username, string& password, string& name, string& user_id, string& developer)
            : Pass(username, password, name, user_id), developer(developer) {}

        [[nodiscard]] string to_string() const override;

        static GamePass* from_string(string& str);
    };

    class DesktopPass: public Pass {
    public:
        DesktopPass();

        DesktopPass(string& username, string& password, string& name, string& user_id, string& developer)
            : Pass(username, password, name, user_id) {};

        [[nodiscard]] string to_string() const override;

        static DesktopPass* from_string(string& str);
    };

    class User{
    private:
        string file_name = "new_user_file.txt";
    public:
        UserEntity* create(UserEntity& user);
        UserEntity* delete_user(const string& user_id);
        UserEntity* update(const string& user_id, UserEntity& updated);
        UserEntity* get(const string& user_id);
        UserEntity* get_user_by_username(const string& username);
    };

    class Password{
    private:
        string file_name = "new_password_file.txt";
        string password_temp_file = "password_temp.text";
        string desktop_prefix = "DesktopPass->";
        string web_prefix = "WebPass->";
        string game_prefix = "GamePass->";
    public:
        Pass* create(Pass& password);
        Pass* update(Pass& updated_password);
        Pass* get(const string& password_id);
        WebPass* get_web(const string& id);
        GamePass* get_game(const string& id);
        DesktopPass* get_desktop(const string& id);
        vector<Pass*> get_all(const string& user_id);
        Pass* delete_password(const string& password_id);
    };
}

#endif //PASSWORDMANAGER_DATABASE_H
