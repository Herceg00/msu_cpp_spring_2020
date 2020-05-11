#ifndef MSU_CPP_SPRING_2020_CALLBACK_H
#define MSU_CPP_SPRING_2020_CALLBACK_H

#include <functional>

using OnBeginEnd = std::function<void()>;
using OnNumber = std::function<void(int)>;
using OnWord = std::function<void(const char *)>;

void register_on_begin_callback(OnBeginEnd callback);

void register_on_end_callback(OnBeginEnd callback);

void register_on_number_callback(OnNumber callback);

void register_on_word_callback(OnWord callback);

void parse_line(const char *);

#endif //MSU_CPP_SPRING_2020_CALLBACK_H
