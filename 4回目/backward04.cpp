#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

const int n = 4;
double a[n][n], b[n], x[n];

void backward() {
	//逆進代入
	for (int i = n - 1; i >= 0; i--) {
		x[i] = b[i] / a[i][i];

		for (int j = 0; j < i; j++) {
			b[j] -= a[j][i] * x[i];
		}
	}
}

int main() {
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

	backward();

	for (int i = 0; i < n; i++) {
		cerr << x[i] << endl; 
	}
}