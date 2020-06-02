#ifndef INC_4_SERIALIZER_H
#define INC_4_SERIALIZER_H
#pragma once

#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>


enum class Error {
    NoError,
    CorruptedArchive
};

class Serializer {
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream &out)
            : out_(out) {
    }

    template<class T>
    Error save(T &object) {
        return object.serialize(*this);
    }

    template<class... ArgsT>
    Error operator()(ArgsT... args) {
        return process(args...);
    }

private:
    std::ostream &out_;
    template<class T, class... Args>
    Error process(T elem, Args... args) {
        Error error = process(elem);
        if (error == Error::NoError) {
            out_ << Separator;
            return process(args...);
        } else {
            return error;
        }
    }

    Error process(bool &value) {
        if (value) {
            out_ << "true";
        } else {
            out_ << "false";
        }
        return Error::NoError;
    }

    Error process(uint64_t &value) {
        out_ << value;
        return Error::NoError;
    }

    template<class T>
    Error process(T &value) {
        return Error::CorruptedArchive;
    }
};


#endif //INC_4_SERIALIZER_H
