//
// Created by Ademola Olutomiwa Abraham on 07/11/2024.
//
#include <string>

using namespace std;

#ifndef PASSWORDMANAGER_UTIL_H
#define PASSWORDMANAGER_UTIL_H

namespace Utils {
    class Crypto {
    private:
        string encoding_key;
        string hash_key;
    public:
        string encode(string password);
        string decode(string encoded_string);
        string generate_random_password();
        string hash(string password);
    };
}

#endif //PASSWORDMANAGER_UTIL_H
