#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

double func(const double x) {
	//関数の値を返す
	return pow(x, 3) - 3 * pow(x, 2) + 9 * x - 8;
	//return 3 * atan(x - 1) + x / 4;
}

double func_d(const double x) {
	//微分値を返す
	double h = 0.0001;
	return (func(x + h) - func(x)) / h;
}

//２分法
double dichotomy(double a, double b) {
	return (a + b) / 2;
}

double regulaFalsi(double a, double b) {
	return (a * func(b) - b * func(a)) / (func(b) - func(a));
}

void newtonAndDual(double epsilon) {
	int step = 0;
	double x = 0.0;
	double xa = 0.0;
	double xb = 0.0;

	do {
		//f(xa) * f(xb) < 0 になるまでa,bの入力を繰り返す
		cerr << "Enter xa -->";
		cin >> xa;

		cerr << "Enter xb -->";
		cin >> xb;
	}  while (func(xa) * func(xb) >= 0);

	x = xa;
	double nextX = x;

	do {
		step++;
		x = nextX;

		if (abs(func(x - (func(x) / func_d(x)))) <= abs(func(dichotomy(xa, xb)))) {
			nextX = x - (func(x) / func_d(x));
		} else if (abs(func(x - (func(x) / func_d(x)))) > abs(func(dichotomy(xa, xb)))) {
			nextX = dichotomy(xa, xb);
		}

		//nextX = dichotomy(xa, xb);

		double fc = func(nextX);

		cerr << step << endl;
		cerr << "x" << " = " << nextX << ", func = " << func(nextX) << endl;

		if (fc == 0) break;
		else if (fc > 0) {
			if (func(xa) > 0) xa = nextX;
			else if (func(xb) > 0) xb = nextX;
		} else if (fc < 0) {
			if (func(xa) < 0) xa = nextX;
			else if (func(xb) < 0) xb = nextX;
		}
	} while (abs(xa - xb) > epsilon && abs(nextX - x) > epsilon);
}

int main() {
	double epsilon = 0.0;
	cerr << "Enter epsilon" << endl;
	cin >> epsilon;
	
	newtonAndDual(epsilon);

	cerr << "end program" << endl;
}