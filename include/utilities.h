#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <vector>
#include <iostream>
std::string quadratic_solve(std::string equation, int mode);
int factorial(int number);
std::string to_string(double potato);
void search(std::string haystack, std::string needle, std::vector<int>& foundat);
void stringsplit(char splitat, std::string line, std::vector<std::string>& newtext);
#endif
