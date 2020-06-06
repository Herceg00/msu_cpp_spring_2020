#ifndef INC_9_SORTING_H
#define INC_9_SORTING_H

#include <fstream>
#include <ostream>
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>


struct comparator {
    bool operator()(uint64_t i, uint64_t j) { return (i < j); }
} comp_object;

//for each thread
#define MEM_BOUND 4*1024*1024

void merge(const char *file1, const char *file2, const char *result) {
    std::ofstream merged(result, std::ios::binary | std::ios::out);
    std::ifstream left(file1, std::ios::binary | std::ios::in);
    std::ifstream right(file2, std::ios::binary | std::ios::in);
    uint64_t left_elem;
    uint64_t right_elem;
    left.read((char *) &left_elem, sizeof(uint64_t));
    right.read((char *) &right_elem, sizeof(uint64_t));
    while (left || right) {
        if ((!left) or ((right_elem > left_elem) && (left && right))) {
            merged.write((char *) &right_elem, sizeof(uint64_t));
            right.read((char *) &right_elem, sizeof(uint64_t));
        } else {
            merged.write((char *) &left, sizeof(uint64_t));
            left.read((char *) &left_elem, sizeof(uint64_t));
        }
    }
    left.close();
    right.close();
    merged.close();
}

void recursive_sort(const char *filename, size_t file_size) { //size means number of elements
    std::ifstream file(filename, std::ios::binary);
    if (file_size > MEM_BOUND) {
        std::string file1_string(filename);
        std::string file2_string(filename);
        file1_string += "left";
        file2_string += "right";
        std::ofstream file1(file1_string, std::ios::out);
        std::ofstream file2(file2_string, std::ios::out);
        for (size_t i = 0; i < file_size / 2; i++) {
            char temp;
            file.read((char *) (&temp), sizeof(char));
            file1.write((char *) (&temp), sizeof(char));
        }
        for (size_t i = 0; i < file_size - file_size / 2; i++) {
            char temp;
            file.read((char *) (&temp), sizeof(char));
            file2.write((char *) (&temp), sizeof(char));
        }
        file.close();
        recursive_sort(file1_string.c_str(), file_size / 2);
        recursive_sort(file2_string.c_str(), file_size - file_size / 2);
        merge(file1_string.c_str(), file2_string.c_str(), filename);

    } else {
        std::vector<uint64_t> array_to_sort;
        for (size_t i = 0; i < file_size / 2; i++) {
            uint64_t temp;
            file.read((char *) (&temp), sizeof(uint64_t));
            array_to_sort.push_back(temp);
        }
        file.close();
        std::sort(array_to_sort.begin(), array_to_sort.end(), comp_object);
        std::ofstream file_out(filename, std::ios::out | std::ios::binary);
        for (size_t i = 0; i < array_to_sort.size(); i++) {
            uint64_t a = array_to_sort[i];
            file_out.write((char *) (&a), sizeof(uint64_t));
        }
        file_out.close();
    }
}


void sort(const char *filename) {
    std::ifstream file(filename, std::ios::binary);
    file.seekg(0, std::ios::end);
    size_t number_of_elements = file.tellg() / sizeof(uint64_t);
    size_t elements_for_thread = number_of_elements / 2;
    std::ofstream file1("temp1", std::ios::out);
    std::ofstream file2("temp2", std::ios::out);
    for (size_t i = 0; i < elements_for_thread; i++) {
        uint64_t temp;
        file.read((char *) (&temp), sizeof(uint64_t));
        file1.write((char *) (&temp), sizeof(uint64_t));
    }
    for (size_t i = 0; i < number_of_elements - elements_for_thread; i++) {
        uint64_t temp;
        file.read((char *) (&temp), sizeof(uint64_t));
        file2.write((char *) (&temp), sizeof(uint64_t));
    }
    auto thread1 = std::thread([&]() { recursive_sort("temp1", elements_for_thread); });
    auto thread2 = std::thread([&]() { recursive_sort("temp2", elements_for_thread); });
    thread1.join();
    thread2.join();
    merge("temp1", "temp2", filename);
    file1.close();
    file2.close();
}


#endif //INC_9_SORTING_H
