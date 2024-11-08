//
// Created by Ademola Olutomiwa Abraham on 07/11/2024.
//
#include <iostream>
#include <fstream>
#include "database.h"

using namespace std;

// PASSWORD DATABASE IMPLEMENTATION
void DB::Password::delete_password() {}

void DB::Password::update(){}

void DB::Password::create() {}

void DB::Password::get() {}

void DB::Password::get_all() {}

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
    ofstream temp_file("temp.txt");

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
        rename("temp.txt", file_name.c_str());
    } else {
        remove("temp.txt");
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