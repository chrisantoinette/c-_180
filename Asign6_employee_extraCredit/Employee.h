#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_
using namespace std;

class Employee
{
public:

    /***** Complete this class. *****/
    Employee ();
    Employee(int x);
    Employee (int x, string f, string l, double s);
    /*Returns the id of the employee*/
    int get_id() const;
    /*Returns the first name of the employee*/
    string get_fname() const;
    /*Returns the last name of the employee*/
    string get_lname() const;
    /*Returns the salary of the Employee*/
    double get_salary() const;
    /*Sets the id of the employee*/
    void set_id(int i);
    /**Sets the first name */
    void set_fname(string fname);
    /*Sets the last name*/
    void set_lname(string lname);
    /*Sets the salary*/
    void set_salary(double sal);
    /* outputs the records in the desired format*/
    friend ostream& operator <<(ostream& os, Employee& emp);
    /*inputs the records and separates them to the
     * corresponding fields.
     */
    friend istream& operator >>(istream& is, Employee& emp );

private:
    int id;	// id of the employee
    double salary; // salary of the employee
    string first_name; // first name of the employee
    string last_name; // last name of the employee
};

#endif /* EMPLOYEE_H_ */
