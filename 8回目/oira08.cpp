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

int main() {
	double x0, y0, xe, h;
	cerr << "input x0, y0, xe, h" << endl;
	cin >> x0 >> y0 >> xe >> h;
	cerr << x0 << "\t" << y0 << "\t" << xe << "\t" << h << endl;

	//オイラー法
	double x = x0;
	double y = y0;
	while (x < xe) {
		y = y + func(x, y) * h;
		x += h;
		cerr << x << "\t" << y << "\t" << func_y(x) << endl;
	}
}