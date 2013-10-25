package pso;

	public class PsoGenotype implements Cloneable{
		static int NVARS;
		double[] gene;
		double fitness;
		double[] upper;
		double[] lower;
		final static double c1 = 2.0;
		final static double c2 = 2.0;
		static double w = 0.5;
		double[] pBest;
		double bestFit;
		double[] speed;
		double[] maxSpeed;
		PsoGenotype(int dim){
			NVARS = dim;
			fitness = 0;
			gene = new double[NVARS];
			upper = new double[NVARS];
			lower = new double[NVARS];
			bestFit = 0;
			pBest = new double [NVARS];
			speed = new double[NVARS];
			maxSpeed = new double[NVARS];
		}
		public Object clone() throws CloneNotSupportedException{
			PsoGenotype p = (PsoGenotype) super.clone();
			p.gene = (double[])gene.clone();
			p.upper = (double[])upper.clone();
			p.lower = (double[])lower.clone();
			p.pBest = (double[])pBest.clone();
			p.speed = (double[])speed.clone();
			p.maxSpeed = (double[])maxSpeed.clone();
			return p;
		}
	}
