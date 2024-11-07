//
// Created by Ademola Olutomiwa Abraham on 07/11/2024.
//

#include "ui.h"

void Terminal::start() {
    cout << "WELCOME TO THE TERMINAL PASSWORD MANAGER" << endl;

    while (true) {
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

            default: {
                cout << "TERMINATING APPLICATION" << endl;
                return;
            }
        }
    }
}
