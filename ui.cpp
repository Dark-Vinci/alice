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

                cin >> username;
                cin >> password;

                string result = this->application.login(username, password);
                cout << result << endl;
                break;
            }

            case 1: {
                string token, user_id;

                cin >> token;
                cin >> user_id;

                string result = application.delete_user(token, &user_id);
                cout << result << endl;
                break;
            }

            case 2: {
                string username, password, token;

                cin >> username;
                cin >> password;
                cin >> token;

                string result = application.create_user_account(&token, username, password, !token.empty());
                break;
            }

            case 3: {
                string user_id, token;

                cin >> token;
                cin >> user_id;

                string result = application.get_user(token, &user_id);
                cout << result << endl;
                break;
            }

            case 4: {
                string user_id, token, username, password;

                cin >> token;
                cin >> user_id;
                cin >> username;
                cin >> password;

                string result = application.update_user(token, &user_id, &username, &password);
                cout << result << endl;
                break;
            }

            case 5: {
                string result = application.get_user_passwords();
                cout << result << endl;
                break;
            }

            case 6: {
                string result = application.delete_user();
                cout << result << endl;
                break;
            }

            case 7: {
                string result = application.create_password();
                cout << result << endl;
                break;
            }

            case 8: {
                string result = application.update_user();
                cout << result << endl;
                break;
            }

            case 9: {
                string result = application.delete_password();
                cout << result << endl;
                break;
            }

            case 10: {
                string result = application.get_password();
                cout << result << endl;
                break;
            }

            case 11: {
                string result = application.delete_password();
                cout << result << endl;
                break;
            }

            case 12: {
                string result = application.update_password();
                cout << result << endl;
                break;
            }

            default: {
                cout << "TERMINATING APPLICATION" << endl;
                return;
            }
        }

        cout << "___________________________________________________________________________" << endl;
    }
}
