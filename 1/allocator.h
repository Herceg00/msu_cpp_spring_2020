#pragma once

#include <iostream>

class Allocator {
    char *pointer;
    size_t size;
    size_t offset;
public:

    explicit Allocator(size_t _size) : pointer(nullptr), size(0), offset(0) {
        pointer = (char *) malloc(_size);
        if (pointer != nullptr) {
            size = _size;
        }

    }

    char *alloc(size_t _size) {
        if (offset + _size <= size) {
            char *temp_pointer = pointer + offset;
            offset += _size;
            return temp_pointer;
        }
        return nullptr;

    }

    void reset(void) {
        offset = 0;
    }

    ~Allocator() {
        free(pointer);
    }
};
