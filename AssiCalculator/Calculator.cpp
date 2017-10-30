#include <iostream>
#include "Calculator.h"
#include<string>

using namespace std;

Calculator::Calculator()
{

}
Calculator::Calculator(string str):expres(str)
{

}
string Calculator::get_str()
{
	return expres;
}

double Calculator::calc(string str)
{
	double result = 0;
	bool equal = false;
	try
	{
		result = get_expression(str);
	}
	catch(string& s)
	{
		cout << s << endl;
	}
	if(str.substr(str.length()-1) == "=")
		{
			str.erase(str.length()-1);
			equal = true;
		}
		else if(!equal)
		{
			cout << "Missing '=', Expression not complete, therefore \n";
			return 0;
		}
	return result;
}
double Calculator::get_factor(string str) throw(string)
{
	double this_number = 0;
	if(str.empty()){ return 0;}
	if (str[0] == '(' && str[str.length()-1] == ')')
	{

		string p_expr = str.substr(1,str.length()-2 );
		this_number = get_expression(p_expr);
	}

	else
	{
		try
		{
			this_number = stod(str);
		}
		catch(exception& e)
		{
			throw string("***Unexpected bracket.\nEnter valid Expression");
		}
	}
	return this_number;
}
double Calculator::get_term(string str) throw(string)
{
	int index = 0;
	double this_factor = 0;

	if(str.empty()){ return 0;}

	bool found = false;

	int len = 0;
	int open_brace = str.find('(');
	if( open_brace == string::npos )
	{
		len = str.length();
	}
	else
	{
		len = open_brace;
	}
	for(int i = 0; i < len; i++)
	{
		if(str[i] == '*')
		{
			this_factor = get_factor(str.substr(index, i-index)) * get_factor(str.substr(i+1));
			index = i;
			found = true;
			break;
		}
		if(str[i] == '/')
		{
			double den = get_factor(str.substr(i+1));
			double num =  get_factor(str.substr(index, i-index));
			if( den == 0 )
				throw string("***Divide by Zero Error");

			this_factor = num / den ;

			index = i;
			found = true;
			break;
		}
		if(str[i] == '%')
		{
			cout << "*** Unexpected %" << endl;
			break;
		}
	}
	if(!found)
	{
		this_factor = get_factor(str);
	}

	return this_factor;
}
double Calculator::get_expression(string str) throw(string)
{
	int len = 0;
	int index = 0;
	bool found = false;
	double this_term = 0;


	if(str.empty()){ return 0;}

	int open_brace = str.find('(');
	if( open_brace == string::npos ) // if '(' is not present the len = entire string
	{
		len = str.length();
	}
	else
	{
		len = open_brace;
	}
	for(int i = 0; i < len; i++)
	{
		if(str[i] == '+')
		{
			//cout << "expr: " << str.substr(index, i-index) << "   " <<  str.substr(i+1) << endl;
			this_term = get_term(str.substr(index, i-index)) + get_term(str.substr(i+1));
			index = i;
			found = true;
			break;
		}
		if(str[i] == '-')
		{
			this_term =  get_term(str.substr(index, i-index)) -  get_term(str.substr(i+1));
			index = i;
			found = true;
			break;
		}
	}
	if(!found)
	{
		this_term = get_term(str);
	}
	return this_term;

}
