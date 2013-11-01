#include "genotype.cpp"
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctype.h>
#include <cstdio>
#include <fstream>
using namespace std;
const int POPSIZE = 50;
const int funcEvaluate = 300000;
const int row = (int)(pow(2.0,ceil(log(Genotype::NVARS) / log(2))));
const int col = row - 1;
int **oArray;
double MTurn[Genotype::NVARS+1][Genotype::NVARS+1];
double MResult[Genotype::NVARS+1][Genotype::NVARS+1];
double Rosenbrock[Genotype::NVARS+1];
double Rastrigin[Genotype::NVARS+1];
int feNumber;
int f;
Genotype best;
Genotype bestA;
Genotype population[POPSIZE+1];
Genotype MidPop[POPSIZE+1];
double ranval(){
	return rand() * 1.0 / RAND_MAX; 
}
void init(){
	double lbound = -100;
	double ubound = 100;
	//string filename = "/home/ryan/testdata/bound";
	char temp[100];
//	cout<<"ff "<<f<<endl;
//	sprintf(temp,"/home/ryan/testdata/bound%d.txt",f);
//	cout<<temp<<endl;
//	ifstream input;
//	input.open(temp);
//	input>>lbound>>ubound;
//	input.close();
	for(int i = 0;i < Genotype::NVARS;i++){
		for(int j = 1;j <= POPSIZE;j++){
			population[j].fitness = 0;
			population[j].lower[i] = lbound;
			population[j].upper[i] = ubound;
			MidPop[j].lower[i] = lbound;
			MidPop[j].upper[i] = ubound;
			population[j].gene[i] = ranval() * (population[j].upper[i] - population[j].lower[i])
				+ population[j].lower[i];
		}
	}
}
/*
double funcU(double x,int a,int k,int m){
	if(x > a)
		return (double)(k * pow(x-a,m));
	else if(x <= a && x >= -a)
		return 0;
	else
		return (double)(k * pow(-x-a,m));
}
void setME(double ME[][Genotype::NVARS+1]){
	for(int i = 0;i < Genotype::NVARS;i++){
		for(int j = 0;j < Genotype::NVARS; j++){
			if (i == j)
				ME[i][j] = 1;
			else
				ME[i][j] = 0;
		}
	}
}
void MulMatrix(){
	double temp[Genotype::NVARS][Genotype::NVARS];
	for(int i = 0;i < Genotype::NVARS;i++){
		for(int j = 0;j < Genotype::NVARS;j++){
			temp[i][j] = 0;
			for(int k = 0;k < Genotype::NVARS;k++)
				temp[i][j] += MResult[i][k] * MTurn[k][j];
		}
	}
	memcpy(&MResult,&temp,sizeof(temp));
}
void MRot(int i,int j){
	setME(MTurn);
	double alpha = (ranval() - 0.5) * PI * 0.5; 
	MTurn[i][i] = cos(alpha);
	MTurn[j][j] = cos(alpha);
	MTurn[i][j] = sin(alpha);
	MTurn[j][i] = -sin(alpha);
}
*/
void select(){
	for(int i = 1;i <= POPSIZE;i++){
		if(MidPop[i].fitness < population[i].fitness){
			population[i] = Genotype(MidPop[i]);
		}
	}
}
bool keepTheBest(){
	double bestf;
	int index;
	bestf = population[1].fitness;
	index = 1;
	for(int i = 1;i <= POPSIZE;i++){
		if(bestf > population[i].fitness){
			bestf = population[i].fitness;
			index = i;
		}
	}
	best = Genotype(population[index]);
	if(bestA.fitness > best.fitness){
		bestA = Genotype(best);
		return true;
	}
	else
		return false;
}
void mutate_rand_1(){
	for(int i = 1;i <= POPSIZE;i++){
		int ran1 = (int)(POPSIZE * ranval() + 1);
		while(ran1 == i)
			ran1 = (int)(POPSIZE * ranval() + 1);
		Genotype temp1(population[ran1]);
		int ran2 = (int)(POPSIZE * ranval() + 1);
		while(ran2 == ran1 || ran2 == i)
			ran2 = (int)(POPSIZE * ranval() + 1);
		Genotype temp2(population[ran2]);
		int ran3 = (int)(POPSIZE * ranval() + 1);
		while(ran3 == ran1 || ran3 == ran2 || ran3 == i)
			ran3 = (int)(POPSIZE * ranval() + 1);
		for(int j = 0;j < Genotype::NVARS;j++){
			MidPop[i].gene[j] = population[ran3].gene[j] + Genotype::SCALE * 
				(temp1.gene[j] - temp2.gene[j]);
			if(MidPop[i].gene[j] < MidPop[i].lower[j] || MidPop[i].gene[j] > MidPop[i].upper[j])
				MidPop[i].gene[j] = ranval() * (MidPop[i].upper[j] - MidPop[i].lower[j])
					+ MidPop[i].lower[j];
		}
	}
}
void cross(){
	for(int i = 1;i <= POPSIZE;i++){
		int jrand = (int)((ranval() * Genotype::NVARS));
		for(int j = 0;j < Genotype::NVARS;j++){
			if(ranval() > Genotype::PXOVER && j != jrand){
				MidPop[i].gene[j] = population[i].gene[j];
			}
		}
	}
}
void creatOA(){
	oArray = new int *[row+1];
	for(int i = 0;i <= row ;i++){
		oArray[i] = new int[col+1];
	}
	int u = (int)(log(row) / log (2));
	for(int i = 1;i <= row;i++){
		for(int k = 1;k <= u;k++){
			int j = (int)pow(2,k-1);
			oArray[i][j] = (int)(floor((i-1) / pow(2,u-k))) % 2;
		}
	}
	for(int i = 1; i<= row;i++){
		for(int k = 2;k <= u;k++){
			int j = (int)(pow(2,k-1));
			for(int s = 1;s <= j-1;s++){
				oArray[i][j+s] = (oArray[i][s] + oArray[i][j]) % 2;
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
void orthCross(){
	double *ans;
	ans = new double[2];
	for(int p = 1;p <= POPSIZE;p++){
		Genotype temp[row + 2];
		for(int i = 1;i <= row;i++){
			for(int j = 1;j <= Genotype::NVARS;j++){
				if(oArray[i][j] == 1)
					temp[i].gene[j-1] = population[p].gene[j-1];
				else
					temp[i].gene[j-1] = MidPop[p].gene[j-1];
			}
			test_func(temp[i].gene,ans,Genotype::NVARS,1,f);
			temp[i].fitness = ans[0];
			feNumber++;
		}
		double tempfit[Genotype::NVARS+1][Genotype::LEVEL+1];
		Genotype ctemp;
		for(int i = 1;i <= Genotype::NVARS;i++){
			double min = -1;
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
			if(index == 1)
				ctemp.gene[i-1] = population[p].gene[i-1];
		}
		test_func(ctemp.gene,ans,Genotype::NVARS,1,f);
		ctemp.fitness = ans[0];
		if(MidPop[p].fitness > ctemp.fitness)
			memcpy(MidPop[p].gene,ctemp.gene,sizeof(ctemp.gene));
	}
}
int main(){
	srand(time(0));
	creatOA();
	cout <<Genotype::NVARS<<endl;
	double globalbest[29];
	for(int i = 1;i <= 28;i++){
		globalbest[i] = -1400 + (i-1) * 100;
		if(i == 15)
			globalbest[i] += 100;
	}
	double* x;
	for(f = 1;f <= 28;f++){
		for(int t = 0;t < 51;t++){
			bestA.fitness = INF;
			init();
		/*	for(int i = 1;i <= POPSIZE;i++){
				for(int j = 0;j < Genotype::NVARS;j++){
					cout<<population[i].gene[j]<<endl;
				}
			}*/
		//	system("pause");
			char filename[100];
			sprintf(filename,"/home/ryan/testdata/outputc%dthe%dtimes.txt",f,t);
			ofstream output(filename);
			bool isEnd = false;
			feNumber = 0;
			double *di = new double[2];
			for(int i = 1;i <= POPSIZE;i++){
				//for(int j = 0;ij < Genotype::NVARS;j++)
				//	cout<<population[i].gene[j]<<endl;
				test_func(population[i].gene,di,Genotype::NVARS,1,f);
				population[i].fitness = di[0];
				feNumber++;
				//cout<<population[i].fitness<<endl;
			}		
			keepTheBest();
			while(feNumber < funcEvaluate){
				if(isEnd)
					break;
				//cout<<feNumber<<endl;
				mutate_rand_1();
				//for(int j = 0;j < Genotype::NVARS;j++)
				//	cout<<"MID "<<MidPop[2].gene[j]<<endl;
				cross();
				for(int i = 1;i <= POPSIZE;i++){
					test_func(population[i].gene,di,Genotype::NVARS,1,f);
					population[i].fitness = di[0];
					test_func(MidPop[i].gene,di,Genotype::NVARS,1,f);
					MidPop[i].fitness = di[0];
					feNumber+=2;
					if(feNumber == 0.01 * funcEvaluate || feNumber == 0.1 * funcEvaluate 
							|| feNumber == 0.2 * funcEvaluate || feNumber == 0.3 * funcEvaluate
							|| feNumber == 0.4 * funcEvaluate || feNumber == 0.5 * funcEvaluate
							|| feNumber == 0.6 * funcEvaluate || feNumber == 0.7 * funcEvaluate
							|| feNumber == 0.8 * funcEvaluate || feNumber == 0.9 * funcEvaluate
							|| feNumber == funcEvaluate){
						output<<"FES = "<<feNumber<<endl;
						output<<"best :"<<bestA.fitness<<"  error value :"
							<< bestA.fitness - globalbest[f]<<endl;
						if(feNumber == funcEvaluate || bestA.fitness - globalbest[f] < 
								0.00000001){
							isEnd = true;
							break;
						}
					}
				}			
				select();
				keepTheBest();
				if(bestA.fitness - globalbest[f] < 0.00000001)
					break;
			}
			cout<<"function "<<f<<" times "<<t<<" done!"<<endl;
			output<<"The total FES is "<<feNumber<<endl;
			output<<"error value is "<<bestA.fitness - globalbest[f]<<endl;
			output<<"best: "<<bestA.fitness<<endl;
			for(int j = 0;j < Genotype::NVARS;j++)
				output<<bestA.gene[j]<<endl;
			output.close();
		}
		cout<<"function "<<f<<" done!"<<endl;
	}
}
