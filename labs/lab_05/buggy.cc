/*******************************************************************************
 * Name            : buggy.cc
 * Project         : Labs
 * Module          : Lab05
 * Description     : A sample file to read the contents of a file into a
 *                   character buffer
 * Copyright       : 2017 CSCI3081W Staff. All rights reserved.
 * Original Author : Dan DaCosta
 * Modifications by: John Harwell
 * Debugged by team: TEAM_NAME_HERE
 * Team Members    : Dalton Stokke , Xukun Qin
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cstdlib>
#include <iostream>
#include <string>


/*******************************************************************************
 * Functions
 ******************************************************************************/
// NewMat: Allocate a new matrix with dimensions x by y filling cell values
// randomly.
int** NewMat(int x, int y) {
  int** a = new int*[x];
  for (int i = 0; i < x; i++) {
    a[i] = new int[y];
    for (int j = 0; j < y; j++) {
      a[i][j] = rand() % 13;
    } /* for(j..) */
  } /* for(i..) */
  return a;
}

// MulMat: Multiplies A with dimensions x by y by B with dimensions y by z and
// returns a new matrix C with dimensions x by z.
// Pseudocode for matrix multiplication:
// for i from 1 to x
//   for j from 1 to z
//     C[i,j] = 0
//     for k from 1 to y
//       C[i,j] += A[i,k]B[k,j]
int** MulMat(int x, int y, int z, int** A, int** B) {
  int** R = NewMat(x, z);
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < z; j++) {
      R[i][j] = 0;
      for (int k = 0; k < y; k++) {
        R[i][j] += A[i][k] * B[k][j];
      } /* for(k..) */
    } /* for(j..) */
  } /* for(i..) */
  return R;
}

// print_mat: Print the matrix A with dimensions x by y.
void print_mat(int x, int y, int** A) {
  std::cout << "Printing " << x << " by " << y << " matrix:" << std::endl;
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      std::cout << A[i][j] << " ";
    } /* for(j..) */
    std::cout << std::endl;
  } /* for(i..) */
  std::cout << std::endl;
}

void execute() {
  int** A = NewMat(7, 11);
  int** B = NewMat(11, 13);
  int** C = MulMat(7, 11, 13, A, B);
  print_mat(7, 13, C);
  for (int i = 0; i < 7; i++) {
      delete [] A[i];
      }
  delete [] A;
  for (int i = 0; i < 7; i++) {
      delete [] B[i];
      }
  delete [] B;
  for (int i = 0; i < 7; i++) {
      delete [] C[i];
      }
  delete [] C;
}

int main(int argc, char** argv) {
  execute();
  return 0;
}
