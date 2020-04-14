#include <iostream>
#include "string"
#include "vector"

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
        for (int i = 0; i < data.size(); i++) {
            if(data[i] == '{'){
                int num = 0;
                i++;
                do {

                    if((!isdigit(data[i]))) {
                        throw std::runtime_error("wrong format");
                    }
                    num = 10*num + data[i];
                    i++;
                }while(data[i]!='}');
                if(num > num_of_args){
                    throw std::runtime_error("out of range");
                } else{
                    formatted+=args_array[];
                }

            }


        }

    }


};