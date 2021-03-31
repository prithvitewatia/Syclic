#include<stack>
#include<string>
#include<vector>
#include<cmath>
#include<iostream>
#include<algorithm>

// Converts an infix string to postfix string
std::string to_postfix(std::string infix_str);
// evaluates the postfix string
double evaluate_postfix(std::string postfix_str);