#include <iostream>
#include "string"
#include "vector"
#include "assert.h"
#include "sstream"

class String_Handler {

    int num_of_args = 0;
    std::string data;
    std::vector<std::string> args_array;

public:
    explicit String_Handler(const char *_data) {
        data = _data;
    }

    template<typename T>
    void get_args(T &&arg) {
        num_of_args++;
        std::stringstream temp;
        temp<<arg;
        args_array.push_back(temp.str());
    }

    template<typename T, typename... Args>
    void get_args(T &&arg, Args &&...args) {
        num_of_args++;
        std::stringstream temp;
        temp<<arg;
        args_array.push_back(temp.str());
        get_args(std::forward<Args>(args)...);
    }

    std::string process() {
        std::string formatted;
        int num_counter = 0;
        std::cout<<"DATA:"<<data<<std::endl;
        std::cout<<"NUM OF ARGS:"<<num_of_args<<std::endl;

        for (int j = 0; j <num_of_args ; ++j) {
            std::cout<<args_array[j]<<std::endl;
        }

        for (int i = 0; i < data.size(); i++) {
            std::cout<<i<<"-th symbol is "<<data[i]<<std::endl;
            if (data[i] == '{') {
                std::cout<<i<<"-th symbol is "<<data[i]<<std::endl;
                int num = 0;
                i++;
                do {
                    if ((!isdigit(data[i]))) {
                        throw std::runtime_error("wrong format");
                    }
                    num = 10 * num + data[i] - '0';
                    std::cout<<i<<"-th symbol is "<<data[i]<<std::endl;
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
    String_Handler formatter(str);
    formatter.get_args(std::forward<Args>(args)...);
    return formatter.process();
}

int main(void){
    auto text = format("{1}+{1} = {0}", 2, "one");
    assert(text == "one+one = 2");
}