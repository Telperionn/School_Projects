//********************************************************************************
//
//	Programmer: Patrick Sadowy
//	Instructor: Professor Streller
//	Course: cs232
//	Date: 3/6/2021
//	Progam Name: Project 2
//	Program File: cs232_proj1_driver.cpp
//	Input Files: None.
//	Output Files: None.
//	Purpose: This program builds and maintains a set of vertices and a set of weighted 
//		edges. Its purpose is to allow for a graph construction or destruction of any 
//		type, and size.
//
//********************************************************************************


#include "Graph.h"
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

//begin main function
int main()
{
	Graph<string, int> graph; //graph object creation
	int choice = 0, weight = 0; //menu choice selection, weight of edge
	string v1, v2; //name of a vertex


	do
	{
		//print menu to console
		cout << "\nPlease select an option:\n\n"
			<< "Option 1: Read graph from a file\n"
			<< "Option 2: Add vertex\n"
			<< "Option 3: Delete vertex\n"
			<< "Option 4: Add UniDirected edge\n"
			<< "Option 5: Delete UniDirected edge\n"
			<< "Option 6: Add BiDirected edge\n"
			<< "Option 7: Delete BiDirected edge\n"
			<< "Option 8: Print graph\n"
			<< "Option 9: Print shortest distance\n"
			<< "Option 10: Print graph's MST\n"
			<< "Option 11: Print breadth first traversal\n"
			<< "Option 12: Print depth first traversal\n"
			<< "Option 13: Print depth first traversal(recursive)\n"
			<< "Option 14: Exit\n\n";
		cin >> choice;

		//input validation loop.
		while (!cin || (choice < 1 || choice > 14) || cin.peek() != '\n')
		{
			cout << "\nInvalid selection. Please try again: \n\n";
			cin.clear();
			cin.ignore(100, '\n');

			cout << "Option 1: Read graph from a file\n"
				<< "Option 2: Add vertex\n"
				<< "Option 3: Delete vertex\n"
				<< "Option 4: Add directed edge\n"
				<< "Option 5: Delete directed edge\n"
				<< "Option 6: Add undirected edge\n"
				<< "Option 7: Delete undirected edge\n"
				<< "Option 8: Print graph\n"
				<< "Option 9: Print graph's shortest distance\n"
				<< "Option 10: Print graph's MST\n"
				<< "Option 11: Print breadth first traversal\n"
				<< "Option 12: Print depth first traversal\n"
				<< "Option 13: Print depth first traversal(recursive)\n"
				<< "Option 14: Exit\n\n";
			cin >> choice;
		}

		switch (choice)
		{
		case 1:
		{
			graph.GetGraph();
			break;
		}
		case 2:
		{
			cout << "\nVertex to be added: ";
			cin >> v1;
			graph.AddVertex(v1);
			break;
		}
		case 3:
		{
			cout << "\nVertex to be deleted: ";
			cin >> v1;
			graph.DeleteVertex(v1);
			break;
		}
		case 4:
		{
			cout << "\nUniDirected edge to be added (start,end,weight): ";
			cin >> v1 >> v2 >> weight;
			while (!cin)
			{
				cout << "\nInvalid entry, please try again. \nUniDirected edge to be added (start,end,weight): ";
				cin.clear();
				cin.ignore(100, '\n');
				cin >> v1 >> v2 >> weight;
			}
			graph.AddUniEdge(v1, v2, weight);
			break;
		}
		case 5:
		{
			cout << "\nUniDirected edge to be deleted (start,end): ";
			cin >> v1 >> v2;
			graph.DeleteUniEdge(v1, v2);
			break;
		}
		case 6:
		{
			cout << "\nBiDirected edge to be added (start,end,weight): ";
			cin >> v1 >> v2 >> weight;
			while (!cin)
			{
				cout << "\nInvalid entry, please try again. \nBiDirected edge to be added (v1,v2,weight): ";
				cin.clear();
				cin.ignore(100, '\n');
				cin >> v1 >> v2 >> weight;
			}
			graph.AddBiDirEdge(v1, v2, weight);
			break;
		}
		case 7:
		{
			cout << "\nBiDirected edge to be deleted (start,end): ";
			cin >> v1 >> v2;
			graph.DeleteBiDirEdge(v1, v2);
			break;
		}
		case 8:
		{
			graph.SimplePrintGraph();
			break;
		}
		case 9:
		{
			cout << "\nEnter source vertex: ";
			cin >> v1;
			cout << endl;
			graph.FordShortestPaths(v1);
			break;
		}
		case 10:
		{
			graph.mst();
			break;
		}
		case 11:
		{
			cout << "\nSource vertex: ";
			cin >> v1;
			graph.BFTraversal(v1);
			break;
		}
		case 12:
		{
			cout << "\nSource vertex: ";
			cin >> v1;
			graph.DFTraversal(v1);
			break;
		}
		case 13:
		{
			cout << "\nSource vertex: ";
			cin >> v1;
			graph.DFT(v1);
			break;
		}
		case 14:
		{
			return 0;
		}
		}



	} while (choice != '14');

	return 0;


}