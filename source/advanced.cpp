//Created by Nick Kozma

#include "math.h"
#include "advanced.h"

double logarithm(double x)//calculates a log (base 10)
//SYMBOL:: Log
{
	double fx;
	fx =log10(x);

	return(fx);
}

double ln(double x) //calculates a natural log (base e)
//SYMBOL:: Ln or ln
{
	double fx;
	//ln
	fx = log(x);
	return(fx);
}

double fact1(double n, double r) //basically the re-existing facorial calculator except more versatile (for the combination and permutations)
//SYMBOL:: NONE, intermediate step
{
	if (r > 0)
		n = n - r;

	if (n > 1)
		return(n*fact1((n - 1)));
	else
		return(1);
}

double npr(double n, double r) //permutation function (nPr)
//SYMBOL:: nPr
{
	return(fact1(n) / fact1(n, r));
}

double ncr(double n, double r) //combination function (nCr)
//SYMBOL:: nCr
{
	return(fact1(n) / (fact1(r)*fact1(n, r)));
}
