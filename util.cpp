//
// Created by Ademola Olutomiwa Abraham on 07/11/2024.
//

#include <string>
#include <random>
#include <algorithm>
#include <sstream>
#include "util.h"

using namespace std;

string Utils::Crypto::decode(const string& encoded_string) {
    // ENCODED STRING -> DECODE MORSE CODE -> INVERSE ROT13 -> RESULT
    stringstream decoded_morse;
    stringstream morse_stream(encoded_string);
    string morse_char;

    while (morse_stream >> morse_char) {
        if (inverse_morse.find(morse_char) != inverse_morse.end()) {
            decoded_morse << inverse_morse[morse_char];
        } else if (morse_char == "/") {
            decoded_morse << ' ';
        }
    }

    auto decoded_morse_string = decoded_morse.str();

    return this->rot13(decoded_morse_string);
}

string  Utils::Crypto::rot13(const string& str) {
    string rot13_string;

    for (char c: str) {
        if (c >= 'A' && c <= 'Z') {
            rot13_string += (c - 'A' + 13) % 26 + 'A';
        } else if (c >= 'a' && c <= 'z') {
            rot13_string += (c - 'a' + 13) % 26 + 'a';
        } else {
            rot13_string += c;
        }
    }

    return rot13_string;
}

string Utils::Crypto::encode(const string& password) {
    //STRING -> ROT13 -> MORSE CODE -> RESULT
    string rot13 = this->rot13(password);

    stringstream morse_string;

    for(char c: rot13) {
        c = toupper(c);

        if (morse_map.find(c) != morse_map.end()) {
            morse_string << morse_map[c] << " ";
        }
    }

    return morse_string.str();
}

string Utils::Crypto::hash(const string& password) {
    return "*******HASHED*******";
}

string Utils::Crypto::generate_random_password(int length) {
    const char from_pool[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string generated_password;

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, sizeof(from_pool) - 2);

    for (int i = 0; i < length; ++i) {
        generated_password += from_pool[distribution(generator)];
    }

    return generated_password;
}

string Utils::Crypto::generate_id() {
    return generate_random_password(9);
}