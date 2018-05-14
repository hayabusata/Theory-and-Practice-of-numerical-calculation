#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

double func(const double x) {
	//関数の値を返す
	return pow(x, 3) - 3 * pow(x, 2) + 9 * x - 8;
}

//２分法
double dichotomy(double a, double b) {
	return (a + b) / 2;
}

double regulaFalsi(double a, double b) {
	return (a * func(b) - b * func(a)) / (func(b) - func(a));
}

int main() {
	//f(x) = x^3 - 3x^2 + 9x -8

	double epsilon = 0.0;
	cerr << "Enter epsilon" << endl;
	cin >> epsilon;

	double a = 0.0;
	double b = 0.0;
	do {
		//f(a) * f(b) < 0 になるまでa,bの入力を繰り返す
		cerr << "Enter a -->";
		cin >> a;

		cerr << "Enter b -->";
		cin >> b;

		
	}  while (func(a) * func(b) >= 0);

	int step = 0;
	while (b - a > epsilon) {
		//二分法の本体の実装
		double c = dichotomy(a, b);
		//double c = regulaFalsi(a, b);
		double fc = func(c);
		cerr << "f(" << c << ") = " << fc << endl;
		//cerr << "b - a = " << b - a << endl;

		if (fc == 0) break;
		else if (fc > 0) {
			if (func(a) > 0) a = c;
			else if (func(b) > 0) b = c;
			step++;
		} else if (fc < 0) {
			if (func(a) < 0) a = c;
			else if (func(b) < 0) b = c;
			step++;
		}
	}

	cout << "program end" << endl;
}