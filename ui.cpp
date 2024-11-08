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
            case 1: {
                auto a = application.delete_user();
                cout << a << endl;
                break;
            }

            case 2: {
                string result = application.create_user_account();
                break;
            }

            case 3: {
                string result = application.get_user();
                cout << result << endl;
                break;
            }

            case 4: {
                string result = application.update_password();
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

            default: {
                cout << "TERMINATING APPLICATION" << endl;
                return;
            }
        }
    }
}
