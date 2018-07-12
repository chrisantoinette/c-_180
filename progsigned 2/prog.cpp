/*
  Read a sequence of integers from cin that is terminated by
  a zero (which is not a part of the sequence). Print out the
  average of the first and last value of the sequence.
  If there is only one value, print it. If there are none, print 0.
  Do not use an array or vector.
*/
#include <iostream>
using namespace std;

  int main()
  {
  int first(0), last(0), input(-1);
  double average(0);

  while (input !=0)
  {
      cin >> input;
      if (first == 0) //first value will not be initialized
      {
          first = input;
      }
      else
      {
          if (input !=0) // store every other value to track last value
          last = input;
      }

    }
    if (first == 0)
    {
        cout << "Average: 0\n"; // output if there is no input
    }
    else if (last == 0)
    {
        cout << "Average: " << first << endl; // output if there is only one input
    }
    else
    {
       average = ((double)first + (double)last)/2; // output if there are more than one input
       cout << "Average: " << average << endl;
    }
    return 0;
  }


