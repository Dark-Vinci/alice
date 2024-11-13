//
// Created by Ademola Olutomiwa Abraham on 07/11/2024.
//
#include "ui.h"

void Terminal::print_options() {
    cout << "INPUT NUMBER <1 - 9> TO PERFORM THE OPERATIONS BELOW" << endl;
    cout << "USE an hyphen \"-\" for values that are empty" << endl;

    //   User related actions
    cout << "0> Login To Account" << endl;
    cout << "1> Delete User/Self Account" << endl;
    cout << "2> Create User Account" << endl;
    cout << "3> Delete User Account" << endl;
    cout << "4> Update User Details" << endl;
    cout << "5> Create Password" << endl;
    cout << "6> Update User Password" << endl;
    cout << "7> Delete User password" << endl;
    cout << "8> Get All User Password" << endl;
    cout << "9> Get User Password" << endl;
    cout << "10> Search User passwords" << endl;
}

void Terminal::start() {
    cout << "WELCOME TO THE TERMINAL PASSWORD MANAGER" << endl;

    while (true) {
        print_options();

        int typ;
        cin >> typ;

        switch (typ) {
            //     To login to user account, kindly use the right username and password used in the creation of the user account
            case 0: {
                string username, password;

                cout << USERNAME;
                cin >> username;

                cout << PASSWORD;
                cin >> password;

                string result = this->application.login(username, password);
                cout << "RESULT: " + result << endl;
                break;
            }

            // To delete a user account
            // if admin, provide the user_id of the user to be deleted
            // else just provide your login token and use "-" for the user_id
            case 1: {
                string token, user_id;

                cout << USER_ID;
                cin >> user_id;

                cout << TOKEN;
                cin >> token;

                string* user_id_ptr = user_id == "-" ? nullptr : &user_id;

                string result = this->application.delete_user(token, user_id_ptr);
                cout << "RESULT: " + result << endl;

                break;
            }

            //  Create a User account
            // If an admin is creating the account for the user, he/she must provide a login token
            // provide your name, password and *token(if admin)
            case 2: {
                string username, password, token;

                cout << USERNAME;
                cin >> username;

                cout << PASSWORD;
                cin >> password;

                cout << TOKEN;
                cin >> token;

                string* token_ptr = token=="-" ? nullptr : &token;

                string result = this->application.create_user_account(token_ptr, username, password, token=="-");

                cout << "RESULT: " + result << endl;
                break;
            }

            // Get User details fetches the user account details{username, password, created_at, updated_at, user_id}
            // For both admin and normal user
            // token must be provided, if admin (provide the user_id you wish to get)
            // use "-" when you mean empty value
            case 3: {
                string user_id, token;

                cout << TOKEN;
                cin >> token;

                cout << USER_ID;
                cin >> user_id;

                string* user_id_prt = user_id == "-" ? nullptr : &user_id;

                string result = this->application.get_user(token, user_id_prt);
                cout << "RESULT: " + result << endl;

                break;
            }

            // To update a user account
            // provide your login token(must)
            // username if you wish to update "-" if not
            // password if you wish to update "-" if not
            // provide the user_id if an admin
            case 4: {
                string user_id, token, username, password;

                cout << TOKEN;
                cin >> token;

                cout << USER_ID;
                cin >> user_id;

                cout << USERNAME;
                cin >> username;

                cout << PASSWORD;
                cin >> password;

                string* user_id_ptr = user_id == "-" ? nullptr : &user_id;
                string* password_ptr = password == "-" ? nullptr : &password;
                string* username_ptr = username == "-" ? nullptr : &username;

                string result = this->application.update_user(token,  user_id_ptr, username_ptr, password_ptr);
                cout << "RESULT: " + result << endl;

                break;
            }

            //
            case 5: {
                string user_id, token, username, password, type, URL_, developer, name;

                cout << TOKEN;
                cin >> token;

                cout << USER_ID;
                cin >> user_id;

                cout << USERNAME;
                cin >> username;

                cout << PASSWORD;
                cin >> password;

                cout << TYPE;
                cout << "WEB or DESKTOP or GAME: " << endl;
                cin >> type;

                if (type == "WEB") {
                    cout << URL;
                    cin >> URL_;
                }

                if (type == "GAME") {
                    cout << DEVELOPER;
                    cin >> developer;
                }

                cout << NAME;
                cin >> name;

                string* URL_ptr = URL_ == "-" ? nullptr : &URL_;
                string* developer_ptr = developer == "-" ? nullptr : &developer;
                string* user_id_ptr = user_id == "-" ? nullptr : &user_id;

                string result = this->application.create_password(token, type, URL_ptr, username, password, name, developer_ptr, user_id_ptr);

                cout << "RESULT: " + result << endl;

                break;
            }

            case 6: {
                string user_id, token, username, password, type, URL_, developer, name, id;

                cout << TYPE;
                cout << "WEB or DESKTOP or GAME" << endl;
                cin >> type;

                cout << TOKEN;
                cin >> token;

                cout << USER_ID;
                cin >> user_id;

                cout << USERNAME;
                cin >> username;

                cout << PASSWORD;
                cin >> password;

                cout << URL;
                cin >> URL_;

                cout << DEVELOPER;
                cin >> developer;

                cout << NAME;
                cin >> name;

                cout << ID;
                cin >> id;

                string* URL_ptr = URL_ == "-" ? nullptr : &URL_;
                string* developer_ptr = developer == "-" ? nullptr : &developer;
                string* name_ptr = name == "-" ? nullptr : &name;
                string* username_ptr = username == "-" ? nullptr : &username;
                string* password_ptr = password == "-" ? nullptr : &password;
                string* user_id_ptr = user_id == "-" ? nullptr : &user_id;

                string result = this->application.update_password(token, type, user_id_ptr, id, URL_ptr, username_ptr, password_ptr, name_ptr, developer_ptr);
                cout << "RESULT: " + result << endl;

                break;
            }

            case 7: {
                string token, password_id;

                cout << TOKEN;
                cin >> token;

                cout << PASSWORD_ID;
                cin >> password_id;

                string result = this->application.delete_password(token, password_id);
                cout << "RESULT: " + result << endl;
                break;
            }

            case 8: {
                string token, user_id;

                cout << TOKEN;
                cin >> token;

                cout << USER_ID;
                cin >> user_id;

                string result = this->application.get_user_passwords(token, user_id);
                cout << "RESULT: " + result << endl;
                break;
            }

            case 9: {
                string token, password_id;

                cout << TOKEN;
                cin >> token;

                cout << PASSWORD_ID;
                cin >> password_id;

                string result = this->application.get_password(token, password_id);
                cout << "RESULT: " + result << endl;
                break;
            }

            case 10: {
                string token, text;

                cout << TOKEN;
                cin >> token;

                cout << TEXT;
                cin >> text;

                string result = this->application.search_password(token, text);
                cout << "RESULT: " + result << endl;
                break;
            }

            default: {
                cout << "TERMINATING APPLICATION" << endl;
                return;
            }
        }

        cout << "____________________________________________________________________________________________________________________________________________" << endl;
    }
}
