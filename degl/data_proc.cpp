#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;
void process(string dirname){
	string temp1 = dirname;
	temp1.append("result1.txt");
	ofstream output(temp1.c_str());
	output<<"max\tmin\tmean\tstarf\tmeanOrth"<<endl;
	for(int i = 1;i <= 13;i++){
		char filename[100];
		string temp = dirname;
		temp.append("outputc%d.txt");
		sprintf(filename,temp.c_str(),i);
		cout<<filename<<endl;
		ifstream input(filename);
		double maxFitness,minFitness,meanFitness,starf,meanOrthnumber;
		double fitness[52];
		double orthnumber[52];
		meanFitness = 0;
		meanOrthnumber = 0;
		for(int j = 0;j <= 50;j++){
			string s;
			for(int k = 0;k < 4;k++)
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
			for(int k = 0;k <= 29;k++){
				getline(input,s);
			//	cout<<s<<endl;
			
			}
				
			input>>s>>orthnumber[j];
			meanOrthnumber += orthnumber[j];
			cout<<s<<" "<<orthnumber[j]<<endl;
			getline(input,s);
		}
		input.close();
		meanFitness /= 51;
		meanOrthnumber /= 51;
		starf = 0;
		for(int j = 0;j <= 50;j++){
		//double temp = 0;
			starf += pow(fitness[j] - meanFitness,2);
		}
		starf /= 51;
		starf = sqrt(starf);
		output<<maxFitness<<"\t"<<minFitness<<"\t"<<meanFitness<<"\t"<<starf<<"\t"<<meanOrthnumber<<endl;
	}
	output.close();
	
}
int main(){
	string path = "/home/ryan/testdataNN/data_Scale0.5/MBC2013SACrO/";
	string dirname;
//	ifstream input("ls.txt");
/*	while(input>>dirname){
		dirname = path+dirname;
		dirname +="/";
//		cout<<dirname<<endl;
		process(dirname);
	}*/
	process(path);
	//process(dirname);
}
