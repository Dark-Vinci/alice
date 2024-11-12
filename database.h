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

        string to_string() {
            stringstream result;

            result << "User->";
            result << "id:" + id + ",";
            result << "password:" + password + ",";
            result << "username:" + username + ",";
            result << "created_at:" + std::to_string(created_at) + ",";
            result << "updated_at:" + std::to_string(updated_at) + ",";
            result << "is_admin:" + std::to_string(is_admin);

            return result.str();
        }

        static UserEntity* from_string(string& str) {
            string prefix = "User->";

            if (!str.starts_with(prefix)) {
                cerr << "CANNOT PARSE" << endl;
                return nullptr;
            }

            str.erase(0, prefix.size());

            auto result = Utils::split(str, ',');

            auto* d = new UserEntity();

            for (string& entry: result) {
                if (entry.starts_with("updated_at:")) {
                    string p = "updated_at:";

                    entry.erase(0, p.size());

                    d->updated_at = Utils::stringToTimeT(entry);
                } else if (entry.starts_with("created_at:")) {
                    string p = "created_at:";

                    entry.erase(0, p.size());

                    d->created_at = Utils::stringToTimeT(entry);
                } else if (entry.starts_with("username:")) {
                    string p = "username:";

                    entry.erase(0, p.size());

                    d->username = entry;
                } else if (entry.starts_with("password:")) {
                    string p = "password:";

                    entry.erase(0, p.size());

                    d->password = entry;
                } else if (entry.starts_with("id:")) {
                    string p = "id:";

                    entry.erase(0, p.size());

                    d->id = entry;
                }else if (entry.starts_with("is_admin:")) {
                    string p = "is_admin:";

                    entry.erase(0, p.size());

                    if (entry == "true") {
                        d->is_admin = true;
                    } else {
                        d->is_admin = false;
                    }
                }
            }

            return d;
        }
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

            ss << "WebPass->"
               << "username:" + username + ","
               << "user_id:" + user_id + ","
               << "password:" + password + ","
               << "created_at:" + std::to_string(created_at) + ","
               << "updated_at: " + std::to_string(updated_at) + ","
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

        [[nodiscard]] string to_string() const override {
            stringstream ss;

            ss << "WebPass->"
            << "username:" + username + ","
            << "user_id:" + user_id + ","
            << "password:" + password + ","
            << "created_at:" + std::to_string(created_at) + ","
            << "updated_at: " + std::to_string(updated_at) + ","
            << "id:" + id + ","
            << "name:" + name + ","
            << "url:" + url;

            return ss.str();
        }

        static WebPass* from_string(string& str) {
            string prefix = "WebPass->";

            if (!str.starts_with(prefix)) {
                cerr << "CANNOT PARSE" << endl;
                return nullptr;
            }

            str.erase(0, prefix.size());

            auto result = Utils::split(str, ',');

            auto* d = new WebPass();

            for (string& entry: result) {
                if (entry.starts_with("updated_at:")) {
                    string p = "updated_at:";

                    entry.erase(0, p.size());

                    d->updated_at = Utils::stringToTimeT(entry);
                } else if (entry.starts_with("created_at:")) {
                    string p = "created_at:";

                    entry.erase(0, p.size());

                    d->created_at = Utils::stringToTimeT(entry);
                } else if (entry.starts_with("name:")) {
                    string p = "name:";

                    entry.erase(0, p.size());

                    d->name = entry;
                } else if (entry.starts_with("username:")) {
                    string p = "username:";

                    entry.erase(0, p.size());

                    d->username = entry;
                } else if (entry.starts_with("password:")) {
                    string p = "password:";

                    entry.erase(0, p.size());

                    d->password = entry;
                } else if (entry.starts_with("user_id:")) {
                    string p = "user_id:";

                    entry.erase(0, p.size());

                    d->user_id = entry;
                }else if (entry.starts_with("url:")) {
                    string p = "url:";

                    entry.erase(0, p.size());

                    d->url = entry;
                } else if (entry.starts_with("id:")) {
                    string p = "id:";

                    entry.erase(0, p.size());

                    d->id = entry;
                }
            }

            return d;
        }
    };

    class GamePass: public Pass {
    public:
        string developer;

        GamePass();

        GamePass(string& username, string& password, string& name, string& user_id, string& developer)
            : Pass(username, password, name, user_id), developer(developer) {}

        [[nodiscard]] string to_string() const override {
            stringstream ss;

            ss << "GamePass->"
             << "username:" + username + ","
             << "user_id:" + user_id + ","
             << "password:" + password + ","
             << "created_at:" + std::to_string(created_at) + ","
             << "updated_at: " + std::to_string(updated_at) + ","
             << "id:" + id + ","
             << "name:" + name + ","
             << "developer:" + developer;

            return ss.str();
        }

        static GamePass* from_string(string& str) {
            string prefix = "GamePass->";

            if (!str.starts_with(prefix)) {
                cerr << "CANNOT PARSE" << endl;
                return nullptr;
            }

            str.erase(0, prefix.size());

            auto result = Utils::split(str, ',');

            auto* d = new GamePass();

            for (string& entry: result) {
                if (entry.starts_with("updated_at:")) {
                    string p = "updated_at:";

                    entry.erase(0, p.size());

                    d->updated_at = Utils::stringToTimeT(entry);
                } else if (entry.starts_with("created_at:")) {
                    string p = "created_at:";

                    entry.erase(0, p.size());

                    d->created_at = Utils::stringToTimeT(entry);
                } else if (entry.starts_with("name:")) {
                    string p = "name:";

                    entry.erase(0, p.size());

                    d->name = entry;
                } else if (entry.starts_with("username:")) {
                    string p = "username:";

                    entry.erase(0, p.size());

                    d->username = entry;
                } else if (entry.starts_with("password:")) {
                    string p = "password:";

                    entry.erase(0, p.size());

                    d->password = entry;
                } else if (entry.starts_with("user_id:")) {
                    string p = "user_id:";

                    entry.erase(0, p.size());

                    d->password = entry;
                }else if (entry.starts_with("developer:")) {
                    string p = "developer:";

                    entry.erase(0, p.size());

                    d->developer = entry;
                } else if (entry.starts_with("id:")) {
                    string p = "id:";

                    entry.erase(0, p.size());

                    d->id = entry;
                }
            }

            return d;
        }
    };

    class DesktopPass: public Pass {
    public:
        DesktopPass();

        DesktopPass(string& username, string& password, string& name, string& user_id, string& developer)
            : Pass(username, password, name, user_id) {};

        [[nodiscard]] string to_string() const override {
            stringstream ss;

            ss << "DesktopPass->"
             << "id:" + id + ","
             << "name:" + name + ","
             << "username:" + username + ","
             << "user_id:" + user_id + ","
             << "password:" + password + ","
             << "created_at:" + std::to_string(created_at) + ","
             << "updated_at: " + std::to_string(updated_at);

            return ss.str();
        }

        static DesktopPass* from_string(string& str) {
            string prefix = "DesktopPass->";

            if (!str.starts_with(prefix)) {
                cerr << "CANNOT PARSE" << endl;
                return nullptr;
            }

            str.erase(0, prefix.size());

            auto result = Utils::split(str, ',');

            auto* d = new DesktopPass();

            cout << "LINNER" + str << endl;

            for (string& entry: result) {
                cout << "LINER: ENTRY ->" + entry << endl;
                if (entry.starts_with("updated_at:")) {
                    string p = "updated_at:";

                    entry.erase(0, p.size());

                    d->updated_at = Utils::stringToTimeT(entry);
                } else if (entry.starts_with("created_at:")) {
                    string p = "created_at:";

                    entry.erase(0, p.size());

                    d->created_at = Utils::stringToTimeT(entry);
                } else if (entry.starts_with("name:")) {
                    string p = "name:";

                    entry.erase(0, p.size());

                    d->name = entry;
                } else if (entry.starts_with("username:")) {
                    string p = "username:";

                    entry.erase(0, p.size());

                    d->username = entry;
                } else if (entry.starts_with("password:")) {
                    string p = "password:";

                    entry.erase(0, p.size());

                    d->password = entry;
                } else if (entry.starts_with("user_id:")) {
                    string p = "user_id:";

                    entry.erase(0, p.size());

                    d->user_id = entry;
                } else if (entry.starts_with("id:")) {
                    string p = "id:";

                    entry.erase(0, p.size());

                    cout << "IS-> ID" + entry << endl;

                    d->id = entry;
                }
            }

            return d;
        }
    };

    class User{
    private:
        string file_name = "./user_file.txt";
    public:
        UserEntity* create(UserEntity& user);
        UserEntity* delete_user(const string& user_id);
        UserEntity* update(const string& user_id, UserEntity& updated);
        UserEntity* get(const string& user_id);
        UserEntity* get_user_by_username(const string& username);
    };

    class Password{
    private:
        string file_name = "./password_file.text";
        string password_temp_file = "password_temp.text";
        string desktop_prefix = "DesktopPass->";
        string web_prefix = "WebPass->";
        string game_prefix = "GamePass->";
    public:
        Pass* create(Pass& password);
        Pass* update(Pass& updated_password);
        Pass* get(const string& password_id);
        vector<Pass*> get_all(const string& user_id);
        Pass* delete_password(const string& password_id);
    };
}

#endif //PASSWORDMANAGER_DATABASE_H
