#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

double f(const double x, const double y) {
	return pow(x, 2) + pow(y, 2) - 1;
}

double fx(const double x, const double y) {
	double h = 0.001;
	return (f(x + h, y) - f(x, y)) / h;
}

double fy(const double x, const double y) {
	double h = 0.001;
	return (f(x, y + h) - f(x, y)) / h;
}

double g(const double x, const double y) {
	return pow(x, 3) - y;
}

double gx(const double x, const double y) {
	double h = 0.001;
	return (g(x + h, y) - g(x, y)) / h;
}

double gy(const double x, const double y) {
	double h = 0.001;
	return (g(x, y + h) - g(x, y)) / h;
}

int main() {
	double x = 0.0;
	double y = 0.0;
	double epsilon = 0.0;
	cerr << "Enter x0, y0, epsilon" << endl;
	cin >> x >> y >> epsilon;

	int step = 0;
	double dx = 0.0;
	double dy = 0.0;
	cerr << "step x y dx dy" << endl;

	do {
		//2変数ニュートン法の実装
		double value = fx(x, y) * gy(x, y) - fy(x, y) * gx(x, y);
		dx = (gy(x, y) * (-f(x, y)) - fy(x, y) * (-g(x, y))) / value;
		dy = (-gx(x, y) * (-f(x, y)) + fx(x, y) * (-g(x, y))) / value;

		x += dx;
		y += dy;
		fprintf(stderr, "%d\t%.8e\t%.8e\t%.8e\t%.8e\n", step, x, y, dx, dy);
		step++;
	} while (fabs(dx) > epsilon || fabs(dy) > epsilon);
}