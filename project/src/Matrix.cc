/*******************************************************************************
 * Name            : Matrix.cc
 * Project         : fcal
 * Module          : CppCode
 * Description     : Provides function definitions for Matrix implementation
 * Copyright       : 2017 Original Authors. All rights reserved.
 * Original Authors : Dalton Stoke and Xukun Qin
 * Modifications by : None
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "include/Matrix.h"

/*******************************************************************************
 * Functions
 ******************************************************************************/

// matrix constructors
matrix::matrix(int i, int j) {
    rows = i;
    cols = j;
    // create new matrix
    data = new float[i*j];
}

matrix::matrix(const matrix& m) {
    rows = m.n_rows();
    cols = m.n_cols();
    // copy matrix to new matrix
    data = new float[rows*cols];
    int i, j;
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            data[(i*cols)+j] = *(m.access(i, j));
        }
    }
}

// matrix deconstructor
matrix::~matrix() {}

// accessors
int matrix::n_rows() const {
    return rows;
}

int matrix::n_cols() const {
    return cols;
}

// exit on failure
float *matrix::access(const int i, const int j) const {
    if ((0 > i || i >= rows) || (0 > j || j >= cols)) {
        printf("cannot access index (%d,%d) out of bounds\n", i, j);
        fflush(stdout);
        exit(0);
    }
    return &data[(i*cols) + j];
}

// print
std::ostream& operator<<(std::ostream &os, matrix &m) {
    os << m.n_rows() << " " << m.n_cols() << std::endl;
    int i, j;
    for (i = 0; i < m.n_rows(); i++) {
        for (j = 0; j < m.n_cols(); j++) {
            os << *(m.access(i, j)) << "  ";
        }
        os << std::endl;
    }
    return os;
}

// returns 1,1 empty matrix on failure
matrix& matrix::matrix_read(std::string filename) {
    std::ifstream ifs(filename.c_str());
    int i, j, row, col;
    if (!ifs) {
		matrix *dummy = new matrix(1, 1);
        printf("File not found.\n");
        fflush(stdout);
        return *dummy;
    }

    ifs >> row;
    ifs >> col;
    float temp;
    matrix *m = new matrix(row, col);
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            ifs >> temp;
            *(m->access(i, j)) = temp;
        }
    }
    return *m;
}

// returns 1,1 empty matrix on failure
matrix& matrix::operator*(const matrix &m1) {
    int i, j, n;
    if (cols != m1.n_rows()) {
		matrix *dummy = new matrix(1, 1);
        printf("Invalid matrix operation.\n");
        fflush(stdout);
        return *dummy;
    }
    matrix *m = new matrix(rows, m1.n_cols());
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < m1.n_cols(); ++j) {
            *m->access(i, j) = 0;
            for (n = 0; n < m1.n_rows(); ++n) {
                *m->access(i, j) = *(m->access(i, j)) +
                        *(this->access(i, n)) * *(m1.access(n, j));
            }
        }
    }
    return *m;
}

matrix& matrix::operator=(const matrix &m) {
    if (this == &m) {
        return *this;
    }
    rows = m.n_rows();
    cols = m.n_cols();
    data = new float[rows*cols];
    int i, j;
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            data[(i*cols)+j] = *(m.access(i, j));
        }
    }
    return *this;
}





