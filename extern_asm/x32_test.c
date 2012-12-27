#include <stdio.h>

// extern 宣言でアセンブラ内の関数を読み込む
extern int _add(int a, int b);
extern int _sub(int a, int b);
extern int _mul(int a, int b);
extern int _div(int a, int b);
extern float _fadd(float a, float b);
extern float _fsub(float a, float b);
extern float _fmul(float a, float b);
extern float _fdiv(float a, float b);

int main () {
	int i1 = 20, i2 = 4, i3;
	float f1 = 1.5,f2 = 0.3,f3;

	i3 = _add(i1, i2);
	printf("add(%d, %d)=%d\n", i1, i2, i3);
	i3 = _sub(i1, i2);
	printf("sub(%d, %d)=%d\n", i1, i2, i3);
	i3 = _mul(i1, i2);
	printf("mul(%d, %d)=%d\n", i1, i2, i3);
	i3 = _div(i1, i2);
	printf("div(%d, %d)=%d\n", i1, i2, i3);

	f3 = _fadd(f1, f2);
	printf("fadd(%f, %f)=%f\n", f1, f2, f3);
	f3 = _fsub(f1, f2);
	printf("fsub(%f, %f)=%f\n", f1, f2, f3);
	f3 = _fmul(f1, f2);
	printf("fmul(%f, %f)=%f\n", f1, f2, f3);
	f3 = _fdiv(f1, f2);
	printf("fdiv(%f, %f)=%f\n", f1, f2, f3);
    return 0;
}
