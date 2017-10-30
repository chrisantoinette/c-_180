 /*|Assignment:  Assignment number : [10]
   |Author:  Chris Antoinette Sahaaya Seelan*/


#include<iostream>
#include<string>
#include "Calculator.h"
#include<list>


using namespace std;
double calculate(string s); // Wrapper function to call the calculate function
int main()
{
	string input;
	do
	{
		try
			{
				cout<< "Expression ? " ;
				cin >> input;

				if (input != ".")
				{
					double r = calculate(input);
					cout << "Result = " << r << endl;
				}
				else throw(input);

			}
			catch(string i)
			{
				cout << "END\n";
			}
	}while (input != ".");
	return 0;
}
/***********************************************/
double calculate(string s)
{
	Calculator c;
	double result = c.calc(s);
	return result;
}
