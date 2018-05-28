#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

const int NMAX = 10;
double a[NMAX][NMAX], b[NMAX], x[NMAX];		//連立方程式用の配列
int n = 0;									//次数

/*void display() {
	cerr << "<<<<<< display a,b >>>>>>" << endl;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cerr << a[i][j] << "\t";
		}

		cerr << b[i] << endl;
	}
}*/

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

	//display();
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

		//display();
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
	int nData = 0;
	cin >> n >> nData;
	double xk[nData], yk[nData];

	for (int i = 0; i < nData; i++) {
		cerr << "input xk[" << i << "]\tyk[" << i << "]" << endl;
		cin >> xk[i] >> yk[i];
		cerr << xk[i] << "\t" << yk[i] << endl;
	}

	n++;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			a[i][j] = 0.0;
		}

		x[i] = 0.0;
		b[i] = 0.0;
	}

	for (int i = 0; i < nData; i++) {
		//連立1次方程式の係数行列a,bの計算
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				a[j][k] += pow(xk[i], j + k);
			}

			b[j] += pow(xk[i], j) * yk[i];
		}
	}

	cerr << endl << "Solve equations" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cerr << a[i][j] << "\t";
		}

		cerr << b[i] << endl;
	}

	forward();
	backward();

	for (int i = 0; i < n; i++) {
		cerr << "a" << i << " = " << x[i] << endl;
	}

	//Eを計算して出力
}