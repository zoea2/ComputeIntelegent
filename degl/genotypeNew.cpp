#include <cstring>
#include <iostream>
#include "test_func.cpp"
using namespace std;
double ranval(double a,double b){
	return rand() % RAND_MAX * 1.0 / RAND_MAX * (b-a) + a; 
}
class Genotype{
public:

	const static int NVARS = 25;
	double PXOVER;
	const static double SCALE = 0.5;
	const static int LEVEL = 2;
	double gene[NVARS];
	double fitness;
	double upper[NVARS];
	double lower[NVARS];
	int lBest;
	double lBestFit;
	double orthBestFit;
	double orthgene[NVARS];
	int unupdate;
	Genotype(){
		lBestFit = INF;
		memset(gene,0,sizeof(gene));
		memset(upper,0,sizeof(upper));
		memset(lower,0,sizeof(lower));
		fitness = INF;
		unupdate = 0;
		PXOVER = ranval(0.1,0.9);
	}
	Genotype(Genotype &genotype){
		memcpy(this->gene,genotype.gene,sizeof(genotype.gene));	
		memcpy(this->upper,genotype.upper,sizeof(genotype.upper));
		memcpy(this->lower,genotype.lower,sizeof(genotype.lower));
		this->fitness = genotype.fitness;
		
	}
	~Genotype(){
	}
	void genCrRand(){
		PXOVER = ranval(0.1,0.9);
	}
	void genCrExp(int a,int b){
		PXOVER = exp(a * 1.0 / b * log(2)) - 1;
	}
	void genCrLin(int a,int b){
		PXOVER = a * 1.0 / b;
	}
};
