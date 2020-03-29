#ifndef INC_2_MATRIX_H
#define INC_2_MATRIX_H


class Matrix {
    size_t n_rows, n_cols;
    int **pointer;
public:
    class row_array {
        int *row_pointer;
        size_t n_cols;
    public:
        row_array(int *temp_row, size_t n_cols) : n_cols(n_cols), row_pointer(temp_row) {};

        int &operator[](size_t i) {
            if (i >= n_cols) {
                throw std::out_of_range("1 axis out of range");
            } else {
                return row_pointer[i];
            }
        }

        int operator[](size_t i) const {
            if (i >= n_cols) {
                throw std::out_of_range("1 axis out of range");
            } else {
                return row_pointer[i];
            }
        }
    };

    size_t get_n_cols(void) const { return n_cols; }

    size_t get_n_rows(void) const { return n_rows; }

    row_array operator[](size_t i) const {
        if (i >= n_rows) {
            throw std::out_of_range("0 axis out of range");
        } else {
            return row_array(pointer[i], n_cols);
        }
    }

    row_array operator[](size_t i) {
        if (i >= n_rows) {
            throw std::out_of_range("0 axis out of range");
        } else {
            return row_array(pointer[i], n_cols);
        }
    }

    Matrix(size_t n_rows, size_t n_cols) : n_cols(n_cols), n_rows(n_rows) {
        pointer = new int *[n_rows];
        for (size_t i = 0; i < n_rows; i++) {
            pointer[i] = new int[n_cols];
            for (size_t j = 0; j < n_cols; j++) {
                pointer[i][j] = 0;
            }
        }

    }

    void operator*=(const int num) const {
        for (size_t i = 0; i < n_rows; i++) {
            for (size_t j = 0; j < n_cols; j++) {
                pointer[i][j] *= num;
            }
        }
    }

    const void print_matrix(void) const {
        for (size_t i = 0; i < n_rows; i++) {
            for (size_t j = 0; j < n_cols; j++) {
                std::cout << pointer[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    const bool operator==(const Matrix &m) const {
        if ((m.get_n_cols() != n_cols) || (m.get_n_rows() != n_rows))
            return false;
        for (size_t i = 0; i < n_rows; i++) {
            for (size_t j = 0; j < n_cols; j++) {
                if (m[i][j] != pointer[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    const bool operator!=(const Matrix &m) const {
        return !(*this == m);
    }

    ~Matrix() {
        for (size_t i = 0; i < n_rows; i++) {
            delete[] pointer[i];
        }
        delete[] pointer;
    }


};


#endif //INC_2_MATRIX_H
