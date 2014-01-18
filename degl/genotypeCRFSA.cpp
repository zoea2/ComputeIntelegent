#include <cstring>
#include <iostream>
#include "test_func.cpp"
using namespace std;
double ranval(double a,double b){
	return rand() % RAND_MAX * 1.0 / RAND_MAX * (b-a) + a; 
}
class Genotype{
public:
	int orthcount;
	const static int NVARS = 25;
	double nextPXOVER;
	double PXOVER;
	double SCALE;
	const static int LEVEL = 2;
	double gene[NVARS+3];
	double fitness;
	double upper[NVARS+3];
	double lower[NVARS+3];
	int lBest;
	double lBestFit;
	double orthBestFit;
	double orthgene[NVARS+3];
	int unupdate;
	double updateRate;
	Genotype(){
		updateRate = 0;
		lBestFit = INF;
		memset(gene,0,sizeof(gene));
		memset(upper,0,sizeof(upper));
		memset(lower,0,sizeof(lower));
		fitness = INF;
		unupdate = 0;
		PXOVER = ranval(0,1);
		nextPXOVER = PXOVER;
		SCALE = ranval(0,1);
		orthcount = 5;
	}
	Genotype(Genotype &genotype){
		memcpy(this->gene,genotype.gene,sizeof(genotype.gene));	
		memcpy(this->upper,genotype.upper,sizeof(genotype.upper));
		memcpy(this->lower,genotype.lower,sizeof(genotype.lower));
		memcpy(this->orthgene,genotype.orthgene,sizeof(genotype.orthgene));
		this->lBest = genotype.lBest;
		this->lBestFit = genotype.lBestFit;
		this->orthBestFit = genotype.orthBestFit;
		this->fitness = genotype.fitness;		
		this->unupdate = genotype.unupdate;
		this->PXOVER = genotype.PXOVER;
		this->nextPXOVER = genotype.nextPXOVER;
		this->SCALE = genotype.SCALE;
		this->orthcount = genotype.orthcount;
		this->updateRate = genotype.updateRate;
	}
	~Genotype(){
	}
	void genCrRand(){
		PXOVER = ranval(0.1,0.9);
	}
	void genCrExp(int a,int b){
		PXOVER = exp(a / b * log(2)) - 1;
	}
	void genCrLin(int a,int b){
		PXOVER = a * 1.0 / b;
	
	}

};

