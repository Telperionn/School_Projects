//********************************************************************************
//
//	Programmer: Patrick Sadowy
//	Instructor: Professor Streller
//	Course: cs232
//	Date: 4/15/2021
//	Progam Name: Project 3
//	Program File: cs232_proj3_driver.cpp
//	Input Files: User-supplied message .txt file, possibly table_in and encoded message 
//			text files.
//	Output Files: possibly output .txt files
//	Purpose: This program reads through a file, creates a Huffman Table, re reads the 
//			input file and creates a Huffman Encoding Tree and Huffman Code.
//			The program then outputs, if the user wishes, files to store the table and 
//			tree. This program may also decode an encoded message, provided a key table
//			and encoded message are supplied.
//
//********************************************************************************

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <list>
#include "Tree.h"

using namespace std;

//begin the main function
int main()
{

	//variable declarations
	list<TreeNode<info>> mylist; 
	tree<info> tree_obj;
	int choice;

	do 
	{
		//display menu to the console
		cout << "Please select a menu choice: \n" <<
			"1: Encode a message\n" <<
			"2: Decode a message\n" <<
			"3: Exit\n";
		cin >> choice;
		//input validation
		while ((choice < 1 || choice > 3) || !cin || cin.peek() != '\n')
		{
			cout << "\nInvalid selection. Please try again: \n\n";
			cin.clear();
			cin.ignore(50, '\n');

			cout << "Please select a menu choice: \n" <<
				"1: Encode a message\n" <<
				"2: Decode a message\n" <<
				"3: Exit\n";
			cin >> choice;
		}

		switch (choice)
		{
		case 1:
			char pick;
			//read in file, make and get list of 
			//info types, where the letter and its
			//frequency are recorded
			mylist = tree_obj.getlist();
			cout << endl;
			//ask user if they wish to display the Huffman Table or not
			cout << "Would you like to print the Huffman Table for this file? (y/n): \n";
			cin >> pick;
			if (pick == 'y' || pick == 'Y') 
			{
				//display the list of info's sorted
				//in increasing order
				tree_obj.print_Huff_table(mylist);
			}
			else
			{ }
			
			//creates the huffman tree to encode
			//a message
			tree_obj.make_tree(mylist);
			//stores the huff_table on a .txt file
			tree_obj.store_table();
			//stores the encoded message on a .txt file
			tree_obj.store_msg();

			
			break;
		case 2:
			//asks user for huffman table, and
			//an associated encoded message - then 
			//decodes the encoded message 
			tree_obj.decode();
			cout << endl << endl;
			
			break;
		case 3:
			return 0;
		}

	} while (choice != 3);
	
	

	return 0;
}