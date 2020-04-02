#ifndef INC_4_DESERIALIZER_H
#define INC_4_DESERIALIZER_H
#pragma once 

#include <iostream>
#include <fstream>
#include <istream>
#include <istream>



class Deserializer {
    static constexpr char Separator = ' ';
public:
    explicit Deserializer(std::istream &in)
            : in_(in) {
    }

    template<class T>
    Error load(T &object) {
        return object.serialize(*this);
    }

    template<class... ArgsT>
    Error operator()(ArgsT... args) {
        return process(args...);
    }

private:
    std::istream &in_;
    template<class T, class... Args>
    Error process(T elem, Args... args) {
        Error error = process(elem);
        if (error == Error::NoError) {
            return process(args...);
        } else {
            return error;
        }
    }

    Error process(bool &value) {
        std::string text;
        in_ >> text;
        if (text == "true") {
            value = true;
        } else if (text == "false"){
            value = false;
        } else{
            return Error ::CorruptedArchive;
        }
        return Error::NoError;
    }

    Error process(uint64_t &value) {
        std::string text;
        in_ >> text;
        int64_t num = std::stoi(text);
        return Error::NoError;
    }

    template<class T>
    Error process(T &value) {
        return Error::CorruptedArchive;
    }
};

#endif //INC_4_DESERIALIZER_H
