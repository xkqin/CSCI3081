#include "include/Matrix.h"

using namespace std;

int main() {
    float test[12] = {0.0,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0};
    matrix a (3,4);

    int i, j, k;
	float *temp;
    k = 0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
			temp = a.access(i,j);
			*temp = test[k];
			k++;
        }
    }
    matrix l = matrix::matrix_read("samples/sample_8.data");

	cout << a << endl;
	cout << l << endl;

	matrix ans = a * l;
  ans = ans;
	cout << ans << endl;
}
