/*******************************************************************************
 * Name            : Matrix.h
 * Project         : fcal
 * Module          : CppCode
 * Description     : Header file for Matrix.cc
 * Copyright       : 2017 Original Authors. All rights reserved.
 * Original Authors : CSCI3081W Staff
 * Modifications by : Dalton Stoke and Xukun Qin
 ******************************************************************************/

#ifndef PROJECT_INCLUDE_MATRIX_H_
#define PROJECT_INCLUDE_MATRIX_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/


#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

/*******************************************************************************
 * Forward Declarations
 ******************************************************************************/

class matrix {
 public:
    matrix(int i, int j);
    matrix(const matrix& m);

    ~matrix();

    int n_rows() const;
    int n_cols() const;
    float *access(const int i, const int j) const;
    friend std::ostream& operator<<(std::ostream &os, matrix &m);
    static matrix& matrix_read(std::string filename);
    matrix& operator*(const matrix &m);
    matrix& operator=(const matrix &m);

 private:
    matrix() { }
    int rows;
    int cols;

    /* Your implementation of "data" may vary.  There are ways in
       which data can be an array of arrays and thus simplify the
       access method, at the cost of complicating the process of
       allocating space for data.  The choice is entirely up to
       you. */
    float *data;
};

#endif  // PROJECT_INCLUDE_MATRIX_H_
