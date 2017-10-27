#include <iostream>
#include "include/Matrix.h"
#include <math.h>
using namespace std;
int main ( ) {
    matrix l ( matrix::matrix_read ("./samples/my_code_1.data") ) ; 
    matrix m ( matrix::matrix_read ("./samples/sample_8.data") ) ;
    matrix ans ( ( l * m ) );
    cout << l ;
    cout << m ;
    cout << ans ;
}

