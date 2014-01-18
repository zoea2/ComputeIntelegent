#include <iostream>
#include <cmath>
#include <string>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;

#define INF 1.0e99
#define EPS 1.0e-14
#define E  2.7182818284590452353602874713526625
#define PI 3.1415926535897932384626433832795029

double u(double x,double a,double k,double m){
	if(x > a)
		return k * pow((x - a),m);
	else if(x >= -a && x <= a)
		return 0;
	else if(x < -a)
		return k * pow(-x-a,m);
}

void test_func(double *x, double *f, int nx, int mx,int func_num)
{
	for (int i = 0; i < mx; i++)
	{
		switch(func_num)
		{
		case 1:
			{
				f[i] = 0;
				for(int j = 0;j < nx;j++){
					f[i] += x[j] * x[j];
				} 

		 	}
			break; 
		case 2:
			{
				double temp = 1; 
				f[i] = 0; 
				for(int j = 0;j < nx;j++){ 
					double absx = abs(x[j]); 
					f[i]+= absx; 
					temp *= absx; 
				} 
			f[i] += temp; 
			}
			break; 
		case 3: 
			{
				f[i] = 0; 
				for(int j = 0;j < nx;j++){
					double temp = 0; 
					for(int k = 0;k <= j;k++){
						temp += x[k]; 
					}
					f[i] += temp * temp;	 
				} 
			}
			break; 
		case 4: 
			{
				f[i] = 0; 
				double max0 = -1; 
				for(int j = 0;j < nx;j++){
					if(max0 < abs(x[j]))
						max0 = abs(x[j]); 
				}
				f[i] = max0;
			} 
			break;
		case 5: 
			{	
				f[i] = 0; 
				for(int j = 0;j < nx-1;j++){
					f[i] += pow(x[j]-1,2);
					f[i] += 100 * pow(x[j+1] - pow(x[j],2),2); 
				}
			} 
			break;
		case 6:
			{	
				f[i] = 0;
				for(int j = 0;j < nx;j++){
					f[i] += pow(floor(x[j]+0.5),2); 
				}
			}		
			break;
		case 7:
			{
				f[i] = 0;
				for(int j = 0;j < nx;j++){
					f[i] += (j+1) * pow(x[j],4);
				}
				f[i] += rand() % RAND_MAX * 1.0 / RAND_MAX;
			}	
			break;
		case 8:
			{
				f[i] = 0;
				for(int j = 0;j < nx;j++){
					f[i] += (-x[j]) * sin(sqrt(abs(x[j])));
				}
			}
			break;
		case 9: 
			{
				f[i] = 0; 
				for(int j = 0;j < nx;j++){
					f[i] += pow(x[j],2) - 10 * cos(2 * PI * x[j]) + 10;
				}
			}
			break;
		case 10:
			{
				f[i] = 0;
				double temp1 = 0;
				double temp2 = 0;
				for(int j = 0;j < nx;j++){
					temp1 += pow(x[j],2);
					temp2 += cos(2 * PI * x[j]);
				}
				temp1 /= nx;
				temp2 /= nx;
				f[i] = -20  * exp(-0.2 * sqrt(temp1)) - exp(temp2) + 20 + E; 
			}			
			break;
		case 11:
			{
				f[i] = 0;
				double temp = 1;
				for(int j = 0;j < nx;j++){
					temp *= cos(x[j] / sqrt(j+1));
					f[i] += pow(x[j],2);
				}
				f[i] /= 4000;
				f[i] -= temp;
				f[i] += 1;
			}
			break;
		case 12:
			{
				f[i] = 0;
				double tempu = 0;
				double temp = 0;
				for(int j = 0;j < nx;j++){
					double yj = 1 + 0.25 * (x[j] + 1);
					tempu += u(x[j],10,100,4);
					f[i] += 10 * pow(sin(PI * yj),2);
					if(j < nx-1)
						temp += pow(yj-1,2) * (1 + 10 * pow(sin(PI * (1 + 0.25 * (x[j] + 1))),2));
					else
						f[i] += pow(yj-1,2);
				}
				f[i] += temp;
				f[i] *= PI / nx;
				f[i] += tempu;
			}
			break;
		case 13:
			{
				f[i] = pow(sin(3 * PI * x[0]),2);
				double tempu = 0;
				double temp = 0;
				for(int j = 0;j < nx;j++){
					if(j < nx-1){
						f[i] += pow(x[j]-1,2) * (1 + pow(sin(3 * PI * x[j+1]),2));
					}
					else
						f[i] += pow((x[j]-1),2) * (1 + pow(sin(2 * PI * x[j]),2));
					tempu += u(x[j],5,100,4);
				}
				f[i] *= 0.1;
				f[i] += tempu;
			}			
			break;
		default:
			printf("¥nError: There are only 28 test functions in this test suite!¥n");
			f[i] = 0.0;
			break;
		}

	}


}
