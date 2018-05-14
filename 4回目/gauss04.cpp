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

void backward() {
	//逆進代入
	for (int i = n - 1; i >= 0; i--) {
		x[i] = b[i] / a[i][i];

		for (int j = 0; j < i; j++) {
			b[j] -= a[j][i] * x[i];
		}
	}
}

void gauss() {
	for (int i = 0; i < n; i++) {
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