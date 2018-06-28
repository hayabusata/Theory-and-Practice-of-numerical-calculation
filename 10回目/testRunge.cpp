#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

static const int NMAX = 128;

//ルンゲクッタ用の変数
static double xtmp[NMAX][3];
static double k[NMAX][3], k1[NMAX][3], k2[NMAX][3], k3[NMAX][3], k4[NMAX][3];
static double l[NMAX][3], l1[NMAX][3], l2[NMAX][3], l3[NMAX][3], l4[NMAX][3];

void gravity(double (*x)[3], double *m, double (*a)[3], double *p, const int n) {
	for (int i = 0; i < n; i++) {
		//各質点にはたらく重力を計算する
		for (int j = 0; j < 3; j++) {
			a[i][j] = 0;
		}

		for (int j = 0; j < n; j++) {
			if (i != j) {
				double dr = 0;
				for (int k = 0; k < 3; k++) {
					dr += pow(x[j][k] - x[i][k], 2);
				}
				dr = sqrt(dr);

				for (int k = 0; k < 3; k++) {
					a[i][k] += 1.0 * m[i] * (x[j][k] - x[i][k]) / pow(dr, 3.0);
				}
			}
		}
	}
}

double energy(double (*v)[3], double *m, double *p, const int n) {
	//総エネルギーを計算する
	double v2, sumEnergy = 0;

	for (int i = 0; i < n; i++) {
		v2 = pow(v[i][0], 2) + pow(v[i][1], 2) + pow(v[i][2], 2);
		p[i] = 0.5 * m[i] * v2;
		sumEnergy += p[i];
	}

	return sumEnergy;
}

void runge4(double (*x)[3], double (*v)[3], double *m, double (*a)[3], double *p, const double dt, const int n) {
	gravity(x, m, a, p, n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 3; j++) {
			k1[i][j] = v[i][j] * dt;
			l1[i][j] = a[i][j] * dt;

			xtmp[i][j] = x[i][j] + 0.5 * k1[i][j];
		}
	}

	gravity(xtmp, m, a, p, n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 3; j++) {
			k2[i][j] = (v[i][j] + 0.5 * l1[i][j]) * dt;
			l2[i][j] = a[i][j] * dt;

			xtmp[i][j] = x[i][j] + 0.5 * k2[i][j];
		}
	}

	gravity(xtmp, m, a, p, n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			k3[i][j] = (v[i][j] + 0.5 * l2[i][j]) * dt;
			l3[i][j] = a[i][j] * dt;

			xtmp[i][j] = x[i][j] + k3[i][j];
		}
	}

	gravity(xtmp, m, a, p, n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			k4[i][j] = (v[i][j] + l3[i][j]) * dt;
			l4[i][j] = a[i][j] * dt;

			k[i][j] = (k1[i][j] + 2.0 * k2[i][j] + 2.0 * k3[i][j] + k4[i][j]) / 6.0;
			l[i][j] = (l1[i][j] + 2.0 * l2[i][j] + 2.0 * l3[i][j] + l4[i][j]) / 6.0;

			x[i][j] += k[i][j];
			v[i][j] += l[i][j];
		}
	}
}

int main() {
	double x[NMAX][3];
	double v[NMAX][3];
	double a[NMAX][3];
	double m[NMAX];
	double p[NMAX];
	int n;
	double dt, tend;

	cerr << "input n, dt, tend, m, x, v" << endl;
	cin >> n >> dt >> tend;
	cerr << n << "\t" << dt << "\t" << tend << endl;
	for (int i = 0; i < n; i++) {
		cin >> m[i];
		for (int j = 0; j < 3; j++) cin >> x[i][j];
		for (int j = 0; j < 3; j++) cin >> v[i][j];
	}

	gravity(x, m, a, p, n);
	double e0 = energy(v, m, p, n);
	double tnow = 0.0;

	cout << tnow << "\t"
		 << x[0][0] << "\t" << x[0][1] << "\t" << x[0][2] << "\t"
		 << x[1][0] << "\t" << x[1][1] << "\t" << x[1][2] << "\t"
		 << x[2][0] << "\t" << x[2][1] << "\t" << x[2][2] << "\t";

	while (tnow < tend) {
		runge4(x, v, m, a, p, dt, n);
		double e = energy(v, m, p, n);
		tnow += dt;

		cout << tnow << "\t"
		 	 << x[0][0] << "\t" << x[0][1] << "\t" << x[0][2] << "\t"
		 	 << x[1][0] << "\t" << x[1][1] << "\t" << x[1][2] << "\t"
		 	 << x[2][0] << "\t" << x[2][1] << "\t" << x[2][2] << "\t"
		 	 << e << "\t" << (e - e0) / e0 << endl;
	}

	return 0;
}