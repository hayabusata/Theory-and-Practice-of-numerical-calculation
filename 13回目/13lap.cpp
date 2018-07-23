#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

int main() {
	double x0 = 0.0;
	double xe = 1.0;
	double y0 = 0.0;
	double ye = 1.0;
	int n;
	cerr << "input n " << endl;
	cin >> n;

	double dx = (xe - x0) / (n - 1);
	double dy = (ye - y0) / (n - 1);

	const int itr_max = 100;		//ガウスザイデルの最大反復数
	const double eps = 1.0e - 7;	//反復法の許容エラー
	double z[n][n];

	//初期値と境界条件を設定
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			z[i][j] = 0;
		}
	}

	for (int i = 0; i < n; i++) {
		z[i][0] = 0;
		z[i][n - 1] = i * dx;
		z[0][i] = 0;
		z[n - 1][i] = i * dy;

	}

	for (int k = 0; k < itr_max; k++) {
		//ガウスザイデルで方程式を解く

	}

	for (int i = 0; i < n; i++) {
		double x = i * dx;

		for (int j = 0; j < n; j++) {
			double y = j * dy;
			fprintf(stdout, "%.4lf\t%.4lf\t%.4lf\n", x, y, z[i][j]);
		}

		fprintf(stdout, "\n");
	}
}