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
bool isEnd;
double globalbest[29];
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
double lbound ;
double ubound ;

ifstream datainput;
ofstream output;
Genotype best;
Genotype bestA;
Genotype population[POPSIZE+1];
Genotype MidPop[POPSIZE+1];
double ranval(){
	return rand() % RAND_MAX * 1.0 / RAND_MAX; 
}
void printResult(){
	if(feNumber == 0.01 * funcEvaluate || feNumber == 0.1 * funcEvaluate 
		|| feNumber == 0.2 * funcEvaluate || feNumber == 0.3 * funcEvaluate
		|| feNumber == 0.4 * funcEvaluate || feNumber == 0.5 * funcEvaluate
		|| feNumber == 0.6 * funcEvaluate || feNumber == 0.7 * funcEvaluate
		|| feNumber == 0.8 * funcEvaluate || feNumber == 0.9 * funcEvaluate
		|| feNumber == funcEvaluate){
//			output<<"FES = "<<feNumber<<endl;
//			output<<"best :"<<bestA.fitness<<"  error value :"
//				<< bestA.fitness - globalbest[f]<<endl;
			if(feNumber == funcEvaluate || abs(bestA.fitness - globalbest[f]) < 
				0.00000001){
					isEnd = true;
			}
	}		
}
void init(){
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
			MidPop[j].fitness = INF;
		}
	}
}
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
void mutate_best_1(){
	for(int p = 1;p <= POPSIZE;p++){
		int ran1 = (int)(floor)(POPSIZE * ranval() + 1);
		while(ran1 == p)
			ran1 = (int)(floor)(POPSIZE * ranval() + 1);
		Genotype temp1(population[ran1]);
		int ran2 = (int)(floor)(POPSIZE * ranval() + 1);
		while(ran2 == ran1 || ran2 == p)
			ran2 = (int)(floor)(POPSIZE * ranval() + 1);
		Genotype temp2(population[ran2]);
		for(int i = 0; i < Genotype::NVARS;i++){
			MidPop[p].gene[i] = bestA.gene[i] + Genotype::SCALE * (temp1.gene[i] - temp2.gene[i]);
			if(MidPop[p].gene[i] < MidPop[p].lower[i] || MidPop[p].gene[i] > MidPop[p].upper[i])
				MidPop[p].gene[i] = ranval() * (MidPop[p].upper[i] - MidPop[p].lower[i]) + MidPop[p].lower[i];
		}
	}
	
}
void orthMutate_best_1(){
	double *ans;
	ans = new double[2];
	for(int p = 1;p <= POPSIZE;p++){
		int ran1 = (int)floor(POPSIZE * ranval() + 1);
		while(ran1 == p)
			ran1 = (int)floor(POPSIZE * ranval() + 1);
		Genotype temp1(population[ran1]);
		int ran2 = (int)floor(POPSIZE * ranval() + 1);
		while (ran2 == ran1 || ran2 == p)
			ran2 = (int)floor(POPSIZE * ranval() + 1);
		Genotype temp2(population[ran2]);
		int ran3 = (int)floor(POPSIZE * ranval() + 1);
		while(ran3 == ran1 || ran3 == ran2 || ran3 == p)
			ran3 = (int)floor(POPSIZE * ranval() + 1);
		Genotype temp[row + 2];
		for(int i = 1;i <= row;i++){
			for(int j = 1;j <= Genotype::NVARS;j++){
				if(oArray[i][j] == 1)
					temp[i].gene[j-1] = population[p].gene[j-1];
				else
					temp[i].gene[j-1] = population[p].gene[j-1];
			}
			test_func(temp[i].gene,ans,Genotype::NVARS,1,f);
			temp[i].fitness = ans[0];
			feNumber++;
			printResult();
		}
		double tempfit[Genotype::NVARS+1][Genotype::LEVEL+1];
		Genotype ctemp;
		for(int i = 1;i <= Genotype::NVARS;i++){
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
				ctemp.gene[i-1] = population[ran3].gene[i-1];
			else
				ctemp.gene[i-1] = best.gene[i-1];
		}
		test_func(ctemp.gene,ans,Genotype::NVARS,1,f);
		ctemp.fitness = ans[0];
		feNumber++;
		printResult();
		if(best.fitness > ctemp.fitness){
			for(int j = 0;j < Genotype::NVARS;j++){
				MidPop[p].gene[j] = ctemp.gene[j] + Genotype::SCALE * 
									(temp1.gene[j] - temp2.gene[j]);
				if(MidPop[p].gene[j] < MidPop[p].lower[j]
						|| MidPop[p].gene[j] > MidPop[p].upper[j]){
					MidPop[p].gene[j] = ranval() * (MidPop[p].upper[j] - MidPop[p].lower[j])
						+ MidPop[p].lower[j];
				test_func(MidPop[p].gene,ans,Genotype::NVARS,1,f);
				feNumber++;
				printResult();
				}
			}
		}
		else{
			for(int j = 0;j < Genotype::NVARS;j++){
				MidPop[p].gene[j] = best.gene[j] + Genotype::SCALE * 
									(temp1.gene[j] - temp2.gene[j]);
				if(MidPop[p].gene[j] < MidPop[p].lower[j]
						|| MidPop[p].gene[j] > MidPop[p].upper[j]){
					MidPop[p].gene[j] = ranval() * (MidPop[p].upper[j] - MidPop[p].lower[j])
						+ MidPop[p].lower[j];
				}
			}
	
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
			printResult();
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
			else
				ctemp.gene[i-1] = MidPop[p].gene[i-1];
		}
		test_func(ctemp.gene,ans,Genotype::NVARS,1,f);
		ctemp.fitness = ans[0];
		feNumber++;
		printResult();
		if(MidPop[p].fitness > ctemp.fitness){
			memcpy(MidPop[p].gene,ctemp.gene,sizeof(ctemp.gene));
			MidPop[p].fitness = ctemp.fitness;
		}
	}
}
int main(){
	srand(time(0));
	creatOA();
	datainput.open("inputdata.txt");

	cout <<Genotype::NVARS<<endl;
	for(int i = 1;i <= 13;i++){
		if(i == 8)
			globalbest[i] = -12569.5;
		else
			globalbest[i] = 0;
	}
	double* x;
	for(f = 1;f <= 13;f++){
		char filename[100];
	datainput>>lbound>>ubound;
		sprintf(filename,"/home/ryan/testdataNew/data_Scale%.1lf/OMBC2013WC%.1lf/outputc%d.txt",Genotype::SCALE,Genotype::PXOVER,f);
		output.open(filename);
		for(int t = 0;t < 51;t++){
			//cout<<"fuck"<<endl;
			output<<"times "<<t<<endl;
			//cout<<"fuck again"<<endl;
			bestA.fitness = INF;
			init();
		/*	for(int i = 1;i <= POPSIZE;i++){
				for(int j = 0;j < Genotype::NVARS;j++){
					cout<<population[i].gene[j]<<endl;
				}
			}*/
		//	system("pause");
			isEnd = false;
			feNumber = 0;
			double *di = new double[2];
			for(int i = 1;i <= POPSIZE;i++){
				test_func(population[i].gene,di,Genotype::NVARS,1,f);
				population[i].fitness = di[0];
				feNumber++;
				printResult();
			}		
			keepTheBest();
			int count = 0;
			bool isOr = false;
			while(feNumber < funcEvaluate){
				if(isEnd)
					break;
				if(!isOr){

					mutate_best_1();
			//		cross();
				}
				else{

					orthMutate_best_1();
			//		orthCross();
				}
				
				cross();
		
				select();
			//	keepTheBest();
				
				if(keepTheBest()){
					count = 0;
					isOr = false;
				}
				else{
					count++;
					if(count >= 5)
						isOr = true;
				}
			
				if(abs(bestA.fitness - globalbest[f]) < 0.00000001)
					break;
			}
			cout<<"function "<<f<<" times "<<t<<" done!"<<endl;
			output<<"The total FES is "<<feNumber<<endl;
			output<<"error value is "<<bestA.fitness - globalbest[f]<<endl;
			output<<"best: "<<bestA.fitness<<endl;
			for(int j = 0;j < Genotype::NVARS;j++)
				output<<bestA.gene[j]<<endl;
		}
		cout<<"function "<<f<<" done!"<<endl;
		output.close();


	}
		datainput.close();
}

