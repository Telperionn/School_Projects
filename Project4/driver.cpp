//*******************************************************************************
//	Programmer: Patrick Sadowy
//	Instructor: Professor Streller
//	Course: cs232
//	Date: 5/6/21
//	Program name: Project 4
//	File: driver.cpp
//	Input Files: User entered input files, txt required
//	Output Files: there are no output files
//	Modules used: pair.h
//				  table.h
//	Purpose: This program is a finite state machine which accepts a user entered
//			input key as part of a combination to either "unlock" or "alarm" 
//			accordingly. If correct sequence is entered, unlock. If at any time a
//			wrong key is entered, alarm will go off. An action table and transition
//			table are files entered by the user (pre formatted), and placed in a
//			Hash table. 
//			 
//*******************************************************************************



#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include "table.h"
#include "pair.h"

using namespace std;

enum fsm_curstate { nke = 0, ok1, ok2, ok3, fa1, fa2, fa3 };
fsm_curstate getstate(string item);
int f(Pair<char, string> c);

int main()
{
	int n = 35, k=0; //l x w of table. l = 5, w = 7. n = 35.
	Table<Pair<char, string>, string> Transitiontable(n,f), Actiontable(n,f);
	

	ifstream inFile1;
	Pair <Pair<char, string>, string> temp;
	string filename1, tempstring1, tempstring2;

	cout << "Please enter a filename for Action table: " << endl;
	getline(cin, filename1);
	inFile1.open(filename1.c_str());

	if (!inFile1)
	{
		cout << " Incorrect file path for Action table. Terminating program." << endl;
		exit(0);
	}

	//for action table
	inFile1 >> tempstring1;
	//read in the User input character
	getline(inFile1, tempstring2);

	//append to end process string
	tempstring1.append(tempstring2);
	tempstring1.erase(std::remove_if(tempstring1.begin(), tempstring1.end(), ::isspace), tempstring1.end());
	
	//empty initialization so proper value can be entered
	temp.first.second = ""; 

	//for action table
	while (inFile1 >> tempstring2)//read in column state, match with row
	{
		//unchecked is entire row, pre process. 
		//checked is row post process.
		string unchecked, checked;
		
		temp.first.second = tempstring2;
		
		getline(inFile1, unchecked);

		//begin processing string by first
		//removing whitespace from input string 
		unchecked.erase(std::remove_if(unchecked.begin(), unchecked.end(), ::isspace), unchecked.end());
		
		//if string size is 0 then empty row. ie no new information
		if (unchecked.size() == 0) 
		{
			continue;//move to next input line
		}

		//processing step two, separate any values into specific words
		//representing values. either alarm or unlock
		for (int i = 0; i < unchecked.size(); i++)
		{
			checked = unchecked[i];
			temp.second.append(checked);
			

			//character is m, or k then end of word for this specific file. 
			//put into temp's value, and add to action table
			if (unchecked[i] == 'm' || unchecked[i] == 'k')//(temp.second[j] == 'm' || temp.second[j] == 'k')
			{
				cout << " Unchecked i : " << unchecked[i] << endl;
				cout << "Temp second: " << temp.second << endl << endl;

				//add A,B,C,D or E to temp Pair, following tempstring1, 
				//to insert into action table
				if (k == tempstring1.size())
				{
					k = 0;
				}
				if (k < tempstring1.size())
				{
					//put Charcter entry into correct index
					temp.first.first = tempstring1[k]; 
					k++;
				}
				Actiontable.insert(temp);
				temp.second = "";
			}
		}
	}
	inFile1.close();
	cout << "Printing the Action table: " << endl;
	Actiontable.print();
	cout << endl << endl;





	//for transition table
	cout << "Please enter a filename for Transition table: " << endl;
	getline(cin, filename1);
	inFile1.open(filename1.c_str());

	if (!inFile1)
	{
		cout << " Incorrect file path for Transition table. Terminating program." << endl;
		return 0;
	}

	//for transition table
	inFile1 >> tempstring1;
	getline(inFile1, tempstring2);
	tempstring1.append(tempstring2);
	tempstring1.erase(std::remove_if(tempstring1.begin(), tempstring1.end(), ::isspace), tempstring1.end());

	//for transition table
	while (inFile1 >> tempstring2)//read in column, match with row
	{
		temp.first.second = tempstring2; //put 2nd part of entry into index
		for (int k = 0; inFile1.peek() != '\n'; k++)
		{
			if (k >= tempstring1.size())
			{
				break;
			}
			//put Charcter entry into correct index
			temp.first.first = tempstring1[k];
			inFile1 >> tempstring2;
			temp.second = tempstring2;
			Transitiontable.insert(temp);
		}


	}
	inFile1.close();
	cout << "Printing the Transition table: " << endl;
	Transitiontable.print();


	//making fsm
	fsm_curstate cur_state = nke;
	string convert;
	Pair<char, string> user_inputkey;
	user_inputkey.second = "nke";
	//prompt user for input

	//looping question for input combination
	do
	{
		//user entered input key
		cout << endl << "enter input key: " << endl;
		cin >> user_inputkey.first;
		
		//match entry with action/transition table mapping
		//to output the correct response. either alarm or unlock
		//uses enumeration values of state string 
		switch (cur_state)
		{
		case nke:
			switch (user_inputkey.first)
			{
			case 'A':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				break;
			case 'B':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				break;
			case 'C':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				break;
			case 'D':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				break;
			case 'E':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				break;

			}
			break;
		case ok1:
			switch (user_inputkey.first)
			{
			case 'A':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				break;
			case 'B':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				break;
			case 'C':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				break;
			case 'D':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				break;
			case 'E':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				break;

			}
			break;
		case ok2:
			switch (user_inputkey.first)
			{
			case 'A':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				break;
			case 'B':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				break;
			case 'C':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				break;
			case 'D':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				break;
			case 'E':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				break;

			}
			break;
		case ok3:
			switch (user_inputkey.first)
			{
			case 'A':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				cout << endl << Actiontable.lookUp(user_inputkey);
				break;
			case 'B':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				cout << endl << Actiontable.lookUp(user_inputkey);
				break;
			case 'C':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				cout << endl << Actiontable.lookUp(user_inputkey);
				break;
			case 'D':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				cout << endl << Actiontable.lookUp(user_inputkey);
				break;
			case 'E':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				cout << endl << Actiontable.lookUp(user_inputkey);
				break;

			}
			break;
		case fa1:
			switch (user_inputkey.first)
			{
			case 'A':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				break;
			case 'B':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				break;
			case 'C':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				break;
			case 'D':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				break;
			case 'E':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				break;

			}
			break;
		case fa2:
			switch (user_inputkey.first)
			{
			case 'A':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				break;
			case 'B':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				break;
			case 'C':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				break;
			case 'D':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				break;
			case 'E':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				break;

			}
			break;
		case fa3:
			switch (user_inputkey.first)
			{
			case 'A':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				cout << endl << Actiontable.lookUp(user_inputkey);
				break;
			case 'B':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				cout << endl << Actiontable.lookUp(user_inputkey);
				break;
			case 'C':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				cout << endl << Actiontable.lookUp(user_inputkey);
				break;
			case 'D':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				cout << endl << Actiontable.lookUp(user_inputkey);
				break;
			case 'E':
				convert = Transitiontable.lookUp(user_inputkey);
				cur_state = getstate(convert);
				cout << endl << Actiontable.lookUp(user_inputkey);
				break;

			}
			break;
		}

		user_inputkey.second = convert;
		if (cur_state == nke)
		{
			char question;
			cout << endl << "Would you like to run again? (y/n)" << endl;
			cin >> question;
			if (question == 'n' || question == 'N')
			{
				return 0;
			}
		}
	}while (true);
	

	return 0;
}

fsm_curstate getstate(string item)
{

	if (item == "nke")
	{
		return fsm_curstate::nke;
	}
	if (item == "ok1")
	{
		return fsm_curstate::ok1;
	}
	if (item == "ok2")
	{
		return fsm_curstate::ok2;
	}
	if (item == "ok3")
	{
		return fsm_curstate::ok3;
	}
	if (item == "fa1")
	{
		return fsm_curstate::fa1;
	}
	if (item == "fa2")
	{
		return fsm_curstate::fa2;
	}
	if (item == "fa3")
	{
		return fsm_curstate::fa3;
	}
}

int f(Pair<char, string> c)
{
	return 5 * getstate(c.second) + (c.first - 65);
}