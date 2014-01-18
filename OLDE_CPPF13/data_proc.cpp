#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;
void process(string dirname){
	string temp1 = dirname;
	temp1.append("result.txt");
	ofstream output(temp1.c_str());
	output<<"max\tmin\tmean\tstarf"<<endl;
	for(int i = 1;i <= 13;i++){
		char filename[100];
		string temp = dirname;
		temp.append("outputc%d.txt");
		sprintf(filename,temp.c_str(),i);
		cout<<filename<<endl;
		ifstream input(filename);
		double maxFitness,minFitness,meanFitness,starf;
		double fitness[52];
		meanFitness = 0;
		for(int j = 0;j <= 50;j++){
			string s;
			for(int k = 0;k < 3;k++)
				getline(input,s);
			input>>s>>fitness[j];
			if(j == 0){
				maxFitness = fitness[j];
				minFitness = fitness[j];
			}
			else{
				if(maxFitness < fitness[j])
					maxFitness = fitness[j];
				if(minFitness > fitness[j])
					minFitness = fitness[j];
			}
			meanFitness += fitness[j];
			//cout<<fitness[j]<<endl;
			for(int k = 0;k < 31;k++){
				getline(input,s);
			//	cout<<s<<endl;
			}
		
		}
		input.close();
		meanFitness /= 51;
		starf = 0;
		for(int j = 0;j <= 50;j++){
		//double temp = 0;
			starf += pow(fitness[j] - meanFitness,2);
		}
		starf /= 51;
		starf = sqrt(starf);
		output<<maxFitness<<"\t"<<minFitness<<"\t"<<meanFitness<<"\t"<<starf<<endl;
	}
	output.close();
	
}
int main(){
	string path = "/home/ryan/testdataNew/data_Scale0.9/";
	string dirname;
	ifstream input("ls.txt");
	while(input>>dirname){
		dirname = path+dirname;
		dirname +="/";
//		cout<<dirname<<endl;
		process(dirname);
	}
	//process(dirname);
}
