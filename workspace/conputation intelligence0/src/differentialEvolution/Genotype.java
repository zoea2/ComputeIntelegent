package differentialEvolution;

public class Genotype implements Cloneable{
	final static int NVARS = 30;
	//final int MAXGENS = 10000;
	final static double PXOVER = 0.1;
	//final static double PMUTATION = 0.1;
	final static double SCALE = 0.5;
	final static int LEVEL = 2;
	double[] gene;
	double fitness;
	double[] upper;
	double[] lower;
	//double rfitness;
	//double cfitness;
	//int popsize;
	Genotype(){
		//NVARS = dim;
		//popsize = p;
		gene = new double [NVARS];
		upper = new double [NVARS];
		lower = new double [NVARS];
		fitness = 0;
		
	}
	public Object clone() throws CloneNotSupportedException{
		Genotype a = (Genotype)super.clone();
		a.gene = (double[])gene.clone();
		a.upper = (double[])upper.clone();
		a.lower = (double[])lower.clone();
		return a;
	}
}
