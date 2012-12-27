#include <stdio.h>

extern int _add(int a, int b);
extern int _sub(int a, int b);
extern int _mul(int a, int b);
extern int _div(int a, int b);
extern float _fadd(float a, float b);
extern float _fsub(float a, float b);
extern float _fmul(float a, float b);
extern float _fdiv(float a, float b);

int main () {
	printf("_add 4 + 9 = %d\n", _add(4,9));
	printf("_sub 18 - 7 = %d\n", _sub(18,7));
	printf("_mul 8 * 6 = %d\n", _mul(8,6));
	printf("_div 27 / 8 = %d\n", _div(27,8));

	printf("_fadd %f\n", _fadd(4.15, 6.26));
	printf("_fsub %f\n", _fsub(8.56, 4.87));
	printf("_fmul %f\n", _fmul(2.5, 3.76));
	printf("_fdiv %f\n", _fdiv(15.98, 3.64));
    return 0;
}

