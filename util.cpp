//
// Created by Ademola Olutomiwa Abraham on 07/11/2024.
//

#include <string>
#include <random>
#include <algorithm>
#include <sstream>
#include <vector>
#include "util.h"

using namespace std;

vector<string> Utils::split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

time_t Utils::stringToTimeT(const string& timeStr) {
    return static_cast<time_t>(stoll(timeStr));
}

vector<string> Utils::splitl(const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

string Utils::Crypto::decode(const string& encoded_string) {
    return this->rot13(encoded_string);
}

string  Utils::Crypto::rot13(const string& str) {
    string rot13_string;

    for (const char c: str) {
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
    return this->rot13(password);
}

string Utils::Crypto::hash(const string& password) {
    return this->encode(password);
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