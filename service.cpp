//
// Created by Ademola Olutomiwa Abraham on 07/11/2024.
//

#include <vector>
#include <string>
#include "service.h"
#include "database.h"

using namespace std;

// USER SERVICE IMPLEMENTATION
DB::UserEntity Service::User::update_user() {}

DB::UserEntity Service::User::delete_user() {}

vector<DB::UserEntity> Service::User::get_all() {}

void Service::User::delete_user(string user_id) {}

DB::UserEntity Service::User::create_account() {}


// PASSWORD SERVICE IMPLEMENTATION
DB::Pass Service::Password::update(string id) {}

DB::Pass Service::Password::get(string id, string user_id) {}

vector<DB::Pass> Service::Password::get_all_user(string user_id) {}

string Service::Password::delete_(string user_id, string id) {}

DB::Pass Service::Password::create() {}
