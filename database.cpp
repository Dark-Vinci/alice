//
// Created by Ademola Olutomiwa Abraham on 07/11/2024.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "database.h"

using namespace std;

DB::UserEntity::UserEntity() {}

DB::GamePass::GamePass() {}

DB::DesktopPass::DesktopPass() {
}

DB::WebPass::WebPass() {}

// PASSWORD DATABASE IMPLEMENTATION

// DB::Password::delete_password: delete a password by its id
DB::Pass* DB::Password::delete_password(const string& password_id) {
    // fetch the password by its ID
    auto pass = this->get(password_id);

    if (pass == nullptr) {
        return nullptr;
    }

    //    READ THE DB FILE
    ifstream file(file_name);

    // if the file could not be open, return a nullptr value
    if (!file.is_open()) {
        cerr << "Could not open the file!" << endl;
        return nullptr;
    }

    //    CREATE A TEMP FILE TO HANDLE THE DELETING OF THE FILE
    ofstream temp_file("password_temp_file.txt");

    string line;
    bool found = false;

    // filter the required lines out
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
        rename("password_temp_file.txt", file_name.c_str());
    } else {
        remove("password_temp_file.txt");
    }

    return pass;
}

// DB::Password::get_web: get a web password by its id
DB::WebPass* DB::Password::get_web(const string& id) {
    ifstream file(file_name);

    // file could not be opned
    if (!file.is_open()) {
        cerr << "CANNOT OPEN FILE" << endl;
        return nullptr;
    }

    DB::WebPass* password = nullptr;

    string line;

    // filter the required lines out
    while (getline(file, line)) {
        if (line.find(id) != string::npos) {
            if ((line.compare(0, web_prefix.size(), web_prefix) == 0)) {
                password = DB::WebPass::from_string(line);
            }
            break;
        }
    }

    file.close();

    return password;
}

// DB::Password::get_game: get a game password by its id
DB::GamePass* DB::Password::get_game(const string& id) {
    ifstream file(file_name);
    DB::GamePass* password = nullptr;

    if (!file.is_open()) {
        cerr << "CANNOT OPEN FILE" << endl;
        return nullptr;
    }

    string line;

    // filter where the password id is equal to the input id
    while (getline(file, line)) {
        if (line.find(id) != string::npos) {
            if ((line.compare(0, game_prefix.size(), game_prefix) == 0)) {
                password = DB::GamePass::from_string(line);
            }
            break;
        }
    }

    // close the open file
    file.close();

    return password;
}

//DB::Password::get_desktop gets a desktop password by it's id
DB::DesktopPass* DB::Password::get_desktop(const string& id) {
    ifstream file(file_name);
    DB::DesktopPass* password = nullptr;

    if (!file.is_open()) {
        cerr << "CANNOT OPEN FILE" << endl;
        return nullptr;
    }

    string line;

    // filter the desktop where the id is equal to the input id
    while (getline(file, line)) {
        if (line.find(id) != string::npos) {
            if ((line.compare(0, game_prefix.size(), game_prefix) == 0)) {
                password = DB::DesktopPass::from_string(line);
            }
            break;
        }
    }

    //close the opened file
    file.close();

    return password;
}

//DB::Password::update:  update a password
DB::Pass* DB::Password::update(DB::Pass& updated_password){
    auto pass = this->delete_password(updated_password.id);

    // failure to delete
    if (pass == nullptr) {
        return nullptr;
    }

    // create a new password
    auto updated = this->create(updated_password);

    // unable to create
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

//DB::Password::get: get a password by its id
DB::Pass* DB::Password::get(const string& password_id) {
    ifstream file(file_name);
    DB::Pass* password = nullptr;

    if (!file.is_open()) {
        cerr << "CANNOT OPEN FILE" << endl;
        return nullptr;
    }

    string line;

    // filters the password and convert the string to the password object
    while (getline(file, line)) {
        if (line.find(password_id) != string::npos) {
            if (line.compare(0, desktop_prefix.size(), desktop_prefix) == 0) {
                // a desktop application
                password = DB::DesktopPass::from_string(line);
            } else if (line.compare(0, game_prefix.size(), game_prefix) == 0) {
                // game app
                password = DB::GamePass::from_string(line);
            } else if ((line.compare(0, web_prefix.size(), web_prefix) == 0)) {
                // web password
                password = DB::WebPass::from_string(line);
            }
            break;
        }
    }

    // close file
    file.close();

    return password;
}

//DB::Password::get_all: gets all passwords related/created by a user
vector<DB::Pass*> DB::Password::get_all(const string& user_id) {
    ifstream file(file_name);
    vector<DB::Pass*> passwords = {};

    if (!file.is_open()) {
        cerr << "CANNOT OPEN FILE" << endl;
        return {};
    }

    string line;

    // filter the passwords by the user id
    while (getline(file, line)) {
        if (line.find(user_id) != string::npos) {
            if (line.compare(0, desktop_prefix.size(), desktop_prefix) == 0) {
                // a desktop application
                auto result = DB::DesktopPass::from_string(line);
                passwords.push_back(result);
            } else if (line.compare(0, game_prefix.size(), game_prefix) == 0) {
                // game app
                auto result = DB::GamePass::from_string(line);
                passwords.push_back(result);
            } else if ((line.compare(0, web_prefix.size(), web_prefix) == 0)) {
                auto result = DB::WebPass::from_string(line);
                passwords.push_back(result);
            }
        }
    }

    // close file
    file.close();

    return passwords;
}

// USER DATABASE IMPLEMENTATION
DB::UserEntity* DB::User::delete_user(const string& user_id) {
    // validate the user id is not empty
    if (user_id.empty()) {
        return nullptr;
    }

    //     CHECK IF THE USER IS STORED
    auto user = this->get(user_id);

    // user is not found
    if (user == nullptr) {
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

    // filter the needed user
    while (getline(file, line)) {
        if (line.find(user_id) != string::npos) {
            found = true;
            continue;
        }
        temp_file << line << endl;
    }

    // close both opened files
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

// DB::User::create, create a new user
DB::UserEntity* DB::User::create(UserEntity& user){
    ofstream file(file_name, ios::app);

    // error opening file
    if (!file.is_open()) {
        cerr << "CANNOT OPEN FILE" << endl;
        return nullptr;
    }

     const string& user_string = user.to_string();

    file << user_string << endl;

    // close the opened file
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
        DB::UserEntity* temp_user = UserEntity::from_string(line);

        if (temp_user->id == user_id) {
            user = temp_user;
            break;
        }
    }

    file.close();

    return user;
}

//DB::User::get_user_by_username; help get a user by their username
DB::UserEntity* DB::User::get_user_by_username(const string& username) {
    ifstream file(file_name);
    DB::UserEntity* user = nullptr;

    // error opening file
    if (!file.is_open()) {
        cerr << "CANNOT OPEN FILE" << endl;
        return nullptr;
    }

    string line;

    // filter for when the username is equal to the input name
    while (getline(file, line)) {
        DB::UserEntity* temp_user = UserEntity::from_string(line);

        if (temp_user->username == username) {
            user = temp_user;
            break;
        }
    }

    // close the opened file
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

// DB::UserEntity::to_string; converts a user entity to a string
string DB::UserEntity::to_string() {
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

// DB::UserEntity::from_string; create a new user entity from a string
DB::UserEntity* DB::UserEntity::from_string(string& str) {
    string prefix = "User->";

    // input validation
    if (!str.starts_with(prefix)) {
        cerr << "CANNOT PARSE" << endl;
        return nullptr;
    }

    str.erase(0, prefix.size());

    // split the string by the char ','
    auto result = Utils::split(str, ',');

    auto* d = new UserEntity();

    // loop through and update the user entity with the right key:value pair
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

            if (entry == "1") {
                d->is_admin = true;
            } else {
                d->is_admin = false;
            }
        }
    }

    return d;
}

//DB::GamePass::to_string; converts a Game password to string
string DB::GamePass::to_string() const {
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

//DB::GamePass::from_string; create a GamePassword from a string
DB::GamePass* DB::GamePass::from_string(string& str) {
    string prefix = "GamePass->";

    // input validation
    if (!str.starts_with(prefix)) {
        cerr << "CANNOT PARSE" << endl;
        return nullptr;
    }

    str.erase(0, prefix.size());

    auto result = Utils::split(str, ',');

    GamePass* d = new GamePass();

    // loop through the fields and update the game pass with the appropriate values
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

//DB::DesktopPass::from_string; create a Desktop password from a string
DB::DesktopPass* DB::DesktopPass::from_string(string& str) {
    string prefix = "DesktopPass->";

    //input validation
    if (!str.starts_with(prefix)) {
        cerr << "CANNOT PARSE" << endl;
        return nullptr;
    }

    // remove the prefix
    str.erase(0, prefix.size());

    // split the string by the delimiter ','
    auto result = Utils::split(str, ',');

    DesktopPass* d = new DesktopPass();

    // fill the created password with its approriate fields
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
        } else if (entry.starts_with("id:")) {
            string p = "id:";

            entry.erase(0, p.size());

            d->id = entry;
        }
    }

    return d;
}

// DB::DesktopPass::to_string; converts a Desktop password to a string
string DB::DesktopPass::to_string() const {
    stringstream ss;

    ss << "DesktopPass->"
    << "id:" + id + ","
    << "name:" + name + ","
    << "username:" + username + ","
    << "user_id:" + user_id + ","
    << "password:" + password + ","
    << "created_at:" + std::to_string(created_at) + ","
    << "updated_at:" + std::to_string(updated_at);

    return ss.str();
}


// DB::WebPass::to_string; converts a Web password to a string
string DB::WebPass::to_string() const {
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

// DB::WebPass::from_string; creates a Webpassword from a string
DB::WebPass* DB::WebPass::from_string(string& str) {
    string prefix = "WebPass->";

    if (!str.starts_with(prefix)) {
        cerr << "CANNOT PARSE" << endl;
        return nullptr;
    }

    str.erase(0, prefix.size());

    // split the string by a delimiter
    auto result = Utils::split(str, ',');

    WebPass* d = new WebPass();

    // loop through the string and fill the web password with it's appropriate fields
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
        } else if (entry.starts_with("url:")) {
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
