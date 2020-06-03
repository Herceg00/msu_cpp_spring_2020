#ifndef INC_5_BIGINT_H
#define INC_5_BIGINT_H

#include <iostream>
#include <cstring>

class BigInt {
    unsigned char *local_number; // array for a BigInt
    bool sign;
    size_t length; // in the term of array
public:
    BigInt() {
        local_number = nullptr;
        sign = true;
        length = 0;
    }

    ~BigInt() {
        if (length) {
            free(local_number);
        }
    }

    explicit BigInt(int64_t num) {
        if (num < 0) {
            sign = false;
            num = -num;
        } else {
            sign = true;
        }
        length = 0;
        while (num > 0) {
            if (length > 0) {
                local_number = (unsigned char *) realloc(local_number, (length + 1) * sizeof(char));
            } else {
                local_number = (unsigned char *) malloc(sizeof(char));
            }
            local_number[length] = num % 10;
            length++;
            num /= 10;
        }
    }

    BigInt(const BigInt &other) {
        length = other.length;
        sign = other.sign;
        local_number = (unsigned char *) malloc(length * sizeof(char));
        std::copy(other.local_number, other.local_number + length, local_number);
    }

    BigInt &operator=(const BigInt &other) {
        sign = other.sign;
        if (length) {
            free(local_number);
        }
        length = other.length;
        std::cout << length << std::endl;
        local_number = (unsigned char *) malloc(length * sizeof(char));
        std::copy(other.local_number, other.local_number + length, local_number);
        return *this;
    }

    bool operator>(const BigInt &other) {
        if (length > other.length) {
            return true;
        }
        if (length < other.length) {
            return false;
        }
        size_t i = length;
        while (i) {
            i--;
            if (local_number[i] > other.local_number[i]) {
                return true;
            }
            if (local_number[i] < other.local_number[i]) {
                return false;
            }
        }
        return false;
    }

    bool operator<(const BigInt &other) {
        return !operator>(other);
    }

    bool operator>=(const BigInt &other) {
        if (length > other.length) {
            return true;
        }
        if (length < other.length) {
            return false;
        }
        size_t i = length;
        while (i) {
            i--;
            if (local_number[i] > other.local_number[i]) {
                return true;
            }
            if (local_number[i] < other.local_number[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator<=(const BigInt &other) {
        if (length > other.length) {
            return false;
        }
        if (length < other.length) {
            return true;
        }
        size_t i = length;
        while (i) {
            i--;
            if (local_number[i] > other.local_number[i]) {
                return false;
            }
            if (local_number[i] < other.local_number[i]) {
                return true;
            }
        }
        return true;
    }

    BigInt &operator-() {
        sign = !sign;
        return *this;
    }

    BigInt operator-(BigInt &other) {
        return operator+(-other);
    }

    BigInt operator+(BigInt &other) {
        if (sign && other.sign) {
            BigInt result;
            result.length = std::max(length, other.length);
            result.local_number = (unsigned char *) malloc(result.length);
            result.sign = sign;
            size_t min_size = std::min(length, other.length);
            size_t max_size = std::max(length, other.length);
            bool overflow_flag = false;
            for (size_t i = 0; i < min_size; i++) {
                unsigned char temp = local_number[i] + other.local_number[i];
                result.local_number[i] = temp % 10 + overflow_flag;
                if (temp > 9) {
                    overflow_flag = true;
                }
            }
            for (size_t i = min_size; i < max_size; i++) {
                if (max_size == length) {
                    unsigned char temp = local_number[i];
                    result.local_number[i] = temp % 10 + overflow_flag;
                    if (temp > 9) {
                        overflow_flag = true;
                    }
                } else {
                    unsigned char temp = other.local_number[i];
                    result.local_number[i] = temp % 10 + overflow_flag;
                    if (temp > 9) {
                        overflow_flag = true;
                    }
                }
            }
            if (overflow_flag) {
                result.local_number = (unsigned char *) realloc(result.local_number,
                                                                sizeof(char) * (result.length + 1));
                result.local_number[max_size] = 1;
            }
            return result;
        } else {
            size_t min_size = std::min(length, other.length);
            size_t max_size = std::max(length, other.length);
            BigInt result;
            result.length = max_size;
            result.local_number = (unsigned char *) malloc(result.length);
            if (((other.sign) && (other > -*this)) || ((!other.sign) && (-other > *this))) {
                bool credit_flag = false;
                other.sign ? result.sign = false: result.sign = true;
                for (size_t i = 0; i < min_size; i++) {
                    if (credit_flag) {
                        unsigned char temp;
                        if (other.local_number[i] == 0) {
                            result.local_number[i] = 9 - local_number[i];
                        } else {
                            temp = other.local_number[i] - 1;
                            if (local_number[i] > temp) {
                                credit_flag = true;
                                result.local_number[i] = 10 + temp - local_number[i];
                            } else {
                                credit_flag = false;
                                result.local_number[i] = temp - local_number[i];
                            }
                        }
                        continue;
                    }
                    if (local_number[i] > other.local_number[i]) {
                        credit_flag = true;
                        result.local_number[i] = 10 + other.local_number[i] - local_number[i];
                    } else {
                        result.local_number[i] = other.local_number[i] - local_number[i];
                    }
                }
                for (size_t i = min_size; i < max_size; i++) {
                    if (credit_flag) {
                        if (other.local_number[i] == 0) {
                            result.local_number[i] = 9;
                        } else {
                            result.local_number[i] = other.local_number[i] -  1;
                        }
                        continue;
                    }
                }
                for(size_t i = result.length - 1; i!=0;i--){
                    if(result.local_number[i]!=0){
                        break;
                    }
                    result.length--;
                    result.local_number = (unsigned char*)realloc(result.local_number,result.length);
                }
            } else {
                bool credit_flag = false;
                this->sign ? result.sign = true: result.sign = false;
                for (size_t i = 0; i < min_size; i++) {
                    if (credit_flag) {
                        unsigned char temp;
                        if (local_number[i] == 0) {
                            result.local_number[i] = 9 - other.local_number[i];
                        } else {
                            temp = local_number[i] - 1;
                            if (other.local_number[i] > temp) {
                                credit_flag = true;
                                result.local_number[i] = 10 + temp - other.local_number[i];
                            } else {
                                credit_flag = false;
                                result.local_number[i] = temp - other.local_number[i];
                            }
                        }
                        continue;
                    }
                    if (other.local_number[i] > local_number[i]) {
                        credit_flag = true;
                        result.local_number[i] = 10 + local_number[i] - other.local_number[i];
                    } else {
                        result.local_number[i] = local_number[i] - other.local_number[i];
                    }
                }
                for (size_t i = min_size; i < max_size; i++) {
                    if (credit_flag) {
                        if (local_number[i] == 0) {
                            result.local_number[i] = 9;
                        } else {
                            result.local_number[i] = local_number[i] -  1;
                            credit_flag = false;
                        }
                    }
                }
                for(size_t i = result.length - 1; i!=0;i--){
                    if(result.local_number[i]!=0){
                        break;
                    }
                    result.length--;
                    result.local_number = (unsigned char*)realloc(result.local_number,result.length);
                }
            }
            return result;
        }
    }

    friend std::ostream &operator<<(std::ostream &out, const BigInt &A) {
        if (A.sign == 0) {
            out << "-";
        }
        for (size_t i = A.length - 1; i != 0; i--) {
            out << int(A.local_number[i]);
        }
        out << int(A.local_number[0]);
        return out;
    }
};

#endif //INC_5_BIGINT_H