#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>

#include <nds.h>

#include "utilities.h"
#include "calculator.h"

void refreshscreen()
{
	int sx,sy;
	for(sx = 0; sx < 256; sx++)
	    for(sy = 0; sy < 192; sy++)
			VRAM_A[(sy * 256) + (sx)] = RGB15(31,31,31);
}

void plot(int sy, double sx)
{
	sy = -sy;
	sx += 256/2;
	sy += 192/2;
	VRAM_A[((sy) * 256) + int(roundf(sx))] = RGB15(0,0,0);
	return;
}

std::string make_equation(std::vector<std::string> equation_split, double x_value)
{
	std::string equation = "";
	
	int counter = 0;
	
	for(auto &i : equation_split) 
	{
		counter++;
		equation += i;
		
		if(counter != equation_split.size())
		{
			if(x_value < 0)
				equation += "(0" + to_string(x_value) + ")";
			else
				equation += to_string(x_value);
		}
	}
	
	return equation;
}

void graph(std::string equation)
{
	std::vector<std::string> equation_split;
	stringsplit('X', equation, equation_split);
	
	double asdf = 0;
	int value = 0;
	
	videoSetMode(MODE_FB0);
	vramSetBankA(VRAM_A_LCD);
	
	refreshscreen();
	
	while(value < 192/2 && asdf < 256/2)
	{
		plot(value, asdf);
		value = atoi(solve(make_equation(equation_split, asdf), 0).c_str());
		asdf += 0.1;
	}
	
	for(asdf = -asdf; asdf<0; asdf += 0.1)	
	{
		//printf("%s\n", solve(make_equation(equation_split, asdf).c_str(),0).c_str());
		plot(atoi(solve(make_equation(equation_split, asdf), 0).c_str()), asdf);
	}
	
	return;
}
