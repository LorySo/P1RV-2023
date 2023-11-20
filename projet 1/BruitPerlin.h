#ifndef BruitPerlin_h
#define BruitPerlin_h
#include <iostream>
#include <vector>

double interpolation(double a, double b, double t);
double smooth_noise(int i, int j, vector<vector<float>>& t); 
void diamCarreLisse(vector<vector<float>>& t); 
#endif