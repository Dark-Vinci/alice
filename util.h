//
// Created by Ademola Olutomiwa Abraham on 07/11/2024.
//
#include <string>
#include <vector>

using namespace std;

#ifndef PASSWORDMANAGER_UTIL_H
#define PASSWORDMANAGER_UTIL_H

namespace Utils {
    vector<string> split(const string& str, char delimiter);
    time_t stringToTimeT(const string& timeStr);
    vector<string> splitl (const string& s, char delim);

    class Crypto {
    private:
        string encoding_key;
        string hash_key;
        unordered_map<char, string> morse_map = {
                {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."},
                {'F', "..-."}, {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"},
                {'K', "-.-"}, {'L', ".-.."}, {'M', "--"}, {'N', "-."}, {'O', "---"},
                {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
                {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"}, {'Y', "-.--"},
                {'Z', "--.."},{'0', "-----"}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"},
                {'4', "....-"}, {'5', "....."}, {'6', "-...."}, {'7', "--..."},
                {'8', "---.."}, {'9', "----."},{' ', "/"}
        };

        unordered_map<string, char> inverse_morse;

        string rot13(const string& str);
    public:
        string encode(const string& password);
        string decode(const string& encoded_string);
        string generate_random_password(int length);
        string hash(const string& password);
        string generate_id();

        Crypto() {
            for (const auto& pair : this->morse_map) {
                inverse_morse[pair.second] = pair.first;
            }
        }
    };
}

#endif //PASSWORDMANAGER_UTIL_H
