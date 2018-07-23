#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

double func(double x, double xe) {
	return 0.05 * x * (xe - x);
}

int main() {
	double x0 = 0.0;
	double xe = 2.0;
	double t0 = 0.0;
	double te = 5.0;
	double h = 0.25;
	double c = 9.0;
	double k = h / sqrt(c);
	int n = (xe - x0) / h;
	int nt = (te - t0) / k;

	double z[n + 1][nt];

	cerr << n << ", " << nt << endl;

	for (int i = 0; i < n; i++) {
		//初期条件の入力
		double x = x0 + i * h;
		z[i][0] = func(x, xe);
		//z[i][0] = 0.05 * i * (xe - i);
	}

	for (int j = 0; j < nt; j++) {
		//境界条件の入力
		z[0][j] = 0;
		z[n][j] = 0;
	}

	//j = 1でのzの計算
	for (int i = 1; i < n; i++) {
		z[i][1] = 0.5 * (z[i + 1][0] + z[i - 1][0]);
	}

	//j = 1以降でのzの計算
	for (int j = 1; j < nt - 1; j++) {
		for (int i = 1; i < n; i++) {
			z[i][j + 1] = z[i + 1][j] + z[i - 1][j] - z[i][j - 1];

		}
	}

	for (int j = 0; j < nt; j++) {
		for (int i = 0; i <= n; i++) {
			double x = x0 + i * h;
			fprintf(stdout, "%.4lf %.4lf\n", x, z[i][j]);
		}

		fprintf(stdout, "\n\n");
	}
}