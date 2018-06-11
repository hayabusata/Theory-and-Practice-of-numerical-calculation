#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

//f(x,y)の計算
double func(const double x, const double y) {
	return y - 12 * x + 3;
}

//真値の計算
double func_y(const double x) {
	return 12 * x - 8 * exp(x) + 9;
}

double runge(const double x, const double y, const double h) {
	double k1 = h * func(x, y);
	double k2 = h * func(x + h, y + k1);
	return y + (k1 + k2) / 2;
}

int main() {
	double x0, y0, xe, h;
	cerr << "input x0, y0, xe, h" << endl;
	cin >> x0 >> y0 >> xe >> h;
	cerr << x0 << "\t" << y0 << "\t" << xe << "\t" << h << endl;

	//オイラー法
	double x = x0;
	double y1 = y0;
	double y2 = y0;
	cerr << "x    oira    runge     value" << endl;
	while (x < xe) {
		y1 = y1 + func(x, y1) * h;
		y2 = runge(x, y2, h);
		x += h;
		cerr << x << "\t" << y1 << "\t" << y2 << "\t" << func_y(x) << endl;
	}
}