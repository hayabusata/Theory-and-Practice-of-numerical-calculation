#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

const int n = 4;
double a[n][n], b[n], x[n], x2[n];

const int itr_max = 100;	//最大反復回数
const double eps = 1.0e-7;	//誤差がこの値以下になったら反復をやめる

void display() {
	cerr << "<<<<<< display a >>>>>>" << endl;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cerr << a[i][j] << "\t";
		}

		cerr << b[i] << endl;
	}
}

double jacobi() {
	double err = 0.0;	//反復前後のxの差の絶対値の総和
	double sum = 0.0;

	//ヤコビ法
	cerr << "jacobi" << endl;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (j != i) sum += a[i][j] * x[j];
		}

		x2[i] = (b[i] - sum) / a[i][i];
		sum = 0.0;
	}

	for (int i = 0; i < n; i++) {
		err += fabs(x2[i] - x[i]);
		x[i] = x2[i];
	}

	return err;
}

double gausszaidel() {
	double err = 0.0;	//反復前後のxの差の絶対値の総和
	double sum = 0.0;

	//ガウスザイデル
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (j != i) {
				if (j < i) {
					sum += a[i][j] * x2[j];
				} else {
					sum += a[i][j] * x[j];
				}
			}
		}

		x2[i] = (b[i] - sum) / a[i][i];
		sum = 0.0;
	}

	for (int i = 0; i < n; i++) {
		err += fabs(x2[i] - x[i]);
		x[i] = x2[i];
	}

	return err;
}

int main() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cerr << "input a[" << i << "][" << j << "]" << endl;
			cin >> a[i][j];
		}

		cerr << "input b[" << i << "]" <<endl;
		cin >> b[i];
	}

	display();

	for (int i = 0; i < n; i++) {
		x[i] = 0.0;
	}

	for (int k = 0; k < itr_max; k++) {
		//double err = jacobi();
		double err = gausszaidel();
		cerr << k << "\t";

		for (int i = 0; i < n; i++) {
			fprintf(stderr, "%e\t", x[i]);
		}

		cerr << endl;
		if (err < eps) break;
	}
}