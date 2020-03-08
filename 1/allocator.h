#pragma once
#include <iostream>

class Allocator{
    char* pointer;
    size_t size;
    size_t offset;
public:
    explicit Allocator(size_t _size):pointer(nullptr),size(0),offset(0) {
        if(_size > 0) {
            pointer = (char*)malloc(_size);
            if (pointer != nullptr) {
                size = _size;
            }
        }
    }
    char* alloc(size_t _size) {
        if ((int)_size <= 0) {
            printf("0 bytes allocated\n");
            return pointer;
        } else {
            if (offset + _size <= size) {
                char *temp_pointer = pointer + offset;
                offset += _size;
                printf("Allocated %d bytes, total alloc usage is %d bytes\n", (int) _size, (int) offset);
                return temp_pointer;
            }
            printf("Too much memory required, only %d bytes is available\n", (int) size - (int) offset);
            return nullptr;
        }
    }
    void reset(void){
        offset  = 0;
        printf("Reset completed, %d bytes is available\n", (int)(size-offset));
    }

    ~Allocator(){
        free(pointer);
    }
};
