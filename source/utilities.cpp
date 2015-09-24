#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <sstream>

std::string char_to_string(char c)
{
	std::string s;
	s.push_back(c);
	return s;
}

int factorial(int n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

std::string to_string(double potato) { std::stringstream moo; moo << potato; return moo.str(); }

void search(std::string haystack, std::string needle, std::vector<int>& foundat)
{
	int place = -1;
	
	foundat.clear();
	
	while(true)
	{
		place = haystack.find(needle, place+1);
		if (place == haystack.npos)
			break;
		foundat.push_back(place);
	}

	return;
}

void stringsplit(char splitat, std::string line, std::vector<std::string>& newtext)
{
	std::string word = "";
	
	newtext.clear();
	
	for(int z = 0; z < line.size(); z++)
	{
		if(line[z] == splitat)
		{
			newtext.push_back(word);
			word = "";
		}
		else
			word += line[z];
	}
	
	newtext.push_back(word);
}
