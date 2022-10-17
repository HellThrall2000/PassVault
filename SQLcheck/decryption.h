#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>

using namespace std;

string decryptor(string msg,string key) {

    string hexToUni = "";

    for (int i = 0; i < msg.length() - 1; i += 2) {

        string output = msg.substr(i, 2);

        int decimal = strtol(output.c_str(), NULL, 16);

        hexToUni += (char)decimal;

    }

    string decrypText = "";

    int keyItr = 0;

    for (int i = 0; i < hexToUni.length(); i++) {

        int temp = hexToUni[i] ^ key[keyItr];

        decrypText += (char)temp;

        keyItr++;

        if (keyItr >= key.length()) {

            keyItr = 0;
        }
    }

    return decrypText;
}