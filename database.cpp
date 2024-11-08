//
// Created by Ademola Olutomiwa Abraham on 07/11/2024.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "database.h"

using namespace std;

// PASSWORD DATABASE IMPLEMENTATION
DB::Pass* DB::Password::delete_password(const string& password_id) {
    auto pass = this->get(password_id);

    if (pass == nullptr) {
        return nullptr;
    }

    //    READ THE DB FILE
    ifstream file(file_name);

    if (!file.is_open()) {
        cerr << "Could not open the file!" << endl;
        return nullptr;
    }

    //    CREATE A TEMP FILE TO HANDLE THE DELETING OF THE FILE
    ofstream temp_file("password_temp_file.txt");

    string line;
    bool found = false;

    while (getline(file, line)) {
        if (line.find(password_id) != string::npos) {
            found = true;
            continue;
        }
        temp_file << line << endl;
    }

    file.close();
    temp_file.close();

    //  IF FOUND; DELETE THE DB FILE  AND RENAME THE TEMP_FILE TO THE DB FILE
    if (found) {
        remove(file_name.c_str());
        rename("password_temp.txt", file_name.c_str());
    } else {
        remove("password_temp.txt");
    }

    return pass;
}

DB::Pass* DB::Password::update(DB::Pass& updated_password){
    auto pass = this->get(updated_password.id);

    if (pass == nullptr) {
        return nullptr;
    }

    auto updated = this->create(updated_password);

    if (updated == nullptr) {
        return nullptr;
    }

    return updated;
}

DB::Pass* DB::Password::create(DB::Pass& password) {
    ofstream file(file_name, ios::app);

    if (!file.is_open()) {
        cerr << "CANNOT OPEN FILE" << endl;
        return nullptr;
    }

    const string& password_string = password.to_string();

    file << password_string << endl;

    file.close();

    return &password;
}

DB::Pass* DB::Password::get(const string& password_id) {
    ifstream file(file_name);
    DB::Pass* password = nullptr;

    if (!file.is_open()) {
        cerr << "CANNOT OPEN FILE" << endl;
        return nullptr;
    }

    string line;

    while (getline(file, line)) {
        if (line.find(password_id) != string::npos) {
            if (line.compare(0, desktop_prefix.size(), desktop_prefix) == 0) {
                // a desktop application
                auto result = DB::DesktopPass::from_string(line);
                password = new DesktopPass(result);
            } else if (line.compare(0, game_prefix.size(), game_prefix) == 0) {
                // game app
                auto result = DB::GamePass::from_string(line);
                password = new GamePass(result);
            } else if ((line.compare(0, web_prefix.size(), web_prefix) == 0)) {
                auto result = DB::WebPass::from_string(line);
                password = new WebPass(result);
            }
            break;
        }
    }

    file.close();

    return password;
}

vector<DB::Pass*> DB::Password::get_all(const string& user_id) {
    ifstream file(file_name);
    vector<DB::Pass*> passwords = {};

    if (!file.is_open()) {
        cerr << "CANNOT OPEN FILE" << endl;
        return {};
    }

    string line;

    while (getline(file, line)) {
        if (line.find(user_id) != string::npos) {
            if (line.compare(0, desktop_prefix.size(), desktop_prefix) == 0) {
                // a desktop application
                auto result = DB::DesktopPass::from_string(line);
                passwords.push_back(new DesktopPass(result));
            } else if (line.compare(0, game_prefix.size(), game_prefix) == 0) {
                // game app
                auto result = DB::GamePass::from_string(line);
                passwords.push_back(new GamePass(result));
            } else if ((line.compare(0, web_prefix.size(), web_prefix) == 0)) {
                auto result = DB::WebPass::from_string(line);
                passwords.push_back(new WebPass(result));
            }
        }
    }

    file.close();

    return passwords;
}

// USER DATABASE IMPLEMENTATION
DB::UserEntity* DB::User::delete_user(const string& user_id) {
    if (user_id.empty()) {
        cout << "USER ID IS EMPTY" << endl;
        return nullptr;
    }

    //     CHECK IF THE USER IS STORED
    auto user = this->get(user_id);

    if (user == nullptr) {
        cout << "USER NOT FOUND" << endl;
        return nullptr;
    }

    //    READ THE DB FILE
    ifstream file(file_name);

    if (!file.is_open()) {
        cerr << "Could not open the file!" << endl;
        return nullptr;
    }

    //    CREATE A TEMP FILE TO HANDLE THE DELETING OF THE FILE
    ofstream temp_file("user_temp.txt");

    string line;
    bool found = false;

    while (getline(file, line)) {
        if (line.find(user_id) != string::npos) {
            found = true;
            continue;
        }
        temp_file << line << endl;
    }

    file.close();
    temp_file.close();

    //  IF FOUND; DELETE THE DB FILE  AND RENAME THE TEMP_FILE TO THE DB FILE
    if (found) {
        remove(file_name.c_str());
        rename("user_temp.txt", file_name.c_str());
    } else {
        remove("user_temp.txt");
    }

    return user;
}

DB::UserEntity* DB::User::create(UserEntity& user){
    ofstream file(file_name, ios::app);

    if (!file.is_open()) {
        cerr << "CANNOT OPEN FILE" << endl;
        return nullptr;
    }

     const string& user_string = user.to_string();

    file << user_string << endl;

    file.close();

    return &user;
}

DB::UserEntity* DB::User::get(const string& user_id) {
    ifstream file(file_name);
    DB::UserEntity* user = nullptr;

    if (!file.is_open()) {
        cerr << "CANNOT OPEN FILE" << endl;
        return nullptr;
    }

    string line;

    while (getline(file, line)) {
        DB::UserEntity temp_user = UserEntity::from_string(line);

        if (temp_user.id == user_id) {
            user = new DB::UserEntity(temp_user);
            break;
        }
    }

    file.close();

    return user;
}

DB::UserEntity* DB::User::update(const string& user_id, UserEntity& updated) {
    //   DELETE USER -> CREATE THE NEW USER
    auto old_user = this->delete_user(user_id);

    if (old_user == nullptr) {
        cout << "CANNOT UPDATE A USER THAT IS NOT CREATED" << endl;
        return nullptr;
    }

    auto new_user = this->create(updated);

    if (new_user == nullptr) {
        cout << "NOT UPDATED" << endl;
        return nullptr;
    }

    return new_user;
}
