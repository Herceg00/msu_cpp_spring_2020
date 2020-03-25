#ifndef INC_2_MATRIX_H
#define INC_2_MATRIX_H


class Matrix {
    int n_rows, n_cols;
    int **pointer;
public:
    class row_array{
        int *row_pointer;
        int n_cols;
    public:
        row_array(int* temp_row, int n_cols):n_cols(n_cols),row_pointer(temp_row){};
        int& operator[](int i){
            if (i >=n_cols){
                throw std::out_of_range("1 axis out of range");
            } else{
                return row_pointer[i];
            }
        }
        int operator[](int i) const{
            if (i >=n_cols){
                throw std::out_of_range("1 axis out of range");
            } else{
                return row_pointer[i];
            }
        }
    };
    int get_n_cols(void) {return n_cols;}
    int get_n_rows(void) {return n_rows;}
    row_array operator[](int i) const {
        if(i >= n_rows){
            throw std::out_of_range("0 axis out of range");
        } else {
            return row_array(pointer[i],n_cols);
        }
    }
    row_array operator[](int i) {
        if(i >= n_rows){
            throw std::out_of_range("0 axis out of range");
        } else {
            return row_array(pointer[i],n_cols);
        }
    }
    Matrix(int n_rows,int n_cols):n_cols(n_cols),n_rows(n_rows){
        pointer = new int*[n_rows];
        for (int i = 0; i < n_rows; i++) {
            pointer[i] = new int[n_cols];
            for (int j = 0; j <n_cols ; j++) {
                pointer[i][j] = 0;
            }
        }

    }
    Matrix& operator*=(const int num){
        for(int i = 0;i<n_rows;i++){
            for(int j = 0; j<n_cols;j++){
                pointer[i][j] *=num;
            }
        }
    }

    const void print_matrix(void) const{
        for(int i = 0;i<n_rows;i++){
            for(int j = 0; j<n_cols;j++){
                std::cout<<pointer[i][j];
            }
            std::cout<<std::endl;
        }
    }

    const bool operator==(Matrix& m) const {
        if ((m.get_n_cols()!=n_cols)||(m.get_n_rows()!=n_rows))
            return false;
        for(int i = 0;i<n_rows;i++){
            for(int j = 0; j<n_cols;j++){
                if(m[i][j]!=pointer[i][j]){
                    return false;
                }
            }
        }
        return true;
    }

    ~Matrix(){
        for (size_t i = 0; i < n_rows; i++) {
            delete[] pointer[i];
        }
        delete pointer;
    }

};
#endif //INC_2_MATRIX_H
