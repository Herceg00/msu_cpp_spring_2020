#include <cstdlib>
#include <utility>
#include "callback.h"

OnBeginEnd BeginFunc = []() { printf("No begin callback\n"); };
OnBeginEnd EndFunc = []() { printf("No end callback\n"); };
OnWord WordFunc = [](const char *) { printf("No word callback\n"); };
OnNumber NumberFunc = [](int) { printf("No number callback\n"); };

void register_on_end_callback(OnBeginEnd callback) {
    EndFunc = std::move(callback);
}

void register_on_begin_callback(OnBeginEnd callback) {
    BeginFunc = std::move(callback);
}

void register_on_number_callback(OnNumber callback) {
    NumberFunc = std::move(callback);
}

void register_on_word_callback(OnWord callback) {
    WordFunc = std::move(callback);
}

void parse_line(const char *line) {

    BeginFunc();

    using namespace std;
    bool number = true;
    string token;
    token.clear();

    do {
        if (!isspace(*line)) {
            if (!isdigit(*line)) {
                number = false;
            }
            token += *line;
        } else {
            number ? NumberFunc(atoi(token.c_str())) : WordFunc(token.c_str());
            number = true;
            token.clear();
        }
    } while (*++line != '\0');
    number ? NumberFunc(atoi(token.c_str())) : WordFunc(token.c_str()); //after end of line it is necessary
    EndFunc();
}