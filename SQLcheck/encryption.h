#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>

using namespace std;
string encryptor(string msg,string key) {

    string encrypt = "";

    int keyItr = 0;

    stringstream res;

    for (int i = 0; i < msg.length(); i++) {

        int temp = msg[i] ^ key[keyItr];

        res << hex << setfill('0') << std::setw(2) << (int)temp;

        keyItr++;

        if (keyItr >= key.length()) {

            keyItr = 0;
        }
    }

    res >> encrypt;

    return encrypt;
}
