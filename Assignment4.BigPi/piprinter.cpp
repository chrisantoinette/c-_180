//============================================================================
// Name        : assignment_4week.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <stdio.h>
#include <mpir.h>
#include <iostream>
#include <iomanip>

#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;
const char* INPUT_FILE_NAME 	= "output.txt";
const int MAX_ITERATIONS 		= 6;
const int PLACES         		= 1000;        // desired decimal places
const int PRECISION      		= PLACES+1;  	// +1 for the digit 3 before the decimal

const int BASE       			= 10;  // base 10 numbers
const int BIT_COUNT  			= 8;   // bits per machine word

const int BLOCK_SIZE 			= 10;                // print digits in blocks
const int LINE_SIZE  			= 100;               // digits to print per line
const int LINE_COUNT 			= PLACES/LINE_SIZE;  // lines to print
const int GROUP_SIZE 			= 5;                 // line grouping size

/***** Function declarations here. *****/
void print(const mpf_t& pi);

/**
 * The main.
 * Set constants, initialize variables, and iterate
 * to compute pi to the desired number of decimal places.
 */
int main()
{
	//set default precision
	mpf_set_default_prec(BIT_COUNT*PRECISION);  // precision in bits

	//constants that we need in float format
    mpf_t one; mpf_init_set_str (one,"1",BASE);
    mpf_t two; mpf_init_set_str (two, "2", BASE);
    mpf_t four; mpf_init_set_str (four, "4", BASE);
    mpf_t six; mpf_init_set_str (six, "6", BASE);


    mpf_t ao;	        mpf_init (ao);		//ao = 6-(4*sqrt(2))
    mpf_t yo;	        mpf_init (yo); 		//yo = sqrt(2) - 1;
    mpf_t a; 	        mpf_init (a);
    mpf_t y;	        mpf_init (y);
    mpf_t sqr2;	        mpf_init (sqr2); 	//square root of 2
    mpf_t asub;	        mpf_init (asub); 	//4*sqrt(2)

    mpf_sqrt(sqr2,two);              //square root of 2
    mpf_sub(yo,sqr2,one);           //yo = sqrt(2) - 1;
    mpf_mul(asub, four, sqr2);      //4*sqrt(2)
    mpf_sub(ao, six, asub);         //ao = 6-(4*sqrt(2))

    //entering loop
    for (unsigned int i = 1; i <= MAX_ITERATIONS; i++)
    {
        mpf_set_ui(y,0);
        mpf_set_ui(a,0);

        mpf_t up;   		mpf_init (up);				//(1 - pow(1-pow(yo, 4), (1/4)))
        mpf_t down;         mpf_init (down);			//(1 + pow(1-pow(yo, 4), (1/4)))
        mpf_t i_sub;	    mpf_init (i_sub);			//1-pow(yo, 4)
        mpf_t pow_yo;	    mpf_init (pow_yo); 			//pow(yo, 4)
        mpf_t root; 	    mpf_init (root);			// pow(1-pow(yo, 4), (1/4))
        mpf_t root1; 	    mpf_init (root1);			// pow(1-pow(yo, 4), (1/4))
        mpf_t y_pow2; 	    mpf_init (y_pow2); 			// y^2;
        mpf_t one_y;	    mpf_init (one_y); 			// (1+y)
        mpf_t y_term2;	    mpf_init (y_term2); 		//(1 + y + y^2)
        mpf_t y_term1;	    mpf_init (y_term1); 		//y *(1 + y + y^2)
        mpf_t cpp_2; 	 	mpf_init (cpp_2);			// 2 *i;
        mpf_t c_pow; 	 	mpf_init (c_pow);			// (2*i) + 1
        mpf_t c_pow2;	 	mpf_init (c_pow2);			//2 ^ (2*i) + 1
        mpf_t one_y_pow4;	mpf_init (one_y_pow4); 		// (1+y)^4
        mpf_t afirst_val;	mpf_init (afirst_val);		//ao * (1+y) ^4
        mpf_t asec_val;	    mpf_init (asec_val);		// [2 ^ (2*i) + 1] * [y *(1 + y + y^2)]

        //numerator
        mpf_pow_ui (pow_yo ,yo, 4);        						//pow(yo, 4)
        mpf_sub(i_sub, one, pow_yo);        					//1-pow(yo, 4)
        mpf_sqrt(root1,i_sub);									//replacing 1/4 power by two 1/2s and multiplying
        mpf_sqrt(root,root1);
        mpf_sub(up, one, root); 								//(1 - pow(1-pow(yo, 4), (1/4)))

        //denominator
        mpf_add(down, one, root); 								// (1 + pow(1-pow(yo, 4), (1/4)))

        //yi calculation
        mpf_div (y, up, down);  								// y

        //a calculation
        mpf_pow_ui(y_pow2, y, 2);  								// y^2;
        mpf_add_ui(one_y, y, 1);     							// (1+y)
        mpf_add(y_term2 , one_y, y_pow2);   					//(1 + y + y^2)
        mpf_mul(y_term1, y, y_term2);  							//y *(1 + y + y^2)

        //2 power i + 1 calculation
        mpf_mul_2exp(c_pow2,one,((2*i)+1));
        mpf_mul (asec_val, c_pow2, y_term1) ; 					// [2 ^ (2*i) + 1] * [y *(1 + y + y^2)]
        mpf_pow_ui(one_y_pow4, one_y, 4); 						// (1+y)^4
        mpf_mul (afirst_val, ao, one_y_pow4);                   //ao * (1+y) ^4
        mpf_sub (a, afirst_val,asec_val); 						// [ao * (1+y) ^4] - [2 ^ (2*i) + 1] * [y *(1 + y + y^2)]

        //swap logic
        mpf_swap(yo,y);
        mpf_swap(ao,a);
    }
    mpf_ui_div(ao,1,a);
    //1/pi is complete
    //gmp_printf ("%.*Ff\n" ,1000, ao);


    print(ao);

    return 0;
}
/*****************************************************************/

void print(const mpf_t& pi)
{
	char* output = NULL;
	string out2;
	int count = 0;
	char* ret = NULL;
	fstream fout;
	fout.open (INPUT_FILE_NAME);
	 if (fout.fail())
	{
		cout << "Failed to open " << INPUT_FILE_NAME << endl;
		return;
	}

	long int exp(0);
	//cout << "calling string" << endl;
    ret =  mpf_get_str(output, &exp, BASE, PRECISION, pi);
    if(!ret)
    {
    	cout << "invalid string returned from mpf_get_str" << endl;
    	return;
    }

	string out (ret); //cast the const char* to string for ease of use
	for(int i = 0; i < exp; i++)
	{
	   fout << out[i];
	}
	fout << '.';
	for (int k = exp; k < PRECISION; k+=LINE_SIZE)
	{
	   for ( int i = k; i < k+LINE_SIZE; i+=LINE_COUNT)
	   {
		   for( int j = i; j < i+BLOCK_SIZE; j++)
		   {
			   fout << out[j];
		   }
			fout << " ";
		}
	   fout << endl;
	   fout << "  ";
	   count++;
	   if (count == GROUP_SIZE)
	   {
		   count = 0;
		   fout << endl;
		   fout  << "  ";
	   }
	}
	fout.close();

}






