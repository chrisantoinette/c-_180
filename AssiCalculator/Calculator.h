
#ifndef CALCULATOR_H_
#define CALCULATOR_H_
#include<string>
using namespace std;
/*class name : Calculator
 * Description : Performs basic calculator operations on  given double numbers
 * input :any number of double numbers
 * output :The result of calculation
 * private variables: The input string from the user
 * public methods :functions that classifies the expression into factors and terms making it easy for operation */

class Calculator
{
public:
	Calculator();
	Calculator(string str);
	string get_str();
/* Method name :calc
  * Purpose : To perform calculation
  * Parameters : Input string
  * Returns : the final result
  * */
	double calc(string str);
/* Method name :
  * Purpose :
  * Parameters : Input string
  * Returns : the final result
  * */
	double get_factor(string str) throw(string);
/* Method name :get_factor
  * Purpose :to get the factor , the number
  * Parameters : Input string
  * Returns : the final number
  * */
	double get_term(string str) throw(string);
/* Method name :get_term
  * Purpose : To return a double value
  * Parameters : Input string
  * Returns : the final result
  * */
	double get_expression(string str) throw(string);

private:
	string expres;
};



#endif/* CALC_ULATOR_ */
