#include <iostream>
#include "string"
#include "vector"
#include "assert.h"

class String_Handler {
    int num_of_args = 0;
    std::string data;
    std::vector<std::string> args_array;

public:
    String_Handler(const char *_data) {
        data = _data;
    }

    template<typename T, typename... Args>
    void get_args(T &&arg, Args &&...args) {
        if (sizeof...(args) > num_of_args) {
            num_of_args = sizeof...(args);
        }
        args_array.push_back(arg);
        get_args(std::forward<Args>(args)...);
    }

    std::string process() {
        std::string formatted;
        int num_counter = 0;
        std::cout<<data<<std::endl;
        std::cout<<num_of_args<<std::endl;
        for (int i = 0; i < data.size(); i++) {
            if (data[i] == '{') {
                int num = 0;
                i++;
                do {
                    if ((!isdigit(data[i]))) {
                        throw std::runtime_error("wrong format");
                    }
                    num = 10 * num + data[i];
                    std::cout<<num<<std::endl;
                    i++;
                } while (data[i] != '}');
                if (num > num_of_args) {
                    //std::cout<<num<<std::endl;
                    throw std::runtime_error("out of range");
                } else {
                    formatted += args_array[num];
                }

            } else if (data[i] == '}') {
                throw std::runtime_error("wrong format");
            }else{
                formatted+=data[i];
            }
        }
        return formatted;
    }
};
template <typename ...Args>
std::string format(const char *str,Args&&...args)
{
    String_Handler f(str);
    f.get_args(std::forward<Args>(args)...);
    return f.process();
}

int main(void){
    auto text = format("{1}+{1} = {0}", 2, "one");
    assert(text == "one+one = 2");
}