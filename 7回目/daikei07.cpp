#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

double f(double x) {
	return (1 - x) * exp(-x);
}

double integralByTrapezoid(int a, int b, int d) {
	double sum = 0;

	double h = (double)(b - a) / (double)d;

	for (double x = a + h; x < b; x += h) {
		sum += f(x);
	}

	return h * (f(a) + 2 * sum + f(b)) / 2;
}

int main() {
	int a = -1, b = 1;
	int h;

	cerr << "divide = ";
	cin >> h;

	cerr << "integral f(x) [" << a << ", " << b << "] = " << integralByTrapezoid(a, b, h) << endl;

	return 0;
}