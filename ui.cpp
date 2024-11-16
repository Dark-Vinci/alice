//
// Created by Ademola Olutomiwa Abraham on 07/11/2024.
//
#include "ui.h"

void Terminal::print_options() {
    cout << "INPUT NUMBER <0 - 10> TO PERFORM THE OPERATIONS BELOW" << endl;
    cout << "USE an hyphen \"-\" for values that are empty" << endl;

    //   User related actions
    cout << "0> Login To Account" << endl;
    cout << "1> Delete User/Self Account" << endl;
    cout << "2> Create User Account" << endl;
    cout << "3> Get User Details" << endl;
    cout << "4> Update User Details" << endl;
    cout << "5> Create Password" << endl;
    cout << "6> Update User Password" << endl;
    cout << "7> Delete User password" << endl;
    cout << "8> Get All User Password" << endl;
    cout << "9> Get User Password by ID" << endl;
    cout << "10> Search User passwords" << endl;
}

void Terminal::start() {
    cout << "WELCOME TO THE TERMINAL PASSWORD MANAGER" << endl;

    // Application loop: this stops the application to be used for multiple actions without needing to restart the application;
    while (true) {
        print_options();

        int typ;
        cout << "_______________________________________________________________PASSWORD MANAGER_________________________________________________________________" << endl;
        cout << "Choose between 0 - 10: ";
        cin >> typ;

        // if the input is not an int; end the loop and exit the application
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "******************INVALID INPUT; SHUTTING DOWN APPLICATION*******************" << endl;
            break;
        }

        switch (typ) {
            // To login to user account, kindly use the right username and password used in the creation of the user account
            case 0: {
                string username, password;

                cout << USERNAME;
                cin >> username;

                cout << PASSWORD;
                cin >> password;

                string result = this->application.login(username, password);
                cout << "RESULT: \n" + result << endl;
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
                cout << "RESULT: \n" + result << endl;

                break;
            }

            //  Create a User account
            // If an admin is creating the account for the user, he/she must provide a login token
            // provide your name, password and *token(if admin)
            case 2: {
                string username, password, token, is_admin;

                cout << USERNAME;
                cin >> username;

                cout << PASSWORD;
                cin >> password;

                cout << TOKEN;
                cin >> token;

                cout << "0 for not admin and any other number for an admin" << endl;
                cout << IS_ADMIN;
                cin >> is_admin;

                string* token_ptr = token=="-" ? nullptr : &token;

                string result = this->application.create_user_account(token_ptr, username, password, is_admin != "0");

                cout << "RESULT: \n" + result << endl;
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
                cout << "RESULT: \n" + result << endl;

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
                cout << "RESULT: \n" + result << endl;

                break;
            }

            // To create a new password(WEB, DESKTOP, GAME)
            // If an admin is creating the password for the user, the user_id must be added, else the password will be created for the user of the token
            // username is a must provided
            // password must be provided
            // for WEB: URL must be provided
            // For GAME: Developer name must be provided
            // name of the password must also be provided
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

                cout << "RESULT: \n" + result << endl;

                break;
            }

            case 6: {
                string user_id, token, username, password, type, URL_, developer, name, id;

                cout << TYPE;
                cout << "WEB or DESKTOP or GAME" << endl;
                cin >> type;

                if (type == "WEB") {
                    cout << URL;
                    cin >> URL_;
                }

                if (type == "GAME") {
                    cout << DEVELOPER;
                    cin >> developer;
                }

                cout << TOKEN;
                cin >> token;

                cout << USER_ID;
                cin >> user_id;

                cout << USERNAME;
                cin >> username;

                cout << PASSWORD;
                cin >> password;

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
                cout << "RESULT: \n" + result << endl;

                break;
            }

            // To delete a user password(admin, user)
            // provide the login token
            // provide the password id which cannot be empty
            case 7: {
                string token, password_id;

                cout << TOKEN;
                cin >> token;

                cout << PASSWORD_ID;
                cin >> password_id;

                string result = this->application.delete_password(token, password_id);
                cout << "RESULT: \n" + result << endl;
                break;
            }

            // Get list of all user password(admin, user)
            // provide the login token
            // provide the user id an admin checking for a user, else use "-"
            case 8: {
                string token, user_id;

                cout << TOKEN;
                cin >> token;

                cout << USER_ID;
                cin >> user_id;

                string* user_id_ptr = user_id == "-" ? nullptr : &user_id;

                string result = this->application.get_user_passwords(token, user_id_ptr);
                cout << "RESULT: \n" + result << endl;
                break;
            }

            // To get a password by id (user, admin)
            // provide the login token
            // provide the password ID
            case 9: {
                string token, password_id;

                cout << TOKEN;
                cin >> token;

                cout << PASSWORD_ID;
                cin >> password_id;

                string result = this->application.get_password(token, password_id);
                cout << "RESULT: \n" + result << endl;
                break;
            }

            // To search a list of user password
            // provide the user token
            // provide the "substring" to be searched
            case 10: {
                string token, text;

                cout << TOKEN;
                cin >> token;

                cout << TEXT;
                cin >> text;

                string result = this->application.search_password(token, text);
                cout << "RESULT: \n" + result << endl;
                break;
            }

            default: {
                cout << "TERMINATING APPLICATION" << endl;
                return;
            }
        }

        cout << "_______________________________________________________________PASSWORD MANAGER_________________________________________________________________" << endl;
    }
}
