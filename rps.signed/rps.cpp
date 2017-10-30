/*
 * Author : Chris Sahaaya Seelan
 * Date created: 02 / 07 / 2017
 * Problem : Rock Paper Scissors
 * */
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

#define playcount 20

//The functions and the enumeration data types are declared

//possible choices
enum choice {rock, paper, scissors,others};
//possible outcomes of the game
enum outcome{tie, human, computer};

// generate computer's choice
int comp_choice();
// obtain human's choice
choice get_selection(char ch);
//use the obtained computers choice & human choice to get winner
outcome calc_win(int human_select, int comp_select);
//based on win, update counters
void record_win(outcome win, int& human_win, int& comp_win, int& tie);


int main()
{
	char ch;
	srand(time(0));	//generate random seed
	choice human_select; //human choice
	outcome win; //gets current win
	int comp_select, human_win(0), comp_win(0), tie(0), count(1);

	/*The game is played for "playcount" times */
	while (count <= playcount)
	{
		cout << "\n\tRound " << count << endl;
		cout << "Choose an option R,P,S";
		cin >> ch;
		comp_select = comp_choice();
		human_select =  get_selection(ch);
		count++;

		if(human_select == choice::others)
		{
			//do no proceed for invalid input
			continue;
		}
		 win = calc_win(human_select,comp_select);
		 record_win(win, human_win,  comp_win, tie);
	}
	//output format
	cout << "\n\n   Summary:\n"
			"   -------\n\n";
	cout << "Total human win : " << human_win <<endl;
	cout << " Total comp win : " << comp_win << endl;
	cout << "     Total ties : " << tie << endl;


	return 0;
}

/*------------------------------------------------------------------------------------------------------*/
outcome calc_win(int human_select, int comp_select)
 {
	outcome ret;
		if (human_select == comp_select)
		{
			//same choices are ties
			ret= outcome::tie;
		}
		//game logic goes here
		else if (((human_select == choice::paper) && (comp_select == choice::rock)) ||
		 ((human_select == choice::rock) && (comp_select == choice::scissors)) ||
		 ((human_select == choice::scissors) && (comp_select == choice::paper)))
		{
			ret = outcome::human;
		}
		else
		{
			ret = outcome::computer;
		}

		return ret;
 }

/*------------------------------------------------------------------------------------------------------*/
choice get_selection(char ch)
{
	choice human_select;
	switch (ch)
				{
				case 'r':
				case 'R':
					human_select = choice::rock;
					cout << "You have chosen rock\n";
					break;
				case 'p':
				case 'P':
					human_select = choice::paper;
					cout << "You have chosen paper\n";
					break;
				case 's':
				case 'S':
					human_select = choice::scissors;
					cout << "You have chosen scissors\n";
					break;
				default:
					human_select = choice::others;
					cout << "Wrong selection, try again\n";
					break;
				}
	return human_select;
}
/*------------------------------------------------------------------------------------------------------*/
int comp_choice()
{
	int comp_select;
	comp_select = rand() % 3;
	if (comp_select == choice::rock )
	{
		cout << "The computer has chosen rock\n";
	}
	else if (comp_select == choice::paper )
	{
		cout << "The computer has chosen paper\n";
	}
	else if (comp_select == choice::scissors )
	{
		cout << "The computer has chosen scissors\n";
	}
	return comp_select;
}

/*------------------------------------------------------------------------------------------------------*/
void record_win(outcome win, int& human_win, int& comp_win, int& ties)
{
	//use the reference obtained above to update results;
	if (win == outcome::tie)
	{
		ties = ties + 1;
		cout << "Tie = " << ties << endl;
	}

	if (win == outcome::human)
	{
		human_win = human_win + 1;
		cout <<  "Human win = " << human_win << endl;
	}

	if (win == outcome::computer)
	{
		comp_win = comp_win + 1;
		cout << "computer win = "<< comp_win << endl ;
	}

}

/*-------------------------------------------------------------------------------------------*/
