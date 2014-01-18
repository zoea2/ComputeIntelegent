#include "genotypeCRSA.cpp"
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctype.h>
#include <cstdio>
#include <fstream>
#include <assert.h>
using namespace std;
bool isEnd;
double globalbest[29];
const int POPSIZE = 50;
const int NEIBORHOOD = 0.1 * POPSIZE;
const int funcEvaluate = 500000;
const int row = (int)(pow(2.0,ceil(log(Genotype::NVARS) / log(2))));
const int col = row - 1;
int **oArray;
double MTurn[Genotype::NVARS+1][Genotype::NVARS+1];
double MResult[Genotype::NVARS+1][Genotype::NVARS+1];
double Rosenbrock[Genotype::NVARS+1];
double Rastrigin[Genotype::NVARS+1];
int feNumber;
int f;
int bestIdx;
double updateRate = 0;
ofstream output;
Genotype bestA;
Genotype population[POPSIZE+1];
Genotype MidPop[POPSIZE+1];
ifstream datainput;
double lbound;
double ubound;
double *ans;
void printResult(){
	if(feNumber == 0.01 * funcEvaluate || feNumber == 0.1 * funcEvaluate 
		|| feNumber == 0.2 * funcEvaluate || feNumber == 0.3 * funcEvaluate
		|| feNumber == 0.4 * funcEvaluate || feNumber == 0.5 * funcEvaluate
		|| feNumber == 0.6 * funcEvaluate || feNumber == 0.7 * funcEvaluate
		|| feNumber == 0.8 * funcEvaluate || feNumber == 0.9 * funcEvaluate
		|| feNumber == funcEvaluate){
			if(feNumber == funcEvaluate || abs(bestA.fitness - globalbest[f]) < 
				0.00000001){
					isEnd = true;
			}
	}		
}
void init(){
	char temp[100];
	for(int i = 1;i <= POPSIZE;i++){
		for(int j = 0;j < Genotype::NVARS;j++){
			if(j < Genotype::NVARS){
				population[i].lower[j] = lbound;
				population[i].upper[j] = ubound;
				MidPop[i].lower[j] = lbound;
				MidPop[i].upper[j] = ubound;
		
			}
			else if (j == Genotype::NVARS){
				population[i].lower[j] = 0.1;
				population[i].upper[j] = 0.9;
				MidPop[i].lower[j] = 0.1;
				MidPop[i].upper[j] = 0.9;
				
			}
			population[i].gene[j] = ranval(population[i].lower[j],population[i].upper[j]);
			population[i].orthgene[j] = population[i].gene[j];
		}
		test_func(population[i].gene,ans,Genotype::NVARS,1,f);
		population[i].fitness = ans[0];
		feNumber++;
		population[i].lBestFit = population[i].fitness;
		population[i].lBest = i;
		population[i].orthBestFit = population[i].fitness;
		memcpy(population[i].orthgene,population[i].gene,sizeof(population[i].gene));
		if(i == 1){
			bestA = Genotype(population[i]);
			bestIdx = i;
		}
		else if(population[i].fitness < bestA.fitness){
			bestA = Genotype(population[i]);
			bestIdx = i;
		}
		assert(population[i].lBest >= 1 && population[i].lBest <= POPSIZE);			
	}
}
void select(){
	for(int i = 1;i <= POPSIZE;i++){
		if(MidPop[i].fitness < population[i].fitness){
			//population[i] = Genotype(MidPop[i]);
			for(int j = 0;j < Genotype::NVARS;j++){
				population[i].gene[j] = MidPop[i].gene[j];
			}
	//		if((population[i].fitness != 0) && abs((MidPop[i].fitness - population[i].fitness) / population[i].fitness) > updateRate)
	//			population[i].gene[Genotype::NVARS] = MidPop[i].gene[Genotype::NVARS];
			population[i].PXOVER = population[i].nextPXOVER;
			population[i].fitness = MidPop[i].fitness;
			population[i].unupdate = 0;
			if(population[i].fitness < bestA.fitness){
				memcpy(bestA.gene,population[i].gene,sizeof(population[i].gene));
				bestA.fitness = population[i].fitness;
				bestIdx = i;
				bestA.PXOVER = population[i].PXOVER;
				bestA.nextPXOVER = population[i].nextPXOVER;
			}
			if(population[i].fitness <= population[population[i].lBest].fitness){
				population[i].lBest = i;
				population[i].lBestFit = population[i].fitness;
			}
			int index = (i - 2 + POPSIZE) % POPSIZE;
			for(int j = 0;j < 2;j++){
				if(index == 0){
					if(population[i].fitness < population[POPSIZE].fitness){
						population[POPSIZE].lBestFit = population[i].fitness;
						population[POPSIZE].lBest = i;
					}
				}	
				else{
					if(population[i].fitness < population[index].lBestFit){
						population[index].lBestFit = population[i].fitness;
						population[index].lBest = i;
					}
				}
				index++;
			}
			index = (i + 1 + POPSIZE) % POPSIZE;
			for(int j = 0;j < 2;j++){
				if(index == 0){
					if(population[i].fitness < population[POPSIZE].fitness){
						population[POPSIZE].lBestFit = population[i].fitness;
						population[POPSIZE].lBest = i;
					}
				}
				else{
					if(population[i].fitness < population[index].lBestFit){
						population[index].lBestFit = population[i].fitness;
						population[index].lBest = i;
					}
				}
				index++;
			}		
			assert(population[i].lBest >= 1 && population[i].lBest <= POPSIZE);			
		}	
		else{
			population[i].unupdate++;
			population[i].nextPXOVER = population[i].PXOVER;
			//population[i].gene[Genotype::NVARS] = MidPop[i].gene[Genotype::NVARS];
		}
	}
}

void orthMutate_LGNB(){
	for(int p = 1;p <= POPSIZE;p++){
		if(population[p].unupdate >= 10 && population[p].lBest != bestIdx)
		{
			population[p].unupdate = 0;
			Genotype temp[row + 2];
			for(int i = 1;i <= row;i++){
				assert(i >= 1 && i <= row);
				for(int j = 1;j < Genotype::NVARS+1;j++){
					assert(j >= 1 && j <= Genotype::NVARS+1);
					if(oArray[i][j] == 1)
						temp[i].gene[j-1] = bestA.gene[j-1];
					else
						temp[i].gene[j-1] = population[population[p].lBest].gene[j-1];
				}
				test_func(temp[i].gene,ans,Genotype::NVARS,1,f);
				temp[i].fitness = ans[0];
				feNumber++;
			}
			double tempfit[Genotype::NVARS+2][Genotype::LEVEL+1];
			Genotype ctemp;
			for(int i = 1;i < Genotype::NVARS+1;i++){
				double min = 1;
				int index = -1;
				for(int j = 0;j < Genotype::LEVEL;j++){
					tempfit[i][j] = 0;
					int count = 0;
					for(int k = 1;k <= row;k++){
						if(oArray[k][i] == j){
							tempfit[i][j] += temp[k].fitness;
							count++;
						}
					}
					tempfit[i][j] /= count;
					if(index == -1){
						min = tempfit[i][j];
						index = j;
					}
					else if(min > tempfit[i][j]){
						min = tempfit[i][j];
						index = j;
					}
				}
				if (index == 1)
					ctemp.gene[i-1] = bestA.gene[i-1];
				else
					ctemp.gene[i-1] = population[population[p].lBest].gene[i-1];
			}
			test_func(ctemp.gene,ans,Genotype::NVARS,1,f);
			ctemp.fitness = ans[0];
			feNumber++;
			if(ctemp.fitness <= population[p].orthBestFit){
				memcpy(population[p].orthgene,ctemp.gene,sizeof(ctemp.gene));
				population[p].orthBestFit = ctemp.fitness;
			}
		}
		else if(population[p].unupdate >= 10 && bestIdx == population[p].lBest){
			population[p].unupdate = 0;
			memcpy(population[p].orthgene,bestA.gene,sizeof(bestA.gene));
			population[p].orthBestFit = bestA.fitness;
		}
		int ran1 = (int)floor(ranval(0,POPSIZE) + 1);
		while(ran1 == p)
			ran1 = (int)floor(ranval(0,POPSIZE) + 1);
		Genotype temp1(population[ran1]);
		int ran2 = (int)floor(ranval(0,POPSIZE) + 1);
		while (ran2 == ran1 || ran2 == p)
			ran2 = (int)floor( ranval(0,POPSIZE) + 1);
		Genotype temp2(population[ran2]);
		for(int j = 0;j < Genotype::NVARS;j++){
			MidPop[p].gene[j] = population[p].gene[j] + Genotype::SCALE * (population[p].orthgene[j] - population[p].gene[j])
										+ Genotype::SCALE * (temp1.gene[j] - temp2.gene[j]);
			if(MidPop[p].gene[j] < MidPop[p].lower[j]
					|| MidPop[p].gene[j] > MidPop[p].upper[j]){
				MidPop[p].gene[j] = ranval(MidPop[p].lower[j],MidPop[p].upper[j]); 
			}
		}
		
	}
}	
void cross(){
	for(int i = 1;i <= POPSIZE;i++){
		int jrand = (int)ranval(0,Genotype::NVARS+1);
		assert(jrand >= 0 && jrand <= Genotype::NVARS);
		//assert(MidPop[i].gene[Genotype::NVARS] != population[i].gene[Genotype::NVARS]);
		if(ranval(0,1) < 0.1)
			population[i].nextPXOVER = ranval(0,1);
		for(int j = 0;j < Genotype::NVARS;j++){
			if(ranval(0,1) > population[i].nextPXOVER && j != jrand){
				MidPop[i].gene[j] = population[i].gene[j];
			}
		}
		test_func(MidPop[i].gene,ans,Genotype::NVARS,1,f);
		MidPop[i].fitness = ans[0];
		feNumber++;
	}
}
void creatOA(){
	oArray = new int *[row+1];
	for(int i = 0;i <= row ;i++){
		oArray[i] = new int[col+1];
	}
	double u = log(row) / log (2);
	cout<<"u"<<u<<endl;
	for(int i = 1;i <= row;i++){
		for(int k = 1;k <= u;k++){
			int j = (int)pow(2,k-1);
			oArray[i][j] = (int)(floor((i-1) / pow(2,u-k))) % 2;
		}
	}
	for(int i = 1; i<= row;i++){
		for(int k = 2;k <= u;k++){
			int j = (int)(pow(2.0,k-1));
			for(int s = 1;s <= j-1;s++){
				oArray[i][j+s] = (oArray[i][s] + oArray[i][j]) % 2;
				cout<<i<<" "<<j+s<<" "<<oArray[i][j+s]<<endl;
			}
		}
	}
	for(int i = 1;i <= row;i++){
		for(int j = 1;j <= col;j++){
			cout<<oArray[i][j]<<" ";
		}
		cout<<endl;
	}
}
int main(){
	srand(time(0));
	creatOA();
	ans = new double[2];
	datainput.open("inputdata.txt");
	cout <<Genotype::NVARS<<endl;
	for(int i = 1;i <= 13;i++){
		if(i == 8)
			globalbest[i] = -12569.5;
		globalbest[i] = 0;	
	}
	double* x;
	for(f = 5;f <= 5;f++){
		char filename[100];
		sprintf(filename,"/home/ryan/testdataNN/data_Scale%.1lf/MBC2013SACrR/outputc%d.txt",Genotype::SCALE,f);
		cout<<filename<<endl;
		output.open(filename);
		datainput>>lbound>>ubound;
		cout<<lbound<<" "<<ubound<<endl;
		for(int t = 0;t < 51;t++){
			output<<"times "<<t<<endl;
			bestA.fitness = INF;
			init();
			isEnd = false;
			feNumber = 0;
			int gen = 0;		
			while(feNumber < funcEvaluate){
				if(isEnd)
					break;
				orthMutate_LGNB();
				cross();
				select();
	//			if(abs(bestA.fitness - globalbest[f]) < 0.00000001)
	//				break;
				gen++;
			}
			cout<<"function "<<f<<" times "<<t<<" done!"<<endl;
			output<<"gen"<<gen<<endl;
			output<<"The total FES is "<<feNumber<<endl;
			output<<"error value is "<<bestA.fitness - globalbest[f]<<endl;
			output<<"best: "<<bestA.fitness<<endl;
			for(int j = 0;j < Genotype::NVARS;j++)
				output<<bestA.gene[j]<<endl;
			output<<bestA.nextPXOVER<<endl;
		}
		cout<<"function "<<f<<" done!"<<endl;
		output.close();


	}

		datainput.close();
}

