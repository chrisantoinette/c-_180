#include "Employee.h"


Employee::Employee ()
{

}
Employee::Employee(int x):id(x)
{

}
Employee::Employee (int x, string f, string l, double s): id(x),first_name(f), last_name(l), salary(s)
{

}
string Employee::get_fname() const
{
	return first_name;
}
string Employee::get_lname() const
{
	return last_name;
}
double Employee::get_salary() const
{
	return salary;
}
int Employee::get_id() const
{
	return id;
}

void Employee::set_id(int i)
{
	id = i;
}
void Employee::set_fname(string fname)
{
	first_name = fname;
}
void Employee::set_lname(string lname)
{
	last_name = lname;
}
void Employee::set_salary(double sal)
{
	salary = sal;
}
/*Overload the << output stream insertion operator to write the Employee records
 * The values will be displayed in the proper format
 * @param ostream the output stream.
 * @param s the Employee object to output.
 * @return a reference to the output stream. */
ostream& operator <<(ostream& os, Employee& e)
{
	os << "Employee{ID=" << e.get_id() << ", last=" << e.get_lname() << ", first="
			<< e.get_fname() << ", salary=" << e.get_salary() << "}";
	return os;
}
/*Overload the >> innput stream insertion operator to get the employee records
 * the delimiter operators are removed and the salary which is in string format
 * is converted to a double using the string to double conversion function
 * @param istream the input stream.
 * @param s the Employee object to be input.
 * @return a reference to the input stream. */
istream& operator >>(istream& ins, Employee& e )
{
	string str;
	ins >> ws;
	getline (ins,str, ',');
	e.last_name = str;
	getline (ins,str, ',');
	e.first_name = str;
	getline (ins,str);
	e.salary = atof(str.c_str());
	return ins;
}

