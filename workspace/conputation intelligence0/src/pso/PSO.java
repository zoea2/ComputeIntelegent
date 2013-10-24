package pso;

import java.io.*;
import java.util.*;

public class PSO {
	final static int POPSIZE = 100;
	final static int MAXGEN = 10000;
	final static int dim = 2;
	static PsoGenotype gBest;
	static double randval(double high,double low){
		return (Math.random() * (high - low) + low);
	}
	static void init(PsoGenotype[] population) throws FileNotFoundException{
		double lbound;
		double ubound;
		Scanner input = new Scanner(new File("/home/ryan/bound.txt"));
		for(int i = 0;i < PsoGenotype.NVARS;i++){
			lbound = input.nextDouble();
			ubound = input.nextDouble();
			for(int j = 0;j < POPSIZE;j++){
				population[j].lower[i] = lbound;
				population[j].upper[i] = ubound;
				population[j].gene[i] = randval(ubound,lbound);
				System.arraycopy(population[j].gene, 0, 
								population[j].pBest, 0, population[j].gene.length);
				population[j].maxSpeed[i] = 0.1 * (ubound - lbound);
				//population[j].speed[i] = randval(population[j].maxSpeed[i],0);
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
	static void evaluate(PsoGenotype[] population){
		for(int i = 0;i < POPSIZE;i++){
			double x1 = population[i].gene[0];
			double x2 = population[i].gene[1];
			population[i].fitness = 21.5 + x1 * Math.sin(4*Math.PI*x1)+x2*Math.sin(20*Math.PI*x2);
			if(population[i].fitness > population[i].bestFit){
				population[i].bestFit = population[i].fitness;
				System.arraycopy(population[i].gene, 0 , population[i].pBest, 0, population[i].gene.length);
			}
		}
	}
	static void keepTheBest(PsoGenotype[] population) throws CloneNotSupportedException{
		for(int i = 0;i < POPSIZE;i++){
			if(gBest.bestFit < population[i].bestFit){
				gBest = (PsoGenotype) population[i].clone();
				//System.out.printf("gf %f pf %f\n", gBest.bestFit,population[i].bestFit);
			}
			//System.out.printf("gf %f pf %f\n", gBest.bestFit,population[i].bestFit);
		}
	}
	static void nextGen(PsoGenotype[] population){
		for(int i = 0;i < POPSIZE;i++){
			for(int j = 0;j < PsoGenotype.NVARS;j++){
				population[i].speed[j] = PsoGenotype.w * population[i].speed[j] 
										+ PsoGenotype.c1 * Math.random() *(population[i].pBest[j] - population[i].gene[j])
										+ PsoGenotype.c2 * Math.random() * (gBest.pBest[j]- population[i].gene[j]);
				if(population[i].speed[j] > population[i].maxSpeed[j])
					population[i].speed[j] = population[i].maxSpeed[j];
				population[i].gene[j] += population[i].speed[j];
				if(population[i].gene[j] < population[i].lower[j] || population[i].gene[j] > population[i].upper[j])
					population[i].gene[j] = randval(population[i].upper[j],population[i].lower[j]);
			}
		}
	}
	public static void main(String[] args) throws FileNotFoundException, CloneNotSupportedException{
		PsoGenotype[] population = new PsoGenotype[POPSIZE];
		//PsoGenotype[] newPopulation = new PsoGenotype[POPSIZE];
		for(int i = 0;i < POPSIZE;i++){
			population[i] = new PsoGenotype(dim);
			//newPopulation[i] = new PsoGenotype(dim);
		}
		gBest = new PsoGenotype(dim);
		int genaration = 0;
		init(population);
		
		while(genaration < MAXGEN){
			genaration++;
			System.out.println(genaration);
			evaluate(population);
			keepTheBest(population);
			//System.out.println(population[1].bestFit);
			//System.out.println(gBest.bestFit);
			nextGen(population);
			//System.out.println(gBest.bestFit);
		}
		/*for(int i = 0;i < POPSIZE;i++){
			System.out.println(population[i].bestFit);
		}*/
		System.out.printf("%f %f\n", gBest.gene[0],gBest.gene[1]);
		System.out.println(gBest.bestFit);
	}
}

