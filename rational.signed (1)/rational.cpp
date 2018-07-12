#include<iostream>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<cstdlib>
#include<climits>

using namespace std;

const string INPUT_FILE_NAME = "rational.in";
//global functions
//declare class so that return objects for evaluate can be identified
class rational;
//utility used to extract digits
int extract_digit(istream& ins);
//evaluate each line, returns another rational object
rational evaluate(rational& r1,rational& r2,const char op);
//wrapper to evaluate;
void do_problem(rational& r1, rational& r2, const char op);

/*class name : Rational
 * Description : Performs basic arithmetic operations on two given rational numbers
 * input :2 rational numbers in the format specified
 * output : Rational number in the reduced form , mixed or proper fractions
 * private variables: The numerator and denominator of the rational number is private
 * public methods : All the operation methods are friend functions, so that they have the access
 *                  to the numerator and denominator to perform the necessary operations*/
 class rational
 {
 public:

	 rational();
	 rational(int x);
	 rational(int x, int y);
	 void set_numerator(int x);
	 void set_denominator(int y);
	 int get_numerator();
	 int get_denominator();
	 bool check_zero() const;

	 friend rational operator+(const rational& r1, const rational& r2);
	 friend rational operator-(const rational& r1, const rational& r2);
	 friend rational operator*(const rational& r1, const rational& r2);
	 friend rational operator/(const rational& r1, const rational& r2);
	 friend ostream& operator <<(ostream& outs, rational& r);
	 friend istream& operator >>(istream& ins, rational& r);


 private:
	 int numerator;
	 int denominator;
	 void GCD();
 };

 /* Method name : Check_zero
  * Purpose : To check if the numerator or the denominator of the rational number is zero
  * Parameters : The Rational number for which the check should be made
  * Returns : True if either the numerator or the denominator of the rational number is zero
  * */
 bool rational::check_zero() const
   {
 	 bool is_zero = false;
 	 if (!numerator || !denominator)
 	 {
 		 is_zero = true;
 	 }
 	 return is_zero;
   }

 /* Method name :set_numerator
  * Purpose : Setter function that set the value of the numerator
  * Parameters : the numerator value
  * Returns : does not return any value
  * */
void rational::set_numerator(int x)
{
	numerator = x;
}

/* Method name :set_denominrator
 * Purpose : Setter function that set the value of the denominator
 * Parameters : the denominator value
 * Returns : does not return any value
 * */
void rational::set_denominator(int y)
{
	denominator = y;
}

/* Method name :get_numerator
 * Purpose : Getter function that gets the value of the numerator
 * Parameters :no parameters
 * Returns : The value of numerator
 * */
int rational::get_numerator()
{
	return numerator;
}
/* Method name :get_denominator
 * Purpose : Getter function that gets the value of the denominator
 * Parameters :no parameters
 * Returns : The value of denominator
 * */
int rational::get_denominator()
{
	return denominator;
}
/* Construtor name :rational
  * Purpose : default constructor that creates a rational number for 0
  * */
 rational::rational()
 {
	 numerator = 0;
	 denominator = 0;
 }
 /* Construtor name :rational
   * Purpose : constructor with 2 input param
   * */
 rational::rational(int x, int y)
 {
	 numerator = x;
	 denominator = y;
 }
 /* Construtor name :rational
   * Purpose : constructor with input a and initializes b to 1
   * */
 rational::rational(int x)
 {
	 numerator = x;
	 denominator = 1;
 }
 /* Method name :GCD
   * Purpose : Reduces the rational number  to the reduced form
   *           using Euclid’s GCD algorithm
   * Parameters : -
   * Returns : -
   * */
void rational::GCD()
 {
	int big = 0, small = 0, r = INT_MAX, gcd = 0;
 	if (numerator > denominator) {big = numerator; small = denominator;}
 	else { small = numerator; big = denominator; }
 	if (!big || !small)
 	{
 		numerator = 0;
 		denominator = 0;
 		return;
 	}
 	while (r > 1)
 	{
 		r = big % small;
 		big = small;
 		small = r;
 	}
 	if ( r == 0 )
 	{
		gcd = big;
		numerator = numerator/gcd;
		denominator = denominator/gcd;
 	}
 }
/* Operator  : >>
  * Purpose : overloads the >> operator to get the inputs
  * Parameters : istream object and Rational number to be input
  * Returns :  istream object
  * */
istream& operator>>(istream& ins, rational& r)
{
	ins >> ws;  // eat up any leading whitespaces

	int whole = -1, numerator = 0, denominator = 1;
	if(isdigit(ins.peek()))
	{
		whole = extract_digit(ins);
		//cout << "whole: " << whole << endl;
	}
	ins >> ws;
	if(ins.peek() == '(') {ins.get();}
	ins >> ws;
	if(isdigit(ins.peek()))
	{
		numerator = extract_digit(ins);
	}
	ins >> ws;
	if (numerator == 0 && whole > 0)
	{
		//special condition where we have whole numbers only
		//and we dont have zeroes in numerator
		r.numerator = whole;
		r.denominator = 1;
		ins >> ws;
		//check if we have reached the end;
		if(ins.peek() == '=') {ins.get();}ins >> ws;
		return ins;

	}
	if (ins.peek() == '/')
	{
		ins.get();
		denominator = extract_digit(ins);
	}
	ins >> ws;
	if(ins.peek() == ')') {ins.get();}ins >> ws;
	if(ins.peek() == '=') {ins.get();}ins >> ws;
	//cout << "are we reaching?" << ins.peek() << endl;
	if ( whole > 0 && numerator != 0)
	{
		numerator = (denominator * whole) + numerator;
	}
	else if( whole == 0 )
	{
		numerator = 0;
		denominator = 0;
	}
	else if( whole > 0 && numerator == 0 )
	{
		numerator = whole;
	}
	r.numerator = numerator;
	r.denominator = denominator;

	return ins;
}
/* Operator  : <<
  * Purpose : overloads the << operator to display the output values
  * Parameters : ostream object and Rational number to be input
  * Returns :  ostream object
  * */
ostream& operator<<(ostream& outs, rational& r)
{
	 int rem = 0 , d = 0;
	 if(r.denominator == 1)
	 {
		 outs << r.numerator;
		 return outs;
	 }

	 r.GCD();
	 if (r.numerator == 0 && r.denominator == 0)
	 {
		 r.numerator = 0;
		 outs << r.numerator;
		 return outs;
	 }
	 if ( r.denominator == 1)
	 {
		 outs << r.numerator;
		 return outs;
	 }
	 if (r.numerator > r.denominator) // improper fraction to mixed number
	 {
		 d = r.numerator / r.denominator;
		 rem = r.numerator % r.denominator;
		 outs << d << "(" << rem << "/" << r.denominator << ")";
	 }
	 else
	 {
		 outs << "(" << r.numerator << "/" << r.denominator << ")";
	 }
	 return outs;
}
/* Operator  : +
  * Purpose : overloads the + operator to perform addition on 2 objects
  * Parameters : 2 Rational numbers on which the addition is to be made
  * Returns :  resultant rational object
  * */
 rational operator+(const rational& r1, const rational& r2)
 {
	 rational newobj;
	 if (r1.check_zero())
	 {
		 newobj.numerator = r2.numerator;
		 newobj.denominator = r2.denominator;
	 }
	 else if (r2.check_zero())
	 {
		 newobj.numerator = r1.numerator;
		 newobj.denominator = r1.denominator;
	 }

	 else
	 {
		 newobj.numerator = (r1.numerator * r2.denominator) + (r1.denominator * r2.numerator);
		 newobj.denominator = (r1.denominator * r2.denominator);
	 }
	 return newobj;
 }
 /* Operator  : -
   * Purpose : overloads the - operator to perform subtraction
   * Parameters : 2 Rational numbers on which the subtraction is to be made
   * Returns :  resultant rational object
   * */
 rational operator-(const rational& r1, const rational& r2)
 {
	 rational newobj;
	 newobj.numerator = (r1.numerator * r2.denominator) - (r1.denominator * r2.numerator);
	 newobj.denominator = (r1.denominator * r2.denominator);
	 return newobj;

 }
 /* Operator  : *
    * Purpose : overloads the * operator to perform multiplication on 2 objects
    * Parameters : 2 Rational numbers on which the multiplication is to be made
    * Returns :  resultant rational object
    * */
 rational operator*(const rational& r1, const rational& r2)
 {
	 rational newobj;
	 if (r1.check_zero() || r2.check_zero())
	 {
		 newobj.numerator = 0;
		 newobj.denominator = 0;
	 }
	 else
	 {
		 newobj.numerator = (r1.numerator * r2.numerator);
		 newobj.denominator = (r1.denominator * r2.denominator);
	 }
	 return newobj;

 }
 /* Operator  : /
    * Purpose : overloads the / operator to perform division
    * Parameters : 2 Rational numbers on which the division is to be made
    * Returns :  resultant rational object
    * */
 rational operator/(const rational& r1, const rational& r2)
 {
	 rational newobj;
	 if (r1.check_zero() || r2.check_zero())
	 {
		 newobj.numerator = 0;
		 newobj.denominator = 0;
	 }
	 else
	 {
		 newobj.numerator = (r1.numerator * r2.denominator);
		 newobj.denominator = (r1.denominator * r2.numerator);
	 }
	 return newobj;
 }
// main function
 int main()
 {
     // Open the input file.
     ifstream input;
     input.open(INPUT_FILE_NAME);
     if (input.fail())
     {
         cout << "Failed to open " << INPUT_FILE_NAME << endl;
         return -1;
     }

     rational r1, r2;
     char op;
     do    // Read the file till the end of the file is reached
     {
		 input >> r1 >> op >> r2;
		 do_problem(r1, r2, op);
     }while (!input.eof());

     cout << endl << "Done!" << endl;
     return 0;
 }

 /****************************************************************/
 /* Method name : evaluate
   * Purpose : Calls the methods to perform the arithmetic operations
   *           based on the operator given
   * Parameters : 2 rational numbers and the operator
   * Returns : Final value of the operations
   * */
 rational evaluate (rational& r1,rational& r2, const char op)
  {
 	 rational final_value;
 	 switch (op)
 	 {
 	  case '+':
 		  final_value = r1 + r2;
 		  break;
 	  case '-':
 		  final_value = r1 - r2;
 		  break;
 	  case '*':
 		  final_value = r1 * r2;
 		  break;
 	  case '/':
 		  final_value = r1 / r2;
 		  break;
 	  default:
 		  cout << "invalid numbers\n" << endl;
 	 }
 	 return final_value;
  }
 /****************************************************************/
 /* Method name :do_problem
   * Purpose : calls the evaluate method and places the final value in he result
   *           outputs the result in the reduced form
   * Parameters :  2 rational numbers and the operator
   * Returns : -
   * */
  void do_problem(rational& r1,rational& r2, const char op)
  {
      rational result = evaluate(r1, r2, op);
      cout << r1 << " " << op << " " << r2 << " = " << result << endl;

  }
  /****************************************************************/
  /* Method name :extract_digit
    * Purpose : gets the digits from the input file
    * Parameters : object from which he input is got, here its a file
    * Returns : Integer value
    * */
 int extract_digit(istream& ins)
 {
 	int ret = 0;
 	try
 	{
 		string digit;

 		while(isdigit(ins.peek()))
 		{
 			char c = ins.get();
 			digit = digit + c;
 		}
 		ret = stoi(digit);
 	}
 	catch(exception& e)
 	{
 		ret = 0;
 		cout << "exception:" << e.what() << endl;
 	}

 	return ret;
 }


