//Sam Fenimore Program 7 11/10/15

#include <iostream>
#include <cctype>
#include <cstdlib>

using namespace std;

void match(char, char&);
void error();
double expr(char&);
double Term(char&);
double Factor(char&);
double RealNum(char&);
void N(char&);

int main(void)
{
	char curr;
	cout << "Input an expression: ";
	cin.get(curr);
	cout << "Expression evaluates to " << expr(curr) << endl;
}
void match(char lookahead, char& curr)
{
	if (curr == lookahead)
		cin.get(curr);
	else error();
}

void error()
{
	cout << "syntax error" << endl;
	exit(1);
}
double expr(char& curr)
{
    bool negative = false;
    double result;
    N(curr);
    if(curr == '+' || curr == '-')
    {
        if(curr == '-')
        {
            negative = true;
        }
        match(curr, curr);
    }
    result = Term(curr);
    if (negative) result = -result;
    while(curr == '+' || curr == '-')
    {
        N(curr);
        if(curr == '+')
        {
            match('+', curr);
            result = result + Term(curr);
        }
        else
        {
            match('-', curr);
            result = result - Term(curr);
        }
        N(curr);
    }
    return result;
}
double Term(char& curr)
{
    N(curr);
    double result;
    result = Factor(curr);
    while(curr == '*' || curr == '/')
    {
        N(curr);
        if(curr == '*')
        {
            match('*', curr);
            result = result * Factor(curr);
        }
        else
        {
            match('/', curr);
            result = result / Factor(curr);
        }
        N(curr);
    }
}
double Factor(char& curr)
{
    N(curr);
    double result;
    if(curr == '+' || curr == '-' || isdigit(curr))
    {
        result = RealNum(curr);
    }
    else if(curr == '(' || curr == ' ')
    {
        N(curr);
        match('(', curr);
        N(curr);
        expr(curr);
        N(curr);
        match(')', curr);
        N(curr);
    }
    else
    {
        cout<<"FactorError\n";
        error();
    }
}
double RealNum(char& curr)
{
    N(curr);
    double result;
    N(curr);
    cin.unget();
    N(curr);
    cin >> result;
    N(curr);
    cin.get(curr);
    N(curr);
    return result;
}
void N(char& curr)
{
    if(curr == ' ')
    {
        match(' ', curr);
        N(curr);
    }
}
