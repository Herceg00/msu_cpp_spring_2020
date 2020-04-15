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
        for (int i = 0; i < data.size(); i++) {
            if (data[i] == '{') {
                int num = 0;
                i++;
                do {
                    if (i == data.size()){
                        throw std::runtime_error("wrong format");
                    }
                    if ((!isdigit(data[i]))) {
                        throw std::runtime_error("wrong format");
                    }
                    num = 10 * num + data[i] - '0';
                    i++;
                } while (data[i] != '}');

                if (num >= num_of_args) {
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

std::string format(const char *str)
{
    String_Handler formatter(str);
    return formatter.process();
}

int main(){
    auto text = format("{0}+{1} = {0}", 2, "one");
    assert(text == "2+one = 2");
    auto text1 = format("privet!!");
    assert(text1 == "privet!!");


    try{
        auto text2 = format("{0}+{2} = {0}", 2, "one");
    }
    catch (std::runtime_error& error){
        std::string reason = error.what();
        assert(reason == "out of range");
    }
    try{
        auto text2 = format("{0}+{2} = {0}");
    }
    catch (std::runtime_error& error){
        std::string reason = error.what();
        assert(reason == "out of range");
    }
    try{
        auto text2 = format("{0}+{} = {0}", 2, "one");
    }
    catch (std::runtime_error& error){
        std::string reason = error.what();
        assert(reason == "wrong format");
    }
    try{
        auto text2 = format("{0}+{0} = {0}{", 2, "one");
    }
    catch (std::runtime_error& error){
        std::string reason = error.what();
        assert(reason == "wrong format");
    }
    try{
        auto text2 = format("{0}+{0} = {0}}", 2, "one");
    }
    catch (std::runtime_error& error){
        std::string reason = error.what();
        assert(reason == "wrong format");
    }
}