#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

const int n = 2;
double a[n][n], b[n], x[n];		//連立方程式用の配列
const int nData = 10;			//データ数
double xk[nData], yk[nData];	//データ

void display() {
	cerr << "<<<<<< display a,b >>>>>>" << endl;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cerr << a[i][j] << "\t";
		}

		cerr << b[i] << endl;
	}
}

void selectPivot(const int s) {
	double max = 0;
	int max_s = s;
	double tmp;

	for (int i = s + 1; i < n; i++) {
		if (a[i][s] > max) {
			max = a[i][s];
			max_s = i;
		}
	}

	cerr << "s = " << s << ", max_s = " << max_s << endl;

	for (int i = 0; i < n; i++) {
		tmp = a[s][i];
		a[s][i] = a[max_s][i];
		a[max_s][i] = tmp;
	}

	tmp = b[s];
	b[s] = b[max_s];
	b[max_s] = tmp;

	display();
}

void forward() {
	for (int i = 0; i < n; i++) {
		selectPivot(i);

		b[i] /= a[i][i];

		for (int j = n - 1; j >= i; j--) {
			a[i][j] /= a[i][i];
		}

		for (int j = i + 1; j < n; j++) {
			b[j] -= b[i] * a[j][i];

			for (int k = n - 1; k >= i; k--) {
				a[j][k] -= a[i][k] * a[j][i];
			}
		}

		display();
	}
}

//逆進代入
void backward() {
	for (int i = n - 1; i >= 0; i--) {
		x[i] = b[i] / a[i][i];

		for (int j = 0; j < i; j++) {
			b[j] -= a[j][i] * x[i];
		}
	}
}

int main() {
	for (int i = 0; i < nData; i++) {
		cerr << "input xk[" << i << "]\tyk[" << i << "]" << endl;
		cin >> xk[i] >> yk[i];
		cerr << xk[i] << "\t" << yk[i] << endl;
	}

	a[0][0] = a[0][1] = b[0] = b[1] = x[0] = x[1] = 0.0;

	for (int i = 0; i < nData; i++) {
		//連立1次方程式の係数行列aとbを作成する
		a[0][0] += pow(xk[i], 2);
		a[0][1] += xk[i];
		a[1][0] += xk[i];
		a[1][1] += 1;
		b[0] += xk[i] * yk[i];
		b[1] += yk[i];
	}

	cerr << endl << "Solve equations" << endl;
	cerr << a[0][0] << "\t" << a[0][1] << "\t" << b[0] <<endl;
	cerr << a[1][0] << "\t" << a[1][1] << "\t" << b[1] <<endl;

	forward();
	backward();

	cerr << "a = " << x[0] << endl;
	cerr << "b = " << x[1] << endl;

	//Eを計算して出力
}