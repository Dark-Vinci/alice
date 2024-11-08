//
// Created by Ademola Olutomiwa Abraham on 07/11/2024.
//

#include <string>
//#include <ctime>
//#include <iomanip>
//#include <sstream>
//#include <utility>

using namespace std;

#ifndef PASSWORDMANAGER_DATABASE_H
#define PASSWORDMANAGER_DATABASE_H

namespace DB {
    class UserEntity {
    public:
        string first_name;
        string last_name;
        string password;
        time_t created_at;
        time_t update_at;
        time_t* deleted_at;
        bool is_admin;
        string id;

    public:
        string to_string() {
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
    public:
        string username;
        string name;
        string password;
        time_t created_at;
        time_t updated_at;
        time_t* deleted_at;
        string user_id;
        string id;

    public:
        Pass(string  pwd, string  user)
                : password(std::move(pwd)), user_id(std::move(user)), deleted_at(nullptr) {
            created_at = time(nullptr);
            updated_at = created_at;
        }

        virtual ~Pass() {
            delete deleted_at;
        }

        // Common function for all passes (could be overridden in derived classes)
        [[nodiscard]] virtual string to_string() const;
    };

    class WebPass: public Pass {
    public:
        string url;

        WebPass()
                : Pass(pwd, user), url(std::move(url_)) {};

        [[nodiscard]] string to_string() const override {
            cout << "DesktopPass with generic data" << endl;
            return "WEB_PASSWORD:";
        }

        static WebPass from_string(string& str) {

        }
    };

    class GamePass: public Pass {
    public:
        string developer;

        GamePass()
                : Pass(pwd, user), developer(std::move(dev)) {};

        [[nodiscard]] string to_string() const override {
            cout << "DesktopPass with generic data" << endl;
            return "GAME_PASSWORD:";
        }

        static GamePass from_string(string& str) {

        }
    };

    class DesktopPass: public Pass {
    public:
        DesktopPass()
                : Pass(pwd, user) {};

        [[nodiscard]] string to_string() const override {
            return "DESKTOP_PASSWORD:";
        }

        static DesktopPass from_string(string& str) {

        }
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
        string password_temp_file = "password_temp.text";
        string desktop_prefix = "DESKTOP:";
        string web_prefix = "WEB:";
        string game_prefix = "GAME:";
    public:
        Pass* create(Pass& password);
        Pass* update(Pass& updated_password);
        Pass* get(const string& password_id);
        vector<Pass*> get_all(const string& user_id);
        Pass* delete_password(const string& password_id);
    };
}

#endif //PASSWORDMANAGER_DATABASE_H
