#include "string"
#include "iostream"
#include "format_handler.hpp"


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