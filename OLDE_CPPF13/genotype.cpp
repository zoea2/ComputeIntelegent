#include <cstring>
#include <iostream>
#include "test_func.cpp"
using namespace std;
class Genotype{
public:
	const static int NVARS = 30;
	const static double PXOVER = 0.5;
	const static double SCALE = 0.9;
	const static int LEVEL = 2;
	double gene[NVARS];
	double fitness;
	double upper[NVARS];
	double lower[NVARS];
	Genotype(){
		memset(gene,0,sizeof(gene));
		memset(upper,0,sizeof(upper));
		memset(lower,0,sizeof(lower));
		fitness = INF;
	}
	Genotype(Genotype &genotype){
		memcpy(this->gene,genotype.gene,sizeof(genotype.gene));	
		memcpy(this->upper,genotype.upper,sizeof(genotype.upper));
		memcpy(this->lower,genotype.lower,sizeof(genotype.lower));
		this->fitness = genotype.fitness;
	}
	~Genotype(){
	}
};
