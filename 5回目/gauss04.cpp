#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

const int n = 3;
double a[n][n], b[n], x[n];

void display() {
	cerr << "<<<<<< display a >>>>>>" << endl;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cerr << a[i][j] << "\t";
		}

		cerr << b[i] << endl;
	}
}

//s行目以降で，s列目が最大となる行を探し，s行と入れ替える
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

//逆進代入
void backward() {
	for (int i = n - 1; i >= 0; i--) {
		x[i] = b[i] / a[i][i];

		for (int j = 0; j < i; j++) {
			b[j] -= a[j][i] * x[i];
		}
	}
}

void gauss() {
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

int main() {
	cerr << "n" << endl;
	//cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cerr << "input a[" << i << "][" << j << "]" << endl;
			cin >> a[i][j];
		}

		cerr << "input b[" << i << "]" << endl;
		cin >> b[i];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cerr << a[i][j] << "\t";
		}

		cerr << b[i] << endl;
	}

	gauss();
	backward();

	for (int i = 0; i < n; i++) {
		cerr << x[i] << endl; 
	}

}