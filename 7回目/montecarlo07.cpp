#include <iostream>
#include <cstdio>
#include <cstdlib>
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

double integralBySimpson(int a, int b) {
	int d;
	cerr << "divide (2n) -> ";
	cin >> d;

	double h = (double)(b - a) / (double)d;

	double x = a;
	double i;
	double sum = 0; 
	double f1, f2, f3;
	do {
		i = (x + h) / 3;

		f1 = f(x);
		f2 = f(x + i);
		f3 = f(x + i * 2);

		sum += f1 + 4 * f2 + f3;

		x += h;
	} while (x < b);

	return h * sum / 3;
	
}

void integralByMontecarlo(int a, b) {
	int n;
	cerr << "input n" << endl;
	cin >> n;
	cerr << n << endl;

	srand48(time(NULL));

	int n2 = 0;
	for (int i = 0; i < n; i++) {
		double x = drand48();
		double y = drand48();
		double r2 = x * x + y * y;
		if (r2 < 1.0) n2++;
	}

	cerr << n2 << "\t" << 4.0 * n2 / n << endl;
}

int main() {
	integralByMontecarlo(0, 1);

	return 0;
}