#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>

#include <nds.h>

#include "utilities.h"
#include "calculator.h"
#include "graph.h"

std::string factor(std::string equation)
{
	bool isDone = false;
	int check = 0;
	
	std::vector<std::string> equation_split;
	stringsplit('X', equation, equation_split);
	
	while(not isDone && check < 100) //nothing i need to factor should have over 100
	{
		if(atoi(solve(make_equation(equation_split, check), 0).c_str()) == 0)
			return to_string(check);
		else if(atoi(solve(make_equation(equation_split, -check), 0).c_str()) == 0)
			return to_string(-check);
		check++;
	}
	return "Nothing found :(";
}
