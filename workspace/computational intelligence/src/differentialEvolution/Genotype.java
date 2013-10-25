package differentialEvolution;

public class Genotype {
	final int NVARS = 2;
	//final int MAXGENS = 10000;
	final double PXOVER = 0.8;
	final double PMUTATION = 0.1;
	double[] gene = new double [NVARS];
	double fitness;
	double[] upper = new double[NVARS];
	double[] lower = new double[NVARS];
	double rfitness;
	double cfitness;
	Genotype(){
		;
	}
}
