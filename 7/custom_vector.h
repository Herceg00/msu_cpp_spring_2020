#ifndef INC_6_CUSTOM_VECTOR_H
#define INC_6_CUSTOM_VECTOR_H

#include "iostream"
#include "type_traits"
#include <limits>

template<class T>
class Custom_Allocator {
    using value_type = T;
    using pointer = T *;
    using size_type = std::size_t;
    using const_reference = const T &;
public:

    constexpr pointer allocate(size_type size) {
        if (size) {
            return (pointer) malloc(size * sizeof(value_type));
        } else {
            return nullptr;
        }
    }

    constexpr void deallocate(pointer p, size_type size) {
        if (size) free(p);
    }

    size_type max_size() const noexcept {
        return std::numeric_limits<size_type>::max() / sizeof(value_type);
    }

    void construct(pointer p, const_reference val) {
        new((void *) p) value_type(val);
    }

    void destroy(pointer p, size_type size) {
        for(size_type i = 0;i < size;i++) {
            ((pointer) (p + i))->~value_type();
        }
    }
};


template<class T>
class Custom_Iterator {
    using value_type = T;
    using pointer = T *;
    using reference = T &;
    pointer ptr;
public:

    explicit Custom_Iterator(pointer ptr) : ptr(ptr) {};

    Custom_Iterator &operator++() {
        ptr++;
        return *this;
    }

    Custom_Iterator &operator--() {
        ptr--;
        return *this;
    }

    Custom_Iterator operator+(size_t value) const {
        return Custom_Iterator<value_type>(ptr + value);
    }

    Custom_Iterator operator-(size_t value) const {
        return Custom_Iterator<value_type>(ptr - value);
    }

    bool operator==(const Custom_Iterator<value_type> &other) {
        return ptr == other.ptr;
    }

    bool operator!=(const Custom_Iterator<value_type> &other) {
        return ptr != other.ptr;
    }

    reference operator*() const {
        return *ptr;
    }
};


template<class T, class Allocator = Custom_Allocator<T>>
class Custom_Vector {
    using value_type = T;
    using pointer = T *;
    using size_type = std::size_t;
    using const_reference = const T &;
    using reference = T &;
    using iterator = Custom_Iterator<value_type>;
    Allocator allocator;
    pointer data;
    size_type capacity; //Количество аллоцированных элементов на данный момент
    size_type size; //количество фактических элементов в контейнере
public:
    Custom_Vector() : capacity(0), data(allocator.allocate(0)), size(0) {};
    ~Custom_Vector() {
        allocator.destroy(data, capacity);
        allocator.deallocate(data,capacity);
    };

    void clear() {
        allocator.deallocate(data, size);
        size = 0;
        capacity = 0;
    }

    reference operator[](size_type position) {
        if (position > size) {
            throw std::out_of_range("out of bound");
        }
        return data[position];
    }

    void reserve(size_type new_size) {
        if (new_size > capacity) {
            pointer new_data = allocator.allocate(new_size);
            for (size_t i = 0; i < size; ++i) {
                allocator.construct(new_data + i, data[i]);
            }
            data = new_data;
            capacity = new_size;
        }
    }

    size_type get_size(){
        return size;
    }

    void resize(size_t new_size) {
        if (new_size < this->size) {
            allocator.destruct(data + new_size, this->size - new_size);
            this->size = new_size;
            return;
        }
        if (new_size > this->size) {
            if (new_size > capacity)
                reserve(new_size);
            for (size_type i = this->size; i < new_size; ++i)
                allocator.construct(data + i, (value_type) 0);
            this->size = new_size;
        }
    }
    //Стратегия - увеличение capacity в два раза
    void push_back(const_reference value){
        if (capacity == size) {
            reserve((capacity+1)*2);
        }
        allocator.construct(data + size, value);
        capacity*=2;
        size++;
    }

    void pop_back(){
        if(size){
            allocator.destroy(data + size - 1, 1);
            size--;
        }
    }

    iterator begin() {
        return Custom_Iterator<value_type>(data);
    }

    iterator end() {
        return Custom_Iterator<value_type>(data + size);
    }

    iterator rbegin(){
        return Custom_Iterator<value_type>(data + size - 1, true);
    }

    iterator rend() {
        return Custom_Iterator<value_type>(data - 1, true);
    }

    bool empty(){
        return size == 0;
    }
};


#endif //INC_6_CUSTOM_VECTOR_H
