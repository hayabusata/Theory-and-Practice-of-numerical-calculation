#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

int main() {
	double x0 = 0.0;
	double xe = 4.0;
	double t0 = 0.0;
	double te = 1.0;
	double h = 0.50;
	double c = 2.0;
	double k = 0.1;

	int n = (xe - x0) / h;
	int n2 = n - 1;
	int nt = (te - t0) / k;

	double r = c * k / pow(h, 2);
	double p = 2 * (1 + 1 / r);
	double q = 2 * (1 - 1 / r);

	cerr << h << "\t" << k << "\t" << n << "\t" << nt << "\t" << r << endl;
	cerr << p << "\t" << q << endl;

	double z[n + 1][nt];

	for (int i = 0; i < n; i++) {
		//初期条件の入力
		z[i][0] = 1.0;
	}

	for (int j = 0; j < nt; j++) {
		//境界条件の入力
		z[0][j] = 0;
		z[n][j] = 0;
	}

	//n2*n2行列
	/*double a[n2][n2];
	for (int i = 0; i < n2; i++) {
		for (int j = 0; j < n2; j++) {
			if (i == j) a[i][j] = -p;
			else if (i == j + 1 || j == i + 1) a[i][j] = 1;
			else a[i][j] = 0;
		}
	}*/

	double a0[n2][n2], a[n2][n2], b[n2];
	for (int i = 0; i < n2; i++) {
		for (int j = 0; j < n2; j++) {
			a0[i][j] = 0;
		}
	}
	a0[0][0] = -p;
	a0[0][1] = 1.0;
	a0[n2 - 1][n2 - 2] = 1.0;
	a0[n2 - 1][n2 - 1] = -p;
	for (int i = 1; i < n2 - 1; i++) {
		a0[i][i - 1] = 1.0;
		a0[i][i] = -p;
		a0[i][i + 1] = 1.0;
	}

	for (int i = 0; i < n2; i++) {
		for (int j = 0; j < n2; j++) {
			cerr << a0[i][j] << "\t";
		}
		cerr << endl;
	}

	for (int k = 0; k < (nt - 1); k++) {
		for (int i = 0; i < n2; i++) {
			b[i] = -z[i][k] + q * z[i + 1][k] - z[i + 2][k];
			for (int j = 0; j < n2; j++) {
				a[i][j] = a0[i][j];
			}
		}

		forward(n2);
		backward(n2);
		for (int i = 0; i < n2; i++) {
			z[i + 1][k + 1] = x[i];
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