package differentialEvolution;

import java.io.*;
import java.util.Scanner;

public class DE {
	final static int POPSIZE = 50;
	//final static int funcEvaluate = 100;
	final static int funcEvaluate =300000;
	static int feNumber;
	//final static int Genotype.NVARS = 10;
	static int f;
	static Genotype best;
	static Genotype bestA;
	static int[][] oArray;
	static int row;
	//static int[][] ME;
	static double[][] MTurn;
	static double[][] MResult;
	static double[] Rosenbrock;
	static double[] Rastrigin;
	public static void init(Genotype[] population,Genotype[] MidPop) throws FileNotFoundException{
		double lbound;
		double ubound;
		String filename = "/home/ryan/testdata/bound" + f + ".txt";
		Scanner input = new Scanner(new File(filename));
		lbound = input.nextDouble();
		ubound = input.nextDouble();
		for(int i = 0;i < Genotype.NVARS;i++){			
			System.out.println(lbound);
			System.out.println(ubound);
			for(int j = 1;j <= POPSIZE;j++){
				population[j].fitness = 0.0;
				//population[j].cfitness = 0;
				//population[j].rfitness = 0;
				population[j].lower[i] = lbound;
				population[j].upper[i] = ubound;
				MidPop[j].lower[i] = lbound;
				MidPop[j].upper[i] = ubound;
				population[j].gene[i] = Math.random() * 
						(population[j].upper[i] - population[j].lower[i]) + 
						population[j].lower[i];
			}
		}
		input.close();
		/*
		PrintWriter output = new PrintWriter(new File("/home/ryan/output.txt"));
		for(int i = 0;i < POPSIZE;i++){
			output.printf("Pop  %f %f %f\n",population[i].gene[0],population[i].gene[1],population[i].fitness);
			//output.printf("MidPop  %f %f %f\n",MidPop[i].gene[0],MidPop[i].gene[1],MidPop[i].fitness);
		}
		output.close();
		*/
	}
	public static double funcU(double x,int a,int k,int m){
		if(x > a)
			return (double)(k * Math.pow(x-a, m));
		else if(x <= a && x >= -a)
			return 0;
		else
			return (double)(k * Math.pow(-x - a, m));
	}
	public static void setME(double[][] ME){
		for(int i = 0;i < Genotype.NVARS;i++){
			for(int j = 0;j < Genotype.NVARS;j++){
				if(i == j)
					ME[i][j] = 1;
				else
					ME[i][j] = 0;
			}
		}
	}
	public static void MulMatrix(){ 
		double[][] temp = new double[Genotype.NVARS][Genotype.NVARS];
		for(int i = 0;i < Genotype.NVARS;i++){
			for(int j = 0;j < Genotype.NVARS;j++){
				temp[i][j] = 0;
				for(int k = 0;k < Genotype.NVARS;k++)
					temp[i][j] += MResult[i][k] * MTurn[k][j];
			}
		}
		MResult = temp.clone();
	}
	public static void MRot(int i,int j){
		setME(MTurn);
		double alpha = (Math.random() - 0.5) * Math.PI * 0.5;
		//System.out.printf("alpha: %f\n", alpha);
		MTurn[i][i] = Math.cos(alpha);
		//System.out.printf("mii: %f\n", MTurn[i][i]);
		MTurn[j][j] = Math.cos(alpha);
		MTurn[i][j] = Math.sin(alpha);
		MTurn[j][i] = -Math.sin(alpha);
	}
	public static void CreateMatrix(){
		setME(MResult);
		for(int i = 1;i < Genotype.NVARS;i++){
			MRot(0,i);
			MulMatrix();
			
		}
		for(int i = 1;i < Genotype.NVARS-1;i++){
			MRot(i,Genotype.NVARS-1);
			MulMatrix();
		}
		
	}
	public static void evaluate(Genotype[] population,int size,int number){
		for(int i = 1;i <= size;i++){
			evaluate(population[i],number);
		}
	}
	public static void evaluate(Genotype population,int number){
		switch(number){
			case 0:
					double x1 = population.gene[0];
					double x2 = population.gene[1];
					population.fitness = 21.5 + x1 * Math.sin(4*Math.PI*x1)+x2*Math.sin(20*Math.PI*x2);
					//System.out.printf("popsize %d fitness %f \n",i,population[i].fitness);
				
				break;
			case 1:
					population.fitness = 0;
					for(int j = 0;j < Genotype.NVARS;j++){
						population.fitness += Math.pow(population.gene[j], 2);
					}
					feNumber++;
				break;
			case 2:
					population.fitness = 0;
					double temp = 1;
					for(int j = 0;j < Genotype.NVARS;j++){
						double tempabs = Math.abs(population.gene[j]);
						population.fitness += tempabs;
						temp *= tempabs;
					}
					population.fitness += temp;
					feNumber++;
				break;
			case 3:
					population.fitness = 0;
					for(int j = 0;j < Genotype.NVARS - 1;j++){
						x1 = population.gene[j];
						x2 = population.gene[j+1];
						population.fitness += 100 * Math.pow(x2 - Math.pow(x1,2),2) + Math.pow(x1-1,2);
					}
					feNumber++;
				break;
			case 4:
					population.fitness = Math.random();
					while(population.fitness == 1)
						population.fitness = Math.random();
					for(int j = 0;j < Genotype.NVARS;j++){
						population.fitness += j * Math.pow(population.gene[j], 4);
					}
					feNumber++;
				
				break;
			case 5:
					population.fitness = 418.9829 * Genotype.NVARS;
					for(int j = 0;j < Genotype.NVARS;j++){
						double x = population.gene[j];
						population.fitness -= x * Math.sin(Math.sqrt(Math.abs(x)));
					}
					feNumber++;
				break;
			case 6:
					population.fitness = 0;
					for(int j = 0;j < Genotype.NVARS;j++){
						double x = population.gene[j];
						population.fitness += Math.pow(x,2) - 10 * Math.cos(2 * Math.PI * x) + 10;
					}
					feNumber++;
				break;
			case 7:
					population.fitness = 20 + Math.E;
					double temp1 = 0;
					double temp2 = 0;
					for(int j = 0;j < Genotype.NVARS;j++){
						temp1 += Math.pow(population.gene[j],2);
						temp2 += Math.cos(2 * Math.PI * population.gene[j]);
					}
					population.fitness += -20 * Math.exp(-0.2 * Math.sqrt(temp1 / Genotype.NVARS))
							 				- Math.exp(temp2 / Genotype.NVARS);
					feNumber++;
				break;
			case 8:
					population.fitness = 0;
					temp = 1;
					for(int j = 0;j < Genotype.NVARS;j++){
						population.fitness += Math.pow(population.gene[j], 2);
						temp *= Math.cos(population.gene[j] / Math.sqrt(j+1));
					}
					population.fitness = population.fitness / 4000 - temp + 1;
					feNumber++;
				break;
			case 9:
					double y1 = 1 + (population.gene[0] + 1) / 4;
					double yd = 1 + (population.gene[Genotype.NVARS-1] + 1) / 4;
					temp1 = 10 * Math.pow(Math.sin(Math.PI * y1), 2)
									+ Math.pow(yd-1,2);
					temp2 = 0;					
					for(int j = 0;j < Genotype.NVARS;j++){
						if(j < Genotype.NVARS-1){
							double yi = 1 + (population.gene[j] + 1) / 4;
							double yii = 1 + (population.gene[j+1] + 1) / 4;
							temp1 += Math.pow(yi-1,2) * (1 + 10 * Math.pow(Math.sin(Math.PI * yii), 2));
						}
						temp2 += funcU(population.gene[j],10,100,4);
					}
					population.fitness = temp1 / Genotype.NVARS * Math.PI + temp2; 
					feNumber++;
				break;
			case 10:
					population.fitness = Math.pow(Math.sin(3 * Math.PI * population.gene[0]), 2);
					double xd = population.gene[Genotype.NVARS-1];
					population.fitness += Math.pow(xd-1,2) * (1 + Math.pow(Math.sin(2 * Math.PI * xd), 2));
					temp = 0;
					for(int j = 0;j < Genotype.NVARS;j++){
						if(j < Genotype.NVARS - 1){
							population.fitness += Math.pow(population.gene[j] - 1, 2) 
									* (1 + Math.pow(Math.sin(3 * Math.PI * population.gene[j+1]), 2));
						}
						temp += funcU(population.gene[j],5,100,4);
					}
					population.fitness /= 10;
					population.fitness += temp;
					feNumber++;
				break;
			case 11:
					population.fitness = 418.9829 * Genotype.NVARS;
					for(int j = 0;j < Genotype.NVARS;j++){
						double y = 0;
						for(int k = 0;k < Genotype.NVARS;k++){
							y += MResult[j][k] * (population.gene[k] - 420.96);
						}
						y += 420.96;
						if (Math.abs(y) <= 500)
							y = y * Math.sin(Math.sqrt(Math.abs(y)));
						else
							y = 0;
						population.fitness -= y;
					}
					feNumber++;
				
				break;
			case 12:
					//CreateMatrix(MResult);
					population.fitness = 0;
					for(int j = 0;j < Genotype.NVARS;j++){
						double y = 0;
						for(int k = 0;k < Genotype.NVARS;k++){
							y += MResult[j][k] * population.gene[k];
						}
						population.fitness += Math.pow(y,2) - 10 * Math.cos(2 * Math.PI * y) + 10;
					}
					feNumber++;
				
				break;
			case 13:
					//CreateMatrix(MResult);
					temp1 = 0;
					temp2 = 0;
					for(int j = 0;j < Genotype.NVARS;j++){
						double y = 0;
						for(int k = 0;k < Genotype.NVARS;k++){
							y += MResult[j][k] * population.gene[k];
						}
						temp1 += Math.pow(y, 2);
						temp2 += Math.cos(2 * Math.PI * y);
					}
					population.fitness = -20 * Math.exp(-0.2 * Math.sqrt(temp1 / Genotype.NVARS))
							- Math.exp(temp2 / Genotype.NVARS) + 20 + Math.E;
					feNumber++;
				break;
			case 14:
					//CreateMatrix(MResult);
					population.fitness = 0;
					temp = 1;
					for(int j = 0;j < Genotype.NVARS;j++){
						double y = 0;
						for(int k = 0;k < Genotype.NVARS;k++){
							y += MResult[j][k] * population.gene[k];
						}
						population.fitness += Math.pow(y,2);
						temp *= Math.cos(y / Math.sqrt(j+1));
					}
					population.fitness /= 4000;
					population.fitness = population.fitness - temp + 1;
					feNumber++;
				break;
			case 15:
					population.fitness = 390;
					for(int j = 0;j < Genotype.NVARS-1;j++){
						double z1 = population.gene[j] - Rosenbrock[j] + 1;
						double z2 = population.gene[j+1] - Rosenbrock[j+1] +1;
						population.fitness += 100 * Math.pow(Math.pow(z1,2) - z2, 2) + Math.pow(z1-1,2);
					}
					feNumber++;
				break;
			case 16:
					population.fitness = -330;
					for(int j = 0;j < Genotype.NVARS;j++){
						double z = population.gene[j] - Rastrigin[j];
						population.fitness += Math.pow(z,2) - 10 * Math.cos(2 * Math.PI * z) + 10;
					}
					feNumber++;
				break;
		}
		
		
	}

	public static void select(Genotype[] population,Genotype[] MidPop) throws CloneNotSupportedException{
		for(int i = 1;i <= POPSIZE;i++)
			if(MidPop[i].fitness < population[i].fitness){
				population[i] = (Genotype) MidPop[i].clone();				
			}
	}
	public static boolean keepTheBest(Genotype[] population) throws CloneNotSupportedException{
		double bestf;
		int index;
		best = null;
		if(best == null)
		{
			bestf = population[1].fitness;
			index = 1;
		}
		else{
			bestf = best.fitness;
			index = -1;
		}
		for(int i = 1;i <= POPSIZE;i++){
			if(bestf > population[i].fitness){
				bestf = population[i].fitness;
				index = i;
			}			
		}
		if(index != -1){
			best = (Genotype) population[index].clone();
			//return true;
		}
		if(bestA == null || bestA.fitness > best.fitness){
			bestA = (Genotype) best.clone();
			return true;
		}
		else 
			return false;
	}
	public static void mutate_rand_1_bin(Genotype[] population,Genotype[] MidPop)throws CloneNotSupportedException{
		for(int p = 1;p <= POPSIZE;p++){
			int ran1 = (int)(POPSIZE * Math.random() + 1);
			while(ran1 == p)
				ran1 = (int)(POPSIZE * Math.random() + 1);
			int ran2 = (int)(POPSIZE * Math.random() + 1);
			while(ran2 == ran1 || ran2 == p)
				ran2 = (int)(POPSIZE * Math.random() + 1);
			int ran3 = (int)(POPSIZE * Math.random() + 1);
			while(ran3 == ran2 || ran3 == ran1 || ran3 == p )
				ran3 = (int)(POPSIZE * Math.random() + 1);
			Genotype temp1 = new Genotype();
			temp1 = (Genotype) population[ran2].clone();
			Genotype temp2 = new Genotype();
			temp2 = (Genotype) population[ran3].clone();			
			Genotype[] temp = new Genotype[row+1];
			for(int i = 1;i <= row;i++){
				temp[i] = new Genotype();
				for(int j = 1;j <= Genotype.NVARS;j++){
					if(oArray[i][j] == 1)
						temp[i].gene[j-1] = temp1.gene[j-1];
					else
						temp[i].gene[j-1] = temp2.gene[j-1];
				}				
			}
			evaluate(temp,row,f);
			double[][] tempfit = new double[Genotype.NVARS+1][Genotype.LEVEL+1];
			Genotype ctemp = new Genotype();
			for(int i = 1;i <= Genotype.NVARS;i++){
				double min = 0x7fffffff;
				int index = -1;
				for(int j = 0;j < Genotype.LEVEL;j++){
					tempfit[i][j] = 0;
					int count = 0;
					for(int k = 1;k <= row;k++){
						if(oArray[k][i] == j){
							tempfit[i][j] += temp[k].fitness;
							count++;
						}
					}
					tempfit[i][j] /= count;
					if(min > tempfit[i][j]){
						min = tempfit[i][j];
						index = j;
					}
				}
				if(index == 0)
					ctemp.gene[i-1] = temp2.gene[i-1];
				else
					ctemp.gene[i-1] = temp1.gene[i-1];
				
			}
			Genotype ctemp1 = new Genotype();
			ctemp1 = (Genotype) ctemp.clone();
			int ran4 = (int)(POPSIZE * Math.random() + 1);
			while(ran4 == ran1 || ran4 == ran3 || ran4 == ran2 || ran4 == p)
				ran4 = (int)(POPSIZE * Math.random() + 1);
			int ran5 = (int)(POPSIZE * Math.random() + 1);
			while(ran5 == ran1 || ran5 == ran2 || ran5 == ran3 || ran5 == ran4 || ran5 == p)
				ran5 = (int)(POPSIZE * Math.random() + 1);
			temp1 = (Genotype)population[ran4].clone();
			temp2 = (Genotype)population[ran5].clone();
			//System.out.printf("%d %d %d %d %d\n", ran1,ran2,ran3,ran4,ran5);
			for(int i = 1;i <= row;i++){
				temp[i] = new Genotype();
				for(int j = 1;j <= Genotype.NVARS;j++){
					if(oArray[i][j] == 1)
						temp[i].gene[j-1] = temp1.gene[j-1];
					else
						temp[i].gene[j-1] = temp2.gene[j-1];
				}				
			}
			evaluate(temp,row,f);
			tempfit = new double[Genotype.NVARS+1][Genotype.LEVEL+1];
			ctemp = new Genotype();
			for(int i = 1;i <= Genotype.NVARS;i++){
				double max = 0;
				int index = -1;
				for(int j = 0;j < Genotype.LEVEL;j++){
					tempfit[i][j] = 0;
					int count = 0;
					for(int k = 1;k <= row;k++){
						if(oArray[k][i] == j){
							tempfit[i][j] += temp[k].fitness;
							count++;
						}
					}
					tempfit[i][j] /= count;
					if(max < tempfit[i][j]){
						max = tempfit[i][j];
						index = j;
					}
				}
				//System.out.printf("%f %f\n", ctemp.gene[i-1],ctemp1.gene[i-1]);
				if(index == 0)
					ctemp.gene[i-1] = temp2.gene[i-1];
				else
					ctemp.gene[i-1] = temp1.gene[i-1];
				//System.out.printf("%f %f\n", ctemp.gene[i-1],ctemp1.gene[i-1]);
				
			}
			for(int j = 0;j < Genotype.NVARS;j++){
				MidPop[p].gene[j] = population[ran1].gene[j] + Genotype.SCALE * 
										(ctemp1.gene[j] - ctemp.gene[j]);
				if(MidPop[p].gene[j] < population[ran1].lower[j] || MidPop[p].gene[j] > population[ran1].upper[j])
					MidPop[p].gene[j] = Math.random() * (population[ran1].upper[j] - population[ran1].lower[j])
										+ population[ran1].lower[j];
			}
			//MidPop[p].gene = ctemp.gene.clone();			
		}		
	}
	public static void mutate(Genotype[] population,Genotype[] MidPop) throws CloneNotSupportedException{
		for(int i = 1;i <= POPSIZE;i++){			
			int ran1 = (int)(POPSIZE * Math.random() + 1);
			while(ran1 == i)
				ran1 = (int)(POPSIZE * Math.random() + 1);
			Genotype temp1 = (Genotype) population[ran1].clone();
			int ran2 = (int)(POPSIZE * Math.random() + 1);
			while(ran2 == ran1 || ran2 == i ){
				ran2 = (int)(POPSIZE * Math.random() + 1);
			}
			Genotype temp2 = (Genotype) population[ran2].clone();
			int ran3 = (int)(POPSIZE * Math.random() + 1);
			while(ran3 == ran1 || ran3 == ran2 || ran3 == i)
				ran3 = (int)(POPSIZE * Math.random() + 1);
			for(int j = 0;j < Genotype.NVARS;j++){
				MidPop[i].gene[j] = population[ran3].gene[j] + Genotype.SCALE * 
										(temp1.gene[j] - temp2.gene[j]);
				if(MidPop[i].gene[j] < population[ran3].lower[j] || MidPop[i].gene[j] > population[ran3].upper[j])
					MidPop[i].gene[j] = Math.random() * (population[ran3].upper[j] - population[ran3].lower[j])
										+ population[ran3].lower[j];
			}
		}
	}
	public static void mutate_best_1(Genotype[] population,Genotype[] MidPop) throws CloneNotSupportedException{
		for(int i = 1;i <= POPSIZE;i++){			
			int ran1 = (int)Math.floor(POPSIZE * Math.random() + 1);
			while(ran1 == i)
				ran1 = (int)Math.floor(POPSIZE * Math.random() + 1);
			Genotype temp1 = (Genotype) population[ran1].clone();
			int ran2 = (int)Math.floor(POPSIZE * Math.random() + 1);
			while(ran2 == ran1 || ran2 == i ){
				ran2 = (int)Math.floor(POPSIZE * Math.random() + 1);
			}
			Genotype temp2 = (Genotype) population[ran2].clone();
			for(int j = 0;j < Genotype.NVARS;j++){
				MidPop[i].gene[j] = best.gene[j] + Genotype.SCALE * 
										(temp1.gene[j] - temp2.gene[j]);
				if(MidPop[i].gene[j] < MidPop[i].lower[j] || MidPop[i].gene[j] > MidPop[i].upper[j])
					MidPop[i].gene[j] = Math.random() * (MidPop[i].upper[j] - MidPop[i].lower[j])
										+ MidPop[i].lower[j];
			}
		}
	}
	public static void orthMutate_best_1(Genotype[] population,Genotype[] MidPop) throws CloneNotSupportedException{
		for(int p = 1;p <= POPSIZE;p++){			
			int ran1 = (int)Math.floor(POPSIZE * Math.random() + 1);
			while(ran1 == p)
				ran1 = (int)Math.floor(POPSIZE * Math.random() + 1);
			Genotype temp1 = (Genotype) population[ran1].clone();
			int ran2 = (int)Math.floor(POPSIZE * Math.random() + 1);
			while(ran2 == ran1 || ran2 == p ){
				ran2 = (int)Math.floor(POPSIZE * Math.random() + 1);
			}
			Genotype temp2 = (Genotype) population[ran2].clone();
			int ran3 = (int)Math.floor(POPSIZE * Math.random() + 1);
			while(ran3 == ran1 || ran3 == ran2 || ran3 == p)
				ran3 = (int)Math.floor(POPSIZE * Math.random() + 1);
			Genotype[] temp = new Genotype[row+2];
			for(int i = 1;i <= row;i++){
				temp[i] = new Genotype();
				for(int j = 1;j <= Genotype.NVARS;j++){
					if(oArray[i][j] == 1)
						temp[i].gene[j-1] = population[ran3].gene[j-1];
					else
						temp[i].gene[j-1] = best.gene[j-1];
				}				
			}
			evaluate(temp,row,f);
			double[][] tempfit = new double[Genotype.NVARS+1][Genotype.LEVEL+1];
			Genotype ctemp = new Genotype();
			for(int i = 1;i <= Genotype.NVARS;i++){
				double min = -1;
				int index = -1;
				for(int j = 0;j < Genotype.LEVEL;j++){
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
						//System.out.println(min);
						index = j;
					}
					else if(min > tempfit[i][j]){
						min = tempfit[i][j];
						//System.out.println(min);
						index = j;
					}
				}
				if(index == 0)
					ctemp.gene[i-1] = best.gene[i-1];
				else
					ctemp.gene[i-1] = population[ran3].gene[i-1];
					
			}
			evaluate(ctemp,f);
			if(best.fitness > ctemp.fitness)
			{
				for(int j = 0;j < Genotype.NVARS;j++){
					MidPop[p].gene[j] = ctemp.gene[j] + Genotype.SCALE * 
										(temp1.gene[j] - temp2.gene[j]);
					if(MidPop[p].gene[j] < MidPop[p].lower[j] || MidPop[p].gene[j] > MidPop[p].upper[j])
						MidPop[p].gene[j] = Math.random() * (MidPop[p].upper[j] - MidPop[p].lower[j])
										+MidPop[p].lower[j];
				}
			}
			else{
				for(int j = 0;j < Genotype.NVARS;j++){
					MidPop[p].gene[j] = best.gene[j] + Genotype.SCALE * 
										(temp1.gene[j] - temp2.gene[j]);
					if(MidPop[p].gene[j] < MidPop[p].lower[j] || MidPop[p].gene[j] > MidPop[p].upper[j])
						MidPop[p].gene[j] = Math.random() * (MidPop[p].upper[j] - MidPop[p].lower[j])
										+MidPop[p].lower[j];
				}
			}
		}
	}
	public static void createOA(){
		row = (int)(Math.pow(2.0, Math.ceil(Math.log(Genotype.NVARS+1) / Math.log(2))));
		int col = row - 1;		
		int u = (int)(Math.log(row) / Math.log(2));
		//System.out.println(u);
		oArray = new int[row+2][col+2];
		for(int i = 1;i <= row;i++){
			for(int k = 1;k <= u;k++){
				int j = (int)Math.pow(2,k-1);
				oArray[i][j] = (int)(Math.floor((i - 1) / Math.pow(2,u-k))) % 2;
			}
		}
		
		for(int i = 1;i <= row;i++){
			for(int k = 2;k <= u;k++){
				int j = (int)(Math.pow(2, k-1));
				for(int s = 1; s <= j-1;s++){
					oArray[i][j+s] = (oArray[i][s]+ oArray[i][j]) % 2;
				}
			}
		}
		
		for(int i = 1;i <= row;i++){
			for(int j = 1;j <= col;j++){
				System.out.print(oArray[i][j]);
				System.out.print(" ");
			}
			System.out.println(' ');
		}
		
	}
	public static void orthCross(Genotype[] population,Genotype[] MidPop){
		for(int p = 1;p <= POPSIZE;p++){
			Genotype[] temp = new Genotype[row+2];
			for(int i = 1;i <= row;i++){
				temp[i] = new Genotype();
				for(int j = 1;j <= Genotype.NVARS;j++){
					if(oArray[i][j] == 1)
						temp[i].gene[j-1] = population[p].gene[j-1];
					else
						temp[i].gene[j-1] = MidPop[p].gene[j-1];
				}				
			}
			evaluate(temp,row,f);
			double[][] tempfit = new double[Genotype.NVARS+1][Genotype.LEVEL+1];
			Genotype ctemp = new Genotype();
			for(int i = 1;i <= Genotype.NVARS;i++){
				double min = -1;
				int index = -1;
				for(int j = 0;j < Genotype.LEVEL;j++){
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
						//System.out.println(min);
						index = j;
					}
					else if(min > tempfit[i][j]){
						min = tempfit[i][j];
						//System.out.println(min);
						index = j;
					}
				}
				if(index == 0)
					ctemp.gene[i-1] = MidPop[p].gene[i-1];
				else
					ctemp.gene[i-1] = population[p].gene[i-1];
				
			}
			evaluate(ctemp,f);
			if(MidPop[p].fitness > ctemp.fitness)
				MidPop[p].gene = ctemp.gene.clone();			
		}		
	}
	public static void cross(Genotype[] population,Genotype[] MidPop){
		for(int i = 1;i <= POPSIZE;i++){
			int jrand = (int) (Math.random() * Genotype.NVARS);
			if(jrand == Genotype.NVARS)
				jrand--;
			for(int j = 0;j < Genotype.NVARS;j++){
				if(Math.random() > Genotype.PXOVER && j != jrand){
					MidPop[i].gene[j] = population[i].gene[j];
					//System.out.printf("%f %f\n",MidPop[i].gene[j],population[i].gene[j]);
				}
			}
		}
	}
	public static void main(String[] args) throws CloneNotSupportedException, IOException{
		System.out.println("sjfklsd");
		MResult = new double[Genotype.NVARS+1][Genotype.NVARS+1];
		MTurn = new double[Genotype.NVARS+1][Genotype.NVARS+1];
		Rosenbrock = new double[Genotype.NVARS];
		Rastrigin = new double[Genotype.NVARS];		
		double[][] bestM = new double[20][2];
		double[] accept = new double[17];
		int unUpdateNum = 0;
		boolean isOl = false;
		Scanner input0 = new Scanner(new File("/home/ryan/testdata/accept.txt"));
		for(int i = 1;i <= 16;i++){
			accept[i] = input0.nextDouble();
		}
		final double conFactorInit = 0;
		final double conFactorMax = 1;
		
		input0.close();
		CreateMatrix();	
		createOA();
		for(f = 1;f <= 16;f++){
			if(f == 15){
				
				Scanner input = new Scanner(new File("/home/ryan/testdata/rosenbrock_func_data.txt"));
				for(int i = 0;i < Genotype.NVARS;i++){
					Rosenbrock[i] = input.nextDouble();
					//System.out.println(Rosenbrock[i]);
				}
				input.close();
			}
			if (f == 16){
				//CreateMatrix();	
				Scanner input = new Scanner(new File("/home/ryan/testdata/rastrigin_func_data.txt"));
				for(int i = 0;i < Genotype.NVARS;i++){
					Rastrigin[i] = input.nextDouble();
				}
				input.close();
			}
			bestM[f][0] = 0;
			bestM[f][1] = 0;
			for(int t = 0;t < 25;t++)
			{
				double conFct = conFactorInit;
				if(f >= 11 && f <= 14)
					CreateMatrix();
				Genotype[] population = new Genotype[POPSIZE+1];
			
			//Genotype[] newPopulation = new Genotype[POPSIZE+1];
			Genotype[] MidPop = new Genotype[POPSIZE+1];
			best = null;
			bestA = null;
			
	 		for(int i = 0;i <= POPSIZE;i++){
	 			population[i] = new Genotype();
	 			MidPop[i] = new Genotype();
	 		}
			
			
			init(population,MidPop);
			evaluate(population,POPSIZE,f);
			keepTheBest(population);
			feNumber = 0;
			while(feNumber <= funcEvaluate){	
				conFct += 900 * (conFactorMax - conFactorInit) / funcEvaluate;
				System.out.println(feNumber);
				//orthMutate_best_1(population,MidPop);
				
				if(feNumber > 250000){
					orthMutate_best_1(population,MidPop);
					//System.out.println("omb");
					//System.out.println(conFct);
					//orthCross(population,MidPop);
				}
				else{
					//System.out.println("mr");
					//System.out.println(conFct);
					mutate(population,MidPop);
					//cross(population,MidPop);
				}
				cross(population,MidPop);
				evaluate(population,POPSIZE,f);				
				evaluate(MidPop,POPSIZE,f);
				select(population,MidPop);
				if(!keepTheBest(population)){
					unUpdateNum++;
					if(unUpdateNum == 5)
						isOl = true;
				}
				else{
					unUpdateNum = 0;
					isOl = false;
				}
				
			}
			String filename = "/home/ryan/testdata/output" + f + ".txt";
			PrintWriter output = new PrintWriter(new BufferedWriter(new FileWriter(filename,true)));
			/*for(int i = 1;i <= POPSIZE;i++){
				output.printf("Pop  %.15f %.15f %.15f\n",population[i].gene[0],population[i].gene[1],population[i].fitness);
				output.printf("MidPop  %.15f %.15f %.15f\n",MidPop[i].gene[0],MidPop[i].gene[1],MidPop[i].fitness);
//			}*/
			output.write("best: ");
			output.write(""+bestA.fitness+'\n');
			for(int i = 0;i < Genotype.NVARS;i++)
				output.write(""+bestA.gene[i]+'\n');
			output.close();
			if(bestA.fitness <= accept[f]){
				bestM[f][0]+= bestA.fitness;
				bestM[f][1]++;
			}
			}
			/*System.out.println(best.fitness);
			for(int i = 0;i < Genotype.NVARS;i++)
				System.out.println(best.gene[i]);*/
		}
		
		
		
		/*Genotype a = new Genotype();
		//Genotype b = new Genotype();
		a.fitness = 30;
		a.gene[1] = 23;
		Genotype b = (Genotype) a.clone();
		b.fitness = 50;
		b.gene[1] = a.gene[1];
		a.gene[1] = 26;
		//a.gene[1] = 53;
		System.out.printf("%f %f %f %f",a.fitness,b.fitness,a.gene[1],b.gene[1]);*/
		PrintWriter output = new PrintWriter("/home/ryan/testdata/result1.txt");
		for(int i = 1;i <= 16;i++){
			output.println("function " + i +" :");
			output.println("accept times = "+bestM[i][1]);
			if(bestM[i][1] != 0)
				output.println(bestM[i][0]/bestM[i][1]);
			else
				output.println("unacceptable!");
		}
		output.close();
	}
}
