#include "Keys.h"
//

#include <string.h>
//

#include <string>

char* Keys::getCmd() {
    return keys[0];
}

void Keys::clearKeys() {
    for (int i = 0; i < currentIndex; ++i) {
        delete[] keys[i];
    }
    currentIndex = 0;
    for (int i = 0; i < 20; ++i) {
        keys[i] = NULL;
    }
}

bool Keys::addKey(const std::string &s) {
    keys[currentIndex] = new char[s.size() + 1];
    strcpy(keys[currentIndex++], s.c_str());
    return currentIndex == KEYS_AMOUNT;
}

Keys::Keys() : currentIndex(0) { 
    for (int i = 0; i < 20; ++i) {
        keys[i] = NULL;
    }
}

Keys::~Keys() {
    for (int i = 0; i < currentIndex; ++i) {
        delete[] keys[i];
    }
}