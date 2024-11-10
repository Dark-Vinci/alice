//
// Created by Ademola Olutomiwa Abraham on 07/11/2024.
//
#include "ui.h"

void Terminal::print_options() {
    cout << "INPUT NUMBER <1 - 9> TO PERFORM THE OPERATIONS BELOW" << endl;
    //   User related actions
    cout << "0> Login To User Account" << endl;
    cout << "1> Create User Account" << endl;
    cout << "2> Update User Account" << endl;
    cout << "3> Delete User Account" << endl;
    cout << "4> Get User Details" << endl;

    //    Password related actions
    cout << "5> Create Web password" << endl;
    cout << "6> Create Desktop password" << endl;
    cout << "7> Create Game password" << endl;
    cout << "8> Get User Password" << endl;
    cout << "9> Get All User Password" << endl;
    cout << "10> Search User password" << endl;
    cout << "11> Delete Password By NAME" << endl;
    cout << "12> Update Password By NAME" << endl;
}

void Terminal::start() {
    cout << "WELCOME TO THE TERMINAL PASSWORD MANAGER" << endl;

    while (true) {
        print_options();

        int typ;
        cin >> typ;

        switch (typ) {
            case 0: {
                string username, password;

                cout << USERNAME;
                cin >> username;

                cout << PASSWORD;
                cin >> password;

                string result = this->application.login(username, password);
                cout << result << endl;
                break;
            }

            case 1: {
                string token, user_id;

                cout << TOKEN;
                cin >> token;

                cout << USER_ID;
                cin >> user_id;

                string* user_id_ptr = user_id.empty() ? nullptr : &user_id;

                string result = application.delete_user(token, user_id_ptr);
                cout << result << endl;

                delete user_id_ptr;
                break;
            }

            case 2: {
                string username, password, token;

                cout << USERNAME;
                cin >> username;

                cout << PASSWORD;
                cin >> password;

                cout << TOKEN;
                cin >> token;

                string result = application.create_user_account(&token, username, password, !token.empty());
                break;
            }

            case 3: {
                string user_id, token;

                cout << TOKEN;
                cin >> token;

                cout << USER_ID;
                cin >> user_id;

                string* user_id_prt = user_id.empty() ? nullptr : &user_id;

                string result = application.get_user(token, user_id_prt);
                cout << result << endl;

                delete user_id_prt;
                break;
            }

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

                string* user_id_ptr = user_id.empty() ? nullptr : &user_id;
                string* password_ptr = password.empty() ? nullptr : &password;
                string* username_ptr = username.empty() ? nullptr : &username;

                string result = application.update_user(token, username_ptr, user_id_ptr, password_ptr);
                cout << result << endl;

                delete user_id_ptr;
                delete password_ptr;
                delete username_ptr;

                break;
            }

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
                cin >> type;

                cout << URL;
                cin >> URL_;

                cout << DEVELOPER;
                cin >> developer;

                cout << NAME;
                cin >> name;

                string* URL_ptr = URL_.empty() ? nullptr : &URL_;
                string* developer_ptr = developer.empty() ? nullptr : &developer;
                string* user_id_ptr = user_id.empty() ? nullptr : &user_id;

                string result = this->application.create_password(token, type, URL_ptr, username, password, name, developer_ptr, user_id_ptr);

                cout << result << endl;

                delete URL_ptr;
                delete developer_ptr;
                delete user_id_ptr;

                break;
            }

            case 6: {
                string user_id, token, username, password, type, URL_, developer, name, id;

                cout << TOKEN;
                cin >> token;

                cout << USER_ID;
                cin >> user_id;

                cout << USERNAME;
                cin >> username;

                cout << PASSWORD;
                cin >> password;

                cout << TYPE;
                cin >> type;

                cout << URL;
                cin >> URL_;

                cout << DEVELOPER;
                cin >> developer;

                cout << NAME;
                cin >> name;

                cout << ID;
                cin >> id;

                string* URL_ptr = URL_.empty() ? nullptr : &URL_;
                string* developer_ptr = developer.empty() ? nullptr : &developer;
                string* name_ptr = name.empty() ? nullptr : &name;
                string* username_ptr = username.empty() ? nullptr : &username;
                string* password_ptr = password.empty() ? nullptr : &password;
                string* user_id_ptr = user_id.empty() ? nullptr : &user_id;

                string result = this->application.update_password(token, type, user_id_ptr, id, URL_ptr, username_ptr, password_ptr, name_ptr, developer_ptr);
                cout << result << endl;

                delete URL_ptr;
                delete developer_ptr;
                delete name_ptr;
                delete username_ptr;
                delete password_ptr;
                delete user_id_ptr;

                break;
            }

            case 7: {
                string token, password_id;

                cout << TOKEN;
                cin >> token;

                cout << PASSWORD_ID;
                cin >> password_id;

                string result = application.delete_password(token, password_id);
                cout << result << endl;
                break;
            }

            case 8: {
                string token, user_id;

                cout << TOKEN;
                cin >> token;

                cout << USER_ID;
                cin >> user_id;

                string result = application.get_user_passwords(token, user_id);
                cout << result << endl;
                break;
            }

            case 9: {
                string token, password_id;

                cout << TOKEN;
                cin >> token;

                cout << PASSWORD_ID;
                cin >> password_id;

                string result = application.get_password(token, password_id);
                cout << result << endl;
                break;
            }

            case 10: {
                string token, text;

                cout << TOKEN;
                cin >> token;

                cout << TEXT;
                cin >> text;

                string result = application.search_password(token, text);
                cout << result << endl;
                break;
            }

            default: {
                cout << "TERMINATING APPLICATION" << endl;
                return;
            }
        }

        cout << "__________________________________________________________________________________________" << endl;
    }
}
