#include <iostream>
#include "callback.h"

void OnNumberFound(int num) {
    std::cout << "User defined callback for number " << num << std::endl;
}

void OnWordFound(const char *word) {
    std::cout << "User defined callback for word " << word << std::endl;
}

void OnBeginFunc() {
    std::cout << "User defined callback for begin " << std::endl;
}

void OnEndFunc() {
    std::cout << "User defined callback for end" << std::endl;
}

int main() {

    char line1[] = "+100500 technosphere 9000";
    parse_line(line1);

    register_on_begin_callback(OnBeginFunc);
    register_on_end_callback(OnEndFunc);
    register_on_number_callback(OnNumberFound);
    register_on_word_callback(OnWordFound);

    char line2[] = "+100500 technosphere 9000";
    parse_line(line2);

    return 0;
}