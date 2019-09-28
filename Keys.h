#include <string>

#define KEYS_AMOUNT 20
#define KEYS_SIZE 20

struct Keys {
    ~Keys();
    Keys();
    char* keys[KEYS_AMOUNT];
// Index of the first "empty element" in array.
    unsigned short currentIndex;

    void clearKeys();
// Returns c-string of the command.
    char* getCmd();
// Returns if there is space left for a key.
    bool addKey(const std::string &);
};