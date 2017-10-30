#include "Employee.h"
#include<vector>
#include<cfloat>
#include <iomanip>
using namespace std;
/*An enumerator to get the error codes that are received */
enum ERROR_CODE {NO_ERROR, DUPLICATE, NOT_FOUND, INVALID_COMMAND};
/* Method name :Execute
 * Purpose : Performs operation on the records like inserting a
 *           new record, deleting an existing record and returning the
 *           details of the records requested
 * Parameters : The command ('+' to insert a record, '-' to delete a record,
 * 			  '?' to return the details of the records) , the employee list ,
 * 			  and the input from the file.
 * Returns : -
 * */
void execute (char c, vector<Employee>& employees, istream& inp);
/* Method name :search_index
 * Purpose :  Search the given employee id in the list
 * Parameters : Employee list and the employee id
 * Returns : True if the record is present , False if the record is not
 * 				present
 * */
int search_index(vector<Employee>& elist, int id);
/* Method name :handle_error
 * Purpose :  To display the error in the specified format
 * Parameters : The error code.
 * */
void handle_error(ERROR_CODE& err_code);
/* Method name : add_records
 * Purpose : To add the records in the list for a given record
 * Parameters : Employee list and the employee record
 * Returns : Error code 'Duplicate' if the employee records are already
 *          in the list , 'No-error' if the new record is successfully inserted
 * */
ERROR_CODE add_records(vector<Employee>& employees,Employee emp);
/* Method name :remove_records
 * Purpose : To delete a particular record from the list
 * Parameters : The Employee list and the employee id
 * Returns : Error code'Not- Found' id the id is not in the list
 * 			'no-error' if the record is successfully deleted
 * */
ERROR_CODE remove_records(vector<Employee>& employees,Employee& emp,int x);
/* Method name :get_records
 * Purpose : To get the records of an employee in the list if present
 * Parameters : Employee list and the id to return records
 * Returns : Error code'Not- Found' id the id is not in the list
 * 			'No-error' if the record is found
 * */
ERROR_CODE get_records(vector<Employee>& elist, Employee& e, int eid);
/* Method name :print_all
 * Purpose : Prints all the employee records in the list in the proper
 * 				format
 * Parameters : Employee list
 * */
void print_all( vector<Employee>& elist );
/* Method name :print_stats
 * Purpose : Prints the maximum, minimum and the verage salary in the
 *           records
 * Parameters : Employee list
 * */
void print_stats( vector<Employee>& elist );

const string INPUT_FILE_NAME = "commands.in";

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

    char command;
    vector<Employee> list;
    input >> command;
    while (!input.eof())
    {
        execute(command, list,input);
        input >> command;
    }
    print_all(list);
    print_stats(list);
    return 0;
}
/********************************************************************/

ERROR_CODE add_records(vector<Employee>& employees, Employee emp)
{
	int mid = search_index(employees, emp.get_id());
	if(mid != -1)
	{
		return ERROR_CODE::DUPLICATE;
	}

	//employees.insert(employees.begin() + mid, emp);

	vector<Employee>::iterator it;
	bool inserted = false;
	for (it = employees.begin(); it != employees.end(); it++)
	{
		if((*it).get_id() > emp.get_id())
		{
			//employees.resize(employees.size()+1);
			it = employees.insert(it, emp);
			return ERROR_CODE::NO_ERROR;
		}
	}
	employees.push_back(emp);
	return ERROR_CODE::NO_ERROR;
}

/******************************************************************************/
ERROR_CODE remove_records(vector<Employee>& employees, Employee& emp, int eid)
{
	int mid = search_index(employees, eid);
	if(mid == -1)
	{
		return ERROR_CODE::NOT_FOUND;
	}
	employees.erase(employees.begin() + mid);
	return ERROR_CODE::NO_ERROR;
}
/*****************************************************************************/
ERROR_CODE get_records(vector<Employee>& elist, Employee& e,int eid)
{
	int mid = search_index(elist, eid);
	if( mid == -1)
	{
		return ERROR_CODE::NOT_FOUND;
	}
	e = elist[mid];
	return ERROR_CODE::NO_ERROR;
}
/***************************************************************************/
int search_index(vector<Employee>& elist, int eid)
{
	int high = elist.size() -1;
	int low = 0;
	while (low <= high)
	{
		int mid = (low + high) /2;
		if (eid == elist[mid].get_id())
		{
			return mid;
		}
		else if (eid >  elist[mid].get_id())
		{
			low = mid+1;
		}
		else
		{
			high = mid -1;
		}
	}
	return -1;  // id is not found in the list
}

/********************************************************************/

void execute (char cmd, vector<Employee>& employees, istream& inp)
{
	int id;
	string str;
	Employee new_emp;

	inp >> ws;
	char c = inp.peek();
	while ( c != ',' && c != '\n' && c != ' ')
	{
		str+= c;
		inp.get(); // throw the character which was already used
		c = inp.peek(); //peek the next character
	}
	inp.get();
	id = stoi(str);
	cout << cmd << " " <<id <<": ";
	if (c == ',') //there is an Employee object next!
	{
		new_emp.set_id(id);
		inp >>  new_emp;
	}
	ERROR_CODE ret = ERROR_CODE::NO_ERROR;
	switch(cmd)
	{
		case '+':
			ret = add_records(employees, new_emp);
			break;
		case '-':
			ret = remove_records(employees,new_emp,id);
			break;
		case '?':
			ret = get_records(employees,new_emp,id);
			break;
		default:
			ret = ERROR_CODE::INVALID_COMMAND;
			break;
	}
	if(ret != ERROR_CODE::NO_ERROR)
	{
		handle_error(ret);
	}
	else
	{
		cout << new_emp;
	}
	cout << endl;
}
/**************************************************************/
void handle_error(ERROR_CODE& err_code)
{
	if(err_code == ERROR_CODE::DUPLICATE)
	{
		cout << "*** Duplicate ID ***";
	}
	else if(err_code == ERROR_CODE::NOT_FOUND)
	{
		cout << "*** ID not found ***";
	}
	else if(err_code == ERROR_CODE::INVALID_COMMAND)
	{
		cout << "*** Invalid command ***";
	}
}
/************************************************************/
void print_all( vector<Employee>& elist )
{

	vector<Employee>::iterator it;
	cout << endl << "All employees" <<endl;
	cout << "-------------"<<endl;
	for (it = elist.begin(); it != elist.end(); it++)
	{
		cout << (*it) << endl;
	}
	cout << endl;
}
/**********************************************************/
void print_stats( vector<Employee>& elist )
{
	double min_salary = DBL_MAX;
	double max_salary = DBL_MIN;
	double avg_salary = 0.0;
	double sum_salary = 0.0;
	vector<Employee>::iterator it;
	for (it = elist.begin(); it != elist.end(); it++)
	{
		double this_salary = (*it).get_salary();
		if( this_salary < min_salary)
		{
			min_salary = this_salary;
		}
		if(this_salary > max_salary)
		{
			max_salary = this_salary;
		}
		sum_salary += this_salary;
	}
	int recordsize = elist.size();
	avg_salary = sum_salary / (static_cast<double>(recordsize));
	cout << "Statistics" << endl;
	cout << "----------" << endl;

	cout << "Minimum salary = $ " << std::right << std::fixed << setprecision(2) << min_salary << endl;
	cout << "Maximum salary = $" << std::right << std::fixed << setprecision(2) << max_salary << endl;
	cout << "Average salary = $" << std::right << std::fixed << setprecision(2) << avg_salary << endl;
}
