#include <iostream>
#include <vector>

#include <cstdlib> //rand()
#include "DiamantCarre.h"

using namespace std;

// interpolation linéaire
double interpolation(double a, double b, double t) {
	return ((1 - t) * a + t * b); 
}

double smooth_noise(int i, int j, vector<vector<float>>& t) {
	double a = t[i][j];
	double b = t[i][j + 1];
	double c = t[i + 1][j];
	srand(static_cast<unsigned int>(time(nullptr)));
	double x = static_cast<double>(rand()) / RAND_MAX;
	double y = interpolation(a, b, x); 
	return interpolation(y, c, x); 
}

void diamCarreLisse(vector<vector<float>>& t) {
	int s = t.size();
	for (int i = 0; i < s - 1; i++) {
		for (int j = 0; j < s - 1; j++) {
			smooth_noise(i, j, t);
		}
	}
}