
#include "graph.h"
using std::string;

int main()
{
	int c = 0, wt = 0;
	Graph<string, int> g;
	string v1, v2;

	do
	{
		cout << "\nPlease select an option:\n"
			<< "Option 1: Read graph from a file\n"
			<< "Option 2: Add vertex\n"
			<< "Option 3: Delete vertex\n"
			<< "Option 4: Add directed edge\n"
			<< "Option 5: Delete directed edge\n"
			<< "Option 6: Add undirected edge\n"
			<< "Option 7: Delete undirected edge\n"
			<< "Option 8: Print graph\n"
			<< "Option 9: Print shortest distance\n"
			<< "Option 10: Print breadth first traversal\n"
			<< "Option 11: Print depth first traversal\n"
			<< "Option 12: Exit\n"
			<< "Which option?: ";
		cin >> c;

		while (!cin || (c < 1 || c > 12) || cin.peek() != '\n')	//input validation loop, gives option menu again
		{
			cout << "\nInvalid option, please select again: \n";
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
				<< "Option 10: Print breadth first traversal\n"
				<< "Option 11: Print depth first traversal\n"
				<< "Option 12: Exit\n"
				<< "Which option?: ";
			cin >> c;
		}

		switch (c)
		{
		case 1:
		{
			g.GetGraph();
			break;
		}
		case 2:
		{
			cout << "\n\tVertex to add: ";
			cin >> v1;
			g.AddVertex(v1);
			break;
		}
		case 3:
		{
			cout << "\n\tVertex to delete: ";
			cin >> v1;
			g.DeleteVertex(v1);
			break;
		}
		case 4:
		{
			cout << "\n\tDirected edge to add (v1,v2,wt): ";
			cin >> v1 >> v2 >> wt;
			while (!cin)
			{
				cout << "\n\tInvalid entry, try again (v1,v2,wt): ";
				cin.clear();
				cin.ignore(100, '\n');
				cin >> v1 >> v2 >> wt;
			}
			g.AddUniEdge(v1, v2, wt);
			break;
		}
		case 5:
		{
			cout << "\n\tDirected edge to delete (v1,v2): ";
			cin >> v1 >> v2;
			g.DeleteUniEdge(v1, v2);
			break;

		}
		case 6:
		{
			cout << "\n\tUndirected edge to add (v1,v2,wt): ";
			cin >> v1 >> v2 >> wt;
			while (!cin)
			{
				cout << "\n\tInvalid entry, try again (v1,v2,wt): ";
				cin.clear();
				cin.ignore(100, '\n');
				cin >> v1 >> v2 >> wt;
			}
			g.AddBiDirEdge(v1, v2, wt);
			break;

		}
		case 7:
		{
			cout << "\n\tUndirected edge to delete (v1,v2): ";
			cin >> v1 >> v2;
			g.DeleteBiDirEdge(v1, v2);
			break;

		}
		case 8:
		{
			g.SimplePrintGraph();
			break;
		}
		case 9:
		{
			cout << "\n\tFrom which vertex to which vertex (v1,v2): ";
			cin >> v1 >> v2;
			g.ShortestDistance(v1, v2);
			break;
		}
		case 10:
		{
			cout << "\n\tSource vertex (v1): ";
			cin >> v1;
			g.BFTraversal(v1);
			break;
		}
		case 11:
		{
			cout << "\n\tSource vertex (v1): ";
			cin >> v1;
			g.DFTraversal(v1);
			break;
		}
		case 12:
		{
			return 0;
		}
		}
		
	} while (c != '12');

	return 0;
}