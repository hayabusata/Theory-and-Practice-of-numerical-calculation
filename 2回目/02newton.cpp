#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

double func(const double x) {
	//関数の値を返す
	return pow(x, 3) - 3 * pow(x, 2) + 9 * x - 8;
}

double func_d(const double x) {
	//微分値を返す
	double h = 0.0001;
	return (func(x + h) - func(x)) / h;
}

void newton(double epsilon, double x) {
	int step = 0;
	double nextX = x;

	cerr << "x" << step << " = " << x << endl;

	do {
		x = nextX;
		nextX = x - (func(x) / func_d(x));
		step++;

		cerr << "x" << step << " = " << nextX << ", func = " << func(nextX) << endl;
	} while (abs(nextX - x) > epsilon);
}

void secant(double epsilon, double x, double beforeX) {
	int step = 0;
	double nextX = x;

	cerr << "x" << step << " = " << x << endl;

	do {
		x = nextX;
		nextX = x - ((x - beforeX) / (func(x) - func(beforeX))) * func(x);
		step++;

		cerr << "x" << step << " = " << nextX /*<< ", func = " << func(nextX)*/ << endl;
		beforeX = x;
	} while (abs(nextX - x) > epsilon);
}

int main() {
	double epsilon = 0.0;
	double x = 0.0;
	double x2 = 0.0;
	cerr << "Enter x0, epsilon" << endl;
	cin >> x >> epsilon;
	cerr << "Enter x2" << endl;
	cin >> x2;

	//ニュートン法の実装
	//newton(epsilon, x);

	//セカント法の実装
	secant(epsilon, x, x2);

	cerr << "end program" << endl;
}