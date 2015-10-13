#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <sstream>

#include "utilities.h"
#include "advanced.h"

#define PI 3.14159265
#define E 2.71828182

int g_mode = 0;

std::vector<std::string> functions = {"int(", "sin(","asin(","cos(","acos(","tan(","atan(", "log(", "ln(", "nPr(", "nCr(", "rn(", "rnd(", "mag(", "avg", "("};
std::vector<std::string> operations = {"!","^","v","%","/","*","-","+", ")"};

std::vector<std::string> functions_operations = {"pi", "e", ",", "!","%","^","v","/","*","-","+", ")","(","int(","asin(","sin(","acos(","cos(","atan(","tan(","log(","ln(","nPr(","nCr(","rnd(","mag(","avg(","rn("};

void splitequation(std::string equation, std::vector<std::string>& putinto)
{
	std::string current = "";
	std::string i;
	
	for(int position = 0; position < equation.size(); position++)
	{
		for (int position_o = 0; position_o < functions_operations.size(); position_o++)
		{
			i = functions_operations.at(position_o);
			
			if(equation.find(i,position) == position)
			{
				if(current != "")
				{
					putinto.push_back(current);
					current = "";
				}
				position_o = 0;
				putinto.push_back(i);
				position += i.size();
			}
		}
		
		current += equation[position];
	}
	putinto.push_back(current);
	
	return;
}

bool canbeint(std::string before, std::string after)
{
	for(auto &i : functions_operations) 
	{
		if(before == i || after == i)
			return false;
	}
	return true;
}

void solve_simple(int start, std::vector<std::string>& equation_split)
{
	double answer;
	double previous, next;
	
	for(int place_o = 0; place_o < operations.size(); place_o++)
	{
		for(int place = start; place < equation_split.size(); place++)
		{
			if(place != 0 && place < equation_split.size() - 1)
			{

				previous = atof(equation_split.at(place-1).c_str());
				next = atof(equation_split.at(place+1).c_str());
				
				if(equation_split.at(place) == ")" && operations.at(place_o) != ")")
				{
					place_o++;
					place = start;
				}
				if(equation_split.at(place) == "!" && operations.at(place_o) != "!")
				{
					equation_split.erase(equation_split.begin()+place-1, equation_split.begin()+place+1);
					place--;
					answer=factorial(previous);
					equation_split.insert(equation_split.begin()+place, to_string(answer));
				}
				if(operations.at(place_o) == equation_split.at(place) && canbeint(equation_split.at(place-1), equation_split.at(place+1)))
				{
					switch(equation_split.at(place)[0])
					{
						case '^':
							equation_split.erase(equation_split.begin()+place-1, equation_split.begin()+place+2);
							place--;
							answer=pow(previous,next);
							equation_split.insert(equation_split.begin()+place, to_string(answer));
						break;
						case 'v':
							equation_split.erase(equation_split.begin()+place-1, equation_split.begin()+place+2);
							place--;
							answer=pow(next,1/previous);
							equation_split.insert(equation_split.begin()+place, to_string(answer));
						break;
						case '/':
							equation_split.erase(equation_split.begin()+place-1, equation_split.begin()+place+2);
							place--;
							answer = previous/next;
							equation_split.insert(equation_split.begin()+place, to_string(answer));
						break;
						case '*':
							equation_split.erase(equation_split.begin()+place-1, equation_split.begin()+place+2);
							place--;
							answer = previous*next;
							equation_split.insert(equation_split.begin()+place, to_string(answer));
						break;
						case '%':
							equation_split.erase(equation_split.begin()+place-1, equation_split.begin()+place+2);
							place--;
							answer = fmod(previous,next);
							equation_split.insert(equation_split.begin()+place, to_string(answer));
						break;
						case '+':
							equation_split.erase(equation_split.begin()+place-1, equation_split.begin()+place+2);
							place--;
							answer = previous+next;
							equation_split.insert(equation_split.begin()+place, to_string(answer));
						break;
						case '-':
							equation_split.erase(equation_split.begin()+place-1, equation_split.begin()+place+2);
							place--;
							answer = previous-next;
							equation_split.insert(equation_split.begin()+place, to_string(answer));
						break;
						default: break;
					}
				}
			}
		}
	}

	return;
}

int getbrackets(int start, std::vector<std::string>& equation)
{
	int open = 0;
	int close = 0;
	
	for(int place = start; place < equation.size(); place++) 
	{
		for(char& c : equation.at(place))
		{
			if(c == '(')
				open++;
			else if(c == ')')
				close++;
			if(open == close && place > start)
				return open;
		}
	}
	return -1;
}
	
void function(int start, std::vector<std::string>& equation)
{		
	double answer;
	for(int place = start; place < equation.size(); place++) 
	{
		for(auto &i : functions) 
		{
			if(equation.size() > place && equation.at(place) == i)
			{
				if(i == "int(")
				{	
					if(getbrackets(place, equation) != 1)
						function(place+1, equation);
					
					solve_simple(place, equation);
					
					answer = int(atof(equation.at(place+1).c_str()));
					equation.erase(equation.begin()+place, equation.begin()+place+3);
					
					equation.insert(equation.begin()+place, to_string(answer));
					place--;
				}
				if(i == "(")
				{	
					
					if(getbrackets(place, equation) != 1)
						function(place+1, equation);
					
					solve_simple(place, equation);
					
					answer = (atof(equation.at(place+1).c_str()));
					equation.erase(equation.begin()+place, equation.begin()+place+3);
					
					equation.insert(equation.begin()+place, to_string(answer));
					place--;
				}
				if(i == "sin(")
				{	
					
					if(getbrackets(place, equation) != 1)
						function(place+1, equation);
					
					solve_simple(place, equation);
					
					if(g_mode == 2)
						answer = sin(atof(equation.at(place+1).c_str())*PI/180);
					else
						answer = sin(atof(equation.at(place+1).c_str()));
						
					equation.erase(equation.begin()+place, equation.begin()+place+3);
					
					equation.insert(equation.begin()+place, to_string(answer));
					place--;
				}
				if(i == "asin(")
				{	
					
					if(getbrackets(place, equation) != 1)
						function(place+1, equation);
					
					solve_simple(place, equation);
					
					if(g_mode == 0)
						answer = asin(atof(equation.at(place+1).c_str())*PI/180);
					else
						answer = asin(atof(equation.at(place+1).c_str()));
						
					equation.erase(equation.begin()+place, equation.begin()+place+3);
					
					equation.insert(equation.begin()+place, to_string(answer));
					place--;
				}
				if(i == "cos(")
				{	
					
					if(getbrackets(place, equation) != 1)
						function(place+1, equation);
					
					solve_simple(place, equation);
					
					if(g_mode == 0)
						answer = cos(atof(equation.at(place+1).c_str())*PI/180);
					else
						answer = cos(atof(equation.at(place+1).c_str()));
						
					equation.erase(equation.begin()+place, equation.begin()+place+3);
					
					equation.insert(equation.begin()+place, to_string(answer));
					place--;
				}
				if(i == "acos(")
				{	
					
					if(getbrackets(place, equation) != 1)
						function(place+1, equation);
					
					solve_simple(place, equation);
					
					if(g_mode == 0)
						answer = acos(atof(equation.at(place+1).c_str())*PI/180);
					else
						answer = acos(atof(equation.at(place+1).c_str()));
						
					equation.erase(equation.begin()+place, equation.begin()+place+3);
					
					equation.insert(equation.begin()+place, to_string(answer));
					place--;
				}
				if(i == "tan(")
				{	
					
					if(getbrackets(place, equation) != 1)
						function(place+1, equation);
					
					solve_simple(place, equation);
					
					if(g_mode == 0)
						answer = tan(atof(equation.at(place+1).c_str())*PI/180);
					else
						answer = tan(atof(equation.at(place+1).c_str()));
						
					equation.erase(equation.begin()+place, equation.begin()+place+3);
					
					equation.insert(equation.begin()+place, to_string(answer));
					place--;
				}
				if(i == "atan(")
				{	
					
					if(getbrackets(place, equation) != 1)
						function(place+1, equation);
					
					solve_simple(place, equation);
					
					if(g_mode == 0)
						answer = atan(atof(equation.at(place+1).c_str())*PI/180);
					else
						answer = atan(atof(equation.at(place+1).c_str()));
						
					equation.erase(equation.begin()+place, equation.begin()+place+3);
					
					equation.insert(equation.begin()+place, to_string(answer));
					place--;
				}
				if(i == "log(")
				{	
					if(getbrackets(place, equation) != 1)
						function(place+1, equation);
					
					solve_simple(place, equation);
					
					answer = logarithm(atof(equation.at(place+1).c_str()));
					equation.erase(equation.begin()+place, equation.begin()+place+3);
					
					equation.insert(equation.begin()+place, to_string(answer));
					place--;
				}
				if(i == "ln(")
				{	
					if(getbrackets(place, equation) != 1)
						function(place+1, equation);
					
					solve_simple(place, equation);
					
					answer = ln(atof(equation.at(place+1).c_str()));
					equation.erase(equation.begin()+place, equation.begin()+place+3);
					
					equation.insert(equation.begin()+place, to_string(answer));
					place--;
				}
				if(i == "nPr(")
				{	
					if(getbrackets(place, equation) != 1)
						function(place+1, equation);
					
					solve_simple(place, equation);
					
					answer = npr(atof(equation.at(place+1).c_str()),atof(equation.at(place+3).c_str()));
					equation.erase(equation.begin()+place, equation.begin()+place+5);
					
					equation.insert(equation.begin()+place, to_string(answer));
					place--;
				}
				if(i == "nCr(")
				{
					if(getbrackets(place, equation) != 1)
						function(place+1, equation);
					
					solve_simple(place, equation);
					
					answer = ncr(atof(equation.at(place+1).c_str()),atof(equation.at(place+3).c_str()));
					equation.erase(equation.begin()+place, equation.begin()+place+5);
					
					equation.insert(equation.begin()+place, to_string(answer));
					place--;
				}
				if(i == "rn(")
				{
					if(getbrackets(place, equation) != 1)
						function(place+1, equation);
					
					solve_simple(place, equation);
					
					answer = roundf(atof(equation.at(place+1).c_str()) * pow(10,atof(equation.at(place+3).c_str()))) / pow(10,atof(equation.at(place+3).c_str()));
					equation.erase(equation.begin()+place, equation.begin()+place+5);
					
					equation.insert(equation.begin()+place, to_string(answer));
					place--;
				}
				if(i == "mag(")
				{
					if(getbrackets(place, equation) != 1)
						function(place+1, equation);
					
					solve_simple(place, equation);
					
					if(atof(equation.at(place+1).c_str()) > 0)
						answer = atof(equation.at(place+1).c_str());
					else
						answer = atof(equation.at(place+1).c_str())*-1;
					
					equation.erase(equation.begin()+place, equation.begin()+place+3);
					
					equation.insert(equation.begin()+place, to_string(answer));
					place--;
				}
			}
		}
	}

	return;
}

bool checkequation(std::vector<std::string>& equation)
{
	int open = 0;
	int close = 0;
	
	for(auto &i : equation) 
	{
		for(char& c : i)
		{
			if(c == '(')
				open++;
			else if(c == ')')
				close++;
			if(close > open)
				return true;
		}
	}

	if(open == close)
		return false;
	return true;
}

void replace(std::vector<std::string>& equation)
{
	for(int place = 0; place < equation.size(); place++) 
	{
		if(equation.at(place) == "pi")
			equation.at(place) = to_string(PI);
		if(equation.at(place) == "e")
			equation.at(place) = to_string(E);
	}
	return;
}

std::string solve(std::string equation, int mode)
{		
	g_mode = mode;
	std::vector<std::string> equation_split;
	splitequation(equation, equation_split);
	replace(equation_split);
	
	if(checkequation(equation_split))
		return "Error: Syntax Error";
	
	function(0, equation_split);
	solve_simple(0, equation_split);
	equation = "";
	
	for(auto &i : equation_split) 
		equation += i + "";
	
	return equation;
}


