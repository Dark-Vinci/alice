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

//void create(const UserEntity& user);
//void delete_user(const string& user_id);
//void update(const string& user_id, const UserEntity& updated);
//void get(const string& user_id);

// USER DATABASE IMPLEMENTATION
void DB::User::delete_user() {}

void DB::User::create(const UserEntity& user){
    std::ifstream file(file_name, ios::app);

    if (!file.is_open()) {
        cerr << "CANNOT OPEN FILE" << endl;
        return;
    }



    file.close();
}

void DB::User::get() {}

void DB::User::update() {}