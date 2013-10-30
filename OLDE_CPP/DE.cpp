#include "genotype.cpp"
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
const int POPSIZE = 50;
const int funcEvaluate = 300000;
int feNumber;
int f;
Genotype best;
Genotype bestA;
int oArray[][];
int row;
double MTurn[Genotype.NVARS+1][Genotype.NVARS];
double MResult[Genotype.NVARS+1][Genotype.NVARS+1];
double Rosenbrock[Genotype.NVARS+1];
double Rastrigin[Genotype.NVARS+1];
void init(){
	double lbound;
	double ubound;
	string filename = "/home/ryan/testdata/bound";
	filename.append(1,'0'+f);
	filename.append(".txt");
}


int main(){
}
