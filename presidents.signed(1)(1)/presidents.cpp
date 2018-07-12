#include<iostream>
#include <fstream>
#include <string>
using namespace std;

const string INPUT_FILE_NAME = "presidents.in";

int main()
{
  /* To check if the file opens or not. If the file does not open display
   * output saying "Failed to open".*/

  ifstream input;
  input.open(INPUT_FILE_NAME);
  if (input.fail())
  {
      cout << "Failed to open " << INPUT_FILE_NAME << endl;
      return -1;
  }

   /*Declare the variables that are used through out this
    *  program is declared here  */

   string first_name("A"), middle_name, last_name, party, buffer, sec_last_name ;
   int   set (0), born(0), age, start_year;
   double average(0), sum(0), count(0);
   char test_lower;
   bool is_firstname_set(false);

   /*The first line of the output , the way it should be
    * displayed with the spaces is coded here */

   cout << "First name " << "Middle name " << "Last name  " << "Born "
         << "Died  " << "Age  " << "Start " << "End   " << "Party" << endl;
   cout << "---------- " << "----------- " << "---------  " << "---- "
         << "----  " << "---  " << "----- " << "----  " << "-----" << endl;

   /* To read the file till it reaches the end of the file.
    * This is checked if the first name is a period (".") or a
    * string which is usually the first name */

   while (first_name.compare(".") != 0)
   {
       /*Declare the variables that should be initialized to 0 every
        * time it reaches the start of the loop*/

      int died(0), end_year(0);

      /* A condition is checked whether the last field of the previous
       *  data is assigned to the first name. If it is assigned then need
       *  not get the first name again   */

      if(is_firstname_set == false)
      {
        input >> first_name;
      }
      else
      {
        first_name = buffer;
        is_firstname_set = false;
      }

      if (first_name.compare(".") == 0)
      {
        break;
      }
      cout.width(10); cout << left << first_name << " ";
      input >> last_name;
      input >> buffer;

      /* Condition is checked if there are Middle names or not by
       * checking if the input value is a parentheses. If it is not a parentheses,
       * then it is further checked if there are two last names  */

      if (buffer.compare("(") != 0)
      {
          test_lower = last_name[0];
          if (test_lower >= 97)
          {
            middle_name = "           ";
            //set = set +1;
            last_name = last_name + " " + buffer;
          }
          else
          {
            middle_name = last_name;
            last_name = buffer;
          }
          input >> buffer;
         if (buffer.compare("(") != 0)
         {
           test_lower = last_name[0];
           if (test_lower >= 97)
           {
             last_name = last_name + " " + buffer;
             input >> buffer;
           }
           else
           {
             middle_name = middle_name + " " + last_name;
             last_name = buffer;
             input >> buffer;
           }
         }

       }
       else
       {
        middle_name = "  ";
       }

      /* Display the output with the correct format and spaces */

       cout.width(11);cout << left << middle_name << " ";
       cout.width(10); cout << left << last_name << " ";

       input >> born >> buffer;
       cout << born << " " ;

       /* Condition is checked if the person has died or still alive.
        * If he is dead then output died year else leave it blank */

       if (buffer.compare("-") == 0)
       {
         input >> died >> buffer;
         cout << died << "  ";
       }
       else
       {
         cout << "      ";
       }

       /* Check if died year is available, if available, calculate the
        *  age and display else leave that column blank. Also if the
        *  age is present for a data keep adding it and also add the
        *  number of persons for whom the age is present*/

       if (died > 0)
       {
         age = died - born;
         cout.width(3); cout << right << age;
         sum = sum + age;
         count = count + 1;
         cout << " ";
       }
       else
       {
         cout << "    ";
       }

       /*To calculate the start and end year of the person*/

       input >> party >> start_year;
       cout.width(6); cout << right << start_year << " ";
       input >> buffer;

       /*Check if the end year is given, if it is not given then
        * the start year is the same as the end year. Also the
        * first name of the next person will be assigned to the end
        * year if it is not given. To handle this condition give a
        * bool switch and check this condition everytime at the
        * beginning of the loop*/

       if (buffer.compare("-") != 0)
       {
         cout.width(4); cout << right << start_year << "  ";
         is_firstname_set = true;
       }
       else
       {
         input >> end_year;
         cout.width(4); cout << right << end_year << "  ";
       }
       cout.width(20); cout << left << party;
       cout << endl;
     }
   /* Calculate the average age of the persons who are dead and display
    * with one precision format*/

   average = sum / count;
   cout.setf(ios::fixed);
   cout.precision(1);
   cout << endl;
   cout << "Average age at death = " << average << endl;

   return 0;

  }


