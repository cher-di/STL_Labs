#include <iostream>
#include <string>
#include <map>


bool char_in_string(char ch, const std::string &string) {
    return string.find(ch) != std::string::npos;
}


int FSM(char ch, int &state) {
    const static std::string UPPER_ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const static std::string LOWER_ALPHABET = "abcdefghijklmnopqrstuvwxyz";
    const static std::string ALPHABET = UPPER_ALPHABET + LOWER_ALPHABET;
    const static std::string NUMBERS = "0123456789";

    switch (state) {
        case 0:
            if (char_in_string(ch, ALPHABET)) {
                state = 1;
                return false;
            } else {
                state = -1;
                return true;
            }
        case 1:
            if (char_in_string(ch, ALPHABET) || char_in_string(ch, NUMBERS))
                return false;
            else if (ch == '=') {
                state = 2;
                return false;
            } else {
                state = -1;
                return true;
            }
        case 2:
            if (char_in_string(ch, ALPHABET)) {
                state = 3;
                return false;
            } else {
                state = -1;
                return true;
            }
        case 3:
            if (char_in_string(ch, ALPHABET) || char_in_string(ch, NUMBERS))
                return false;
            else if (ch == '=' || ch == '>') {
                state = 4;
                return false;
            } else if (ch == '<') {
                state = 6;
                return false;
            } else if (ch == '\n') {
                state = 0;
                return true;
            } else {
                state = -1;
                return true;
            }
        case 4:
            if (char_in_string(ch, ALPHABET)) {
                state = 5;
                return false;
            } else {
                state = -1;
                return true;
            }
        case 5:
            if (char_in_string(ch, ALPHABET) || char_in_string(ch, NUMBERS))
                return false;
            else if (ch == '\n') {
                state = 0;
                return true;
            } else {
                state = -1;
                return true;
            }
        case 6:
            if (ch == '>') {
                state = 4;
                return false;
            } else if (char_in_string(ch, ALPHABET)) {
                state = 5;
                return false;
            } else {
                state = -1;
                return true;
            }
        default:
            return false;
    }
}

bool is_valid(const std::string &string) {
    int state = 0;
    bool status = false;
    for (auto letter: string) {
        status = FSM(letter, state);
        if (state == -1)
            break;
    }

    return status && state == 0;
}

int main() {
    std::map<std::string, bool> tests = {
            {"var1=true\nvari5a6ble=var1>var2\n", true},
            {"VAR1=VAR2\nFDHDdwsghbwig", false},
            {"test=false\n", true},
            {"a=b=c\nvar1=var2\nvar3=var4<>var5\n", true}
            };

    int i = 1;
    std::string status;
    for (const auto& test_case: tests) {
        if (is_valid(test_case.first) == test_case.second)
            status = "OK";
        else
            status = "FAIL";
        std::cout << "Test#" << i << " " << status << std::endl;
        i++;
    }

    return 0;
}
