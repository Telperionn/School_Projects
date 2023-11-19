#ifndef GRAPH_T
#define GRAPH_T
#include "Graph.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <cstdio>
using std::cout;
using std::cin;
using std::ifstream;
using std::ws;
using std::endl;
using std::string;

//*******************************************************************************
//		Class Graph TEMPLATE IMPLEMENTAION SECTION 
//*******************************************************************************


//*******************************************************************************
//	Function Name: Graph
//	Purpose: Default constructor
//	Parameters: none.
//	Return value: none
//	Data Members Accessed/Altered: none
//	Functions Called: none
//*******************************************************************************
template <class V, class W>
Graph<V, W>::Graph()   // Constructor
{


}

//*******************************************************************************
//	Function Name: ~Graph
//	Purpose: Default destructor
//	Parameters: none.
//	Return value: none
//	Data Members Accessed/Altered: none
//	Functions Called: none
//*******************************************************************************
template <class V, class W>
Graph<V, W>::~Graph()
{

}


//*******************************************************************************
//	Function Name: isVertex
//	Purpose: Tests whether v is a vertex in the graph and returns the index
//	Parameters: Reference to variable v of datatype V.
//	Return value: int
//	Data Members Accessed/Altered: accessed each index of Graph.name - to compare values
//	Functions Called: G.size() - to return the current size of the Graph.
//*******************************************************************************
template <class V, class W>
int Graph<V, W>::isVertex(V& v)
{
	for (unsigned i = 0; i < G.size();i++)
	{
		if (v == G[i].name)
		{
			return i;
		}
	}
	return -1;
}


//*******************************************************************************
//	Function Name: isUniEdge
//	Purpose: Tests whether edge <v1,v2> in graph
//	Parameters: Reference to variable v1, and v2; both of datatype V.
//	Return value: int
//	Data Members Accessed/Altered: all index's of Graph.edgelist - to compare values
//				of all names of edges in adjacency list, from start v1, at each 
//				index of the Graph
//	Functions Called: isVertex(V& v) - to check if vertex exists, if yes return the current
//				index of vertex in the Graph.
//*******************************************************************************
template <class V, class W>
int Graph<V, W>::isUniEdge(V& v1, V& v2)
{
	int temp = isVertex(v1);

	if (temp == -1 || isVertex(v2) == -1)
	{
		return -1;
	}
	else
	{
		for (typename list<edgeRep<V, W>>::iterator it = G[temp].edgelist.begin();
			it != G[temp].edgelist.end(); it++)
		{
			if (v2 == it->name)
			{
				return 1;
			}
		}
		return -1;
	}
}


//*******************************************************************************
//	Function Name: isBiDirEdge
//	Purpose: Tests whether edge (v1,v2) in graph
//	Parameters: Reference to variable v1, and v2; both of datatype V.
//	Return value: int
//	Data Members Accessed/Altered: none
//	Functions Called: isUniEdge(V& v1, V& v2) - to return if the UniEdge exists in the Graph 
//				or not
//*******************************************************************************
template <class V, class W>
int Graph<V, W>::isBiDirEdge(V& v1, V& v2)
{
	if ((isUniEdge(v1, v2) == 1) && (isUniEdge(v2, v1) == 1))
	{
		return 1;
	}
	return -1;
}


//*******************************************************************************
//	Function Name: AddVertex
//	Purpose: Adds vertex with name v to the graph, if v is not already in graph, and
//				returns the index where the vertex is stored.
//	Parameters: Reference to variable v of datatype V.
//	Return value: int
//	Data Members Accessed/Altered: none
//	Functions Called: isVertex() - to check if vertex exists, if yes return the current
//				index of vertex in the Graph.
//					  G.size() -  to return the current size of the Graph.
//*******************************************************************************
template <class V, class W>
int Graph<V, W>::AddVertex(V& v)
{
	vertex<V, W> temp;
	temp.name = v;
	if (isVertex(v) == -1)
	{
		G.push_back(temp);
		return (G.size() - 1);
	}
	return isVertex(v);
}


//*******************************************************************************
//	Function Name: DeleteVertex
//	Purpose: Deletes vertex with name v from the graph, if v is in the graph. If there
//				are any edges incident on the vertex, these edges are deleted also.
//	Parameters: Reference to variable v of datatype V.
//	Return value: int
//	Data Members Accessed/Altered: Erase the desired vertex from Graph
//	Functions Called: isVertex(V& v) - to check if vertex exists, if yes return the current
//				index of vertex in the Graph.
//					  G.begin() -  to return an iterator to the beginning of the Graph.
//					  G.erase(iterator position) - erases data from a position in the graph
//*******************************************************************************
template <class V, class W>
int Graph<V, W>::DeleteVertex(V& v)
{
	if (isVertex(v) > -1)
	{
		G.erase(G.begin() + (isVertex(v)));
		return 1;
	}
	return -1;
}


//*******************************************************************************
//	Function Name: AddUniEdge
//	Purpose: Adds the directed edge <v1, v2, wt> to the graph; adds the vertices
//				to the graph if the vertices are not already part of the graph
//	Parameters: Reference to variable v1, v2; of datatype V. Reference to wt of datatype W.
//	Return value: int
//	Data Members Accessed/Altered: desired index of Graph.edgelist - Add the desired 
//				edge to Graph
//	Functions Called: AddVertex(v1) - to add vertex to the list, if not already included
//					  isUniEdge(V& v1, V& v2) -  to check if edge exists the Graph.
//					  isVertex(V& v) - return the current index of vertex in the Graph.
//*******************************************************************************
template <class V, class W>
int Graph<V, W>::AddUniEdge(V& v1, V& v2, W& wt)
{
	edgeRep<V, W> temp;
	temp.name = v2;
	temp.weight = wt;

	AddVertex(v1);
	AddVertex(v2);
	if (isUniEdge(v1, v2) == -1)
	{
		G[isVertex(v1)].edgelist.push_back(temp);
		return 1;
	}

	return -1;
}


//*******************************************************************************
//	Function Name: DeleteUniEdge
//	Purpose: Deletes the directed edge <v1,v2> (any weight) from the graph, if it is
//				in the graph. The vertices are not deleted from the graph, only the edge.
//	Parameters: Reference to variable v1, and v2; both of datatype V.
//	Return value: int
//	Data Members Accessed/Altered: desired index of Graph.edgelist - delete the desired 
//				edge to Graph
//	Functions Called: isUniEdge(V& v1, V& v2) -  to check if edge exists the Graph.
//					  isVertex(V& v) - return the current index of vertex in the Graph.
//*******************************************************************************
template <class V, class W>
int Graph<V, W>::DeleteUniEdge(V& v1, V& v2)
{
	int temp = isVertex(v1);
	if (isUniEdge(v1, v2) > -1)
	{
		for (typename list<edgeRep<V, W>>::iterator it = G[temp].edgelist.begin();
			it != G[temp].edgelist.end(); it++)
		{
			if (it->name == v2)
			{
				G[temp].edgelist.erase(it);
				return 1;
			}
		}
	}
	return -1;
}


//*******************************************************************************
//	Function Name: AddBiDirEdge
//	Purpose: Adds the bi-directional edge (v1,v2,wt) to the graph; adds the vertices
//				 to the graph if the vertices are not already part of  the graph
//	Parameters: Reference to variable v1, and v2; both of datatype V. Reference to wt of 
//					datatype W.
//	Return value: int
//	Data Members Accessed/Altered: adds an edge to Graph.edgelist of desired start to end
//				vertex
//	Functions Called: isUniEdge(V& v1, V& v2) -  to check if edge exists the Graph.
//					  AddUniEdge(V& v) - adds uniEdge to the Graph, adds verticies to
//				Graph if not otherwise in the Graph.
//*******************************************************************************
template <class V, class W>
int Graph<V, W>::AddBiDirEdge(V& v1, V& v2, W& wt)
{
	if ((isUniEdge(v1, v2) == 1) || (isUniEdge(v2, v1) == 1))
	{
		return -1;
	}

	AddUniEdge(v1, v2, wt);
	AddUniEdge(v2, v1, wt);

	return 1;

}


//*******************************************************************************
//	Function Name: DeleteBiDirEdge
//	Purpose: Deletes the bi-directional edge(v1, v2) (any weight) from the graph,
//				if it is in the graph. The vertices are not deleted from the graph, 
//				only the edge.
//	Parameters: Reference to variable v1, and v2; both of datatype V. 
//	Return value: int
//	Data Members Accessed/Altered: Deletes a Uniedge from Graph.edgelist of desired 
//				start to end vertex. This is done in both directions.
//	Functions Called: isBiDirEdge(V& v1, V& v2) -  to check if BiDiredge exists the Graph.
//					  DeleteUniEdge(V& v1, V& v2) - checks if BiDirEdge exists in
//				 Graph, if yes then delete uniEdge in both directions.
//*******************************************************************************
template <class V, class W>
int Graph<V, W>::DeleteBiDirEdge(V& v1, V& v2)
{

	if (isBiDirEdge(v1, v2) > -1)
	{
		DeleteUniEdge(v1, v2);
		DeleteUniEdge(v2, v1);
		return 1;
	}

	return -1;
}


//*******************************************************************************
//	Function Name: SimplePrintGraph
//	Purpose: Prints the list of vertices in the graph, and for each vertex,
//				prints the list of edges in proper parenthesized notation, namely 
//				(v1,v2,wt) or <v1,v2,wt>.  NOTE: This is not a traversal.
//	Parameters: none.
//	Return value: none.
//	Data Members Accessed/Altered: all members - to print as output
//	Functions Called: G.size() -  to check current size of the Graph.
//*******************************************************************************
template <class V, class W>
void Graph<V, W>::SimplePrintGraph()
{
	for (unsigned i = 0; i < G.size();i++)
	{
		cout << "(v1,v2,wt) is : ";

		for (typename list<edgeRep<V, W>>::iterator it = G[i].edgelist.begin();
			it != G[i].edgelist.end(); it++)
		{
			cout << "(" << G[i].name << ' ';
			cout << ", " << it->name << ", " << it->weight << ")";
		}
		cout << endl << endl;
	}
}


//*******************************************************************************
//	Function Name: FordShortestPaths
//	Purpose: Determines the shortest paths to all other vertices 
//           from the specified vertex using Ford's algorithm, and a 'DeQ'( double  
//           ended queue ) ADT for processing the vertices.The output displays th paths 
//           from v. Trace information is displayed,  i.e. the DeQ after each iteration. 
//           When done,  displays the distances and the previous vertex for each vertex  
//           in the graph. That is, the minimum distance is displayed, along with the  
//           sequence of nodes in the path.
//           Note: linked edgelist must be STL list and the DeQ must be implemented 
//           using a STL container.
//	Parameters: Reference to variable v1, and v2; both of datatype V. 
//	Return value: double
//	Data Members Accessed/Altered: all members - to find shortest route of all verticies
//				and weights of desired start->end path.
//	Functions Called: G.size() -  to check current size of the Graph.
//					  isVertex(V& v) - to check if vertex exists, if yes return
//				the current index of vertex in the Graph.
//					  push_back(int) - push to back of vector array
//					  size() - return size of vector array
//					  list<edgeRep<V, W>> .begin() - return iterator to beginning of edgelist
//					  list<edgeRep<V, W>> .end() - return iterator to end of edgelist
//					  empty() - to check if the deque is currently empty or not
//					  push_front(int) - push item to the front of the deque
//					  front() - access the front of the deque
//					  pop_front() - remove item from front of deque
//*******************************************************************************
template <class V, class W>
void Graph<V, W>::FordShortestPaths(V& v)
{
	int* cd = new int[G.size()];
	string* pred = new string[G.size()];
	int id, infinity;
	vertex<V, W> temp;
	std::deque<vertex<V, W>> q;
	
	for (int i = 0; i < G.size(); i++)
	{
		G[i].visited = 0;
		pred[i] = "";
		cd[i] = (INT_MAX - 1);
	}
	cd[isVertex(v)] = 0;

	q.push_front(G[isVertex(v)]);
	G[isVertex(v)].visited = 1;
	infinity = INT_MAX;

	while (!q.empty())
	{
		//front vertex from the queue
		temp = q.front();
		q.pop_front();
		G[isVertex(temp.name)].visited = 1;

		//adjusting all edges from vertex taken from queue
		

		for (typename list<edgeRep<V, W>>::iterator it = G[isVertex(temp.name)].edgelist.begin();
			it != G[isVertex(temp.name)].edgelist.end(); it++)
		{

			if ((G[isVertex(it->name)].visited == 0) && (cd[isVertex(it->name)] > (cd[isVertex(temp.name)] + it->weight)))
			{
				cd[isVertex(it->name)] = (cd[isVertex(temp.name)] + it->weight);
				pred[isVertex(it->name)] = temp.name;
			}
			//if vertex is not in queue, push into queue
			if (G[isVertex(it->name)].visited == 0)
			{
				q.push_back(G[isVertex(it->name)]);
			}
		}

		cout << "trace information after iteration: " << endl;
		for (int i = 0; i < q.size(); i++)
		{
			cout << q[i].name << endl;
		}
		cout << endl;
	}

	for (unsigned k = 0; k < G.size(); k++)
	{
		if (G[k].name != v)
		{
			if(cd[k] != (infinity - 1))
			{ 
				cout << "shortest distance from " << v << " to " << G[k].name << " is: " << cd[k] << endl;
				std::deque<string> path;
				int p = isVertex(G[k].name);
				while (p != isVertex(v))
				{
					if (pred[p] != "")
					{
						path.push_front(pred[p]);
						p = isVertex(pred[p]);
					}
					else
					{
						p = isVertex(v);
					}
				}
				cout << "The path from " << v << " to " << G[k].name << " is: " << endl << endl;
				while (!path.empty())
				{
					string s = path.front();
					path.pop_front();
					cout << s << " to ";
					if (!path.empty())
					{
						s = path.front();
						cout << s << endl;
					}
					else
					{
						cout << G[k].name << endl;
					}
				}
			}
			else
			{
				cout << "There is no path from " << v << " to " << G[k].name << endl;
			
			}
		}
		cout << endl;
	}

	return;
}

//*******************************************************************************
//	Function Name: mst
//	Purpose:	Determine the minimum spanning tree using Prim's algorithm.  
//              Trace information is displayed showing the distance, neighbor and 
//              component arrays for each iteration. Weight of MST is also displayed. 
//              Displays what vertex is connected to whom. 
//	Parameters:  
//	Return value: void/none
//	Data Members Accessed/Altered: 
//	Functions Called: G.size() -  to check current size of the Graph.
//					  isVertex(V& v) - to check if vertex exists, if yes return
//				the current index of vertex in the Graph.
//					  size.push_back(int) - push to back of vector array
//					  size.size() - return size of vector array
//					  list<edgeRep<V, W>> .begin() - return iterator to beginning of edgelist
//					  list<edgeRep<V, W>> .end() - return iterator to end of edgelist
//					  SimplePrintGraph() - call function to print out info of current
//				MST from given graph
//					  AddBiDirEdge(V& v1, V& v2, W& wt) - adds a BiDirEdge to the MST
//				graph when an appropriate edge is found
//*******************************************************************************
template <class V, class W>
void Graph<V, W>::mst()
{
	int spot, weightmin = INT_MAX, weightSUM = 0;
	Graph<V, W> MST;
	int* cd = new int[G.size()];
	int* neighbor = new int[G.size()];
	int* component = new int[G.size()];

	for (int i = 0; i < G.size(); i++)
	{
		component[i] = 0;
		neighbor[i] = 0;
		cd[i] = (INT_MAX - 1);
	}

	for (typename list<edgeRep<V, W>>::iterator it = G[0].edgelist.begin();
		it != G[0].edgelist.end(); it++)
	{
		cd[isVertex(it->name)] = it->weight;
	}
	component[0] = 1;
	cd[0] = 0;

	for (int i = 1; i < G.size(); i++)
	{
		weightmin = INT_MAX;

		for (int j = 0; j < G.size(); j++)
		{
			if (component[j] == 0)
			{
				if (cd[j] < weightmin)
				{
					spot = j;
					weightmin = cd[j];
				}
			}
		}
		if (weightmin < INT_MAX)
		{
			component[spot] = 1;
			MST.AddBiDirEdge(G[spot].name, G[neighbor[spot]].name, cd[spot]);

			for (typename list<edgeRep<V, W>>::iterator it = G[spot].edgelist.begin();
				it != G[spot].edgelist.end(); it++)
			{
				if (component[isVertex(it->name)] == 0)
				{
					if (it->weight < cd[isVertex(it->name)])
					{
						cd[isVertex(it->name)] = it->weight;
						neighbor[isVertex(it->name)] = spot;
					}

				}
			}

		}
		else
			break;

		cout << "This is the distance array: " << endl;
		for (int c = 0; c < G.size(); c++)
		{
			cout << cd[c] << " ";
		}
		cout << endl;
		cout << "This is the neighbor array: " << endl;
		for (int c = 0; c < G.size(); c++)
		{
			cout << neighbor[c] << " ";
		}
		cout << endl;
		cout << "This is the component array: " << endl;
		for (int c = 0; c < G.size(); c++)
		{
			cout << component[c] << " ";
		}
		cout << endl << endl;
	}
	cout << endl << endl;
	for (int i = 0; i < G.size(); i++)
	{
		weightSUM += cd[i];
	}
	cout << "The weight of the MST is: " << weightSUM << ". " << endl;
	MST.SimplePrintGraph();

}



//*******************************************************************************
//	Function Name: GetGraph
//	Purpose: Retrieves a graph from a special file and sets up the adjacency 
//				list for the graph. The program will be able to read any graph that 
//				is in the same format: graph node followed by any adjacent nodes with
//				followed by distance/weight to the node.The adjacency entry is terminated
//				by #
//	Parameters: void/none.
//	Return value: void.
//	Data Members Accessed/Altered: all members - to add values to components of Graph
//	Functions Called: AddUniEdge(V& v) - adds uniEdge to the Graph, adds verticies to
//				Graph if not otherwise in the Graph.
//					  infile.ignore() - ignore the rest of the file after all relevant
//					data is read in.
//*******************************************************************************
template <class V, class W>
void Graph<V, W>::GetGraph()
{
	string name;
	ifstream infile;
	V start, end;
	W wt;

	cin.ignore();
	cout << "please enter file path: ";
	getline(cin, name);

	infile.open(name);
	if (!infile)
	{
		cout << "Invalid path. Now exiting program." << endl;
		return;
	}


	while (infile >> start)
	{
		infile >> ws;
		while (infile.peek() != '#')
		{

			infile >> end;
			infile >> wt;
			infile >> ws;

			AddUniEdge(start, end, wt);
		}
		infile.ignore();
	}

	infile.close();
}


//*******************************************************************************
//	Function Name: BFTraversal
//	Purpose: Performs Breadth First Traversal of the graph starting at specified vertex
//				(parameter). prints trace information.
//	Parameters: Reference to variable v of datatype V.
//	Return value: void/none.
//	Data Members Accessed/Altered: 
//	Functions Called: G.size() -  to check current size of the Graph.
//					  path.push(int) - push int to front of queue
//					  isVertex(V& v) - to check if vertex exists, if yes return
//				the current index of vertex in the Graph.
//					  path.empty() - returns if queue is empty or not empty
//					  path.front() - return value at front of queue
//					  path.pop() - remove item from queue
//*******************************************************************************
template <class V, class W>
void Graph<V, W>::BFTraversal(V& v)
{
	int index, ok = 0;
	std::queue<int> path;
	for (int i = 0; i < G.size(); i++)
	{
		G[i].visited = 0;
	}
	cout << "The BFTraversal from start " << v << " is: " << endl;

	path.push(isVertex(v));
	do
	{
		ok = 0;
		while (!path.empty())
		{
			index = path.front();
			if (G[index].visited == 0)
			{
				G[index].visited = 1;
				path.pop();
				for (typename list<edgeRep<V, W>>::iterator it = G[index].edgelist.begin();
					it != G[index].edgelist.end(); it++)
				{
					path.push(isVertex(it->name));
				}
				cout << G[index].name << " ";
			}
			else
			{
				path.pop();
			}
		}
		for (int i = 0; i < G.size(); i++)
		{
			if (G[i].visited == 0)
			{
				cout << endl << "Here are verticies unreachable by given input, in DFTraversal: " << endl;
				ok = 1;
				path.push(i);
				break;
			}
		}

	} while (ok == 1);


}


//*******************************************************************************
//	Function Name: DFTraversal
//	Purpose: Performs (non-recusive) Depth First Traversal of the graph starting at 
//				specified vertex (parameter); prints trace information.
//	Parameters: Reference to variable v of datatype V.
//	Return value: void/none.
//	Data Members Accessed/Altered: 
//	Functions Called: G.size() -  to check current size of the Graph.
//					  path.push(int) - push int to top of stack
//					  isVertex(V& v) - to check if vertex exists, if yes return
//				the current index of vertex in the Graph.
//					  path.empty() - returns if stack is empty or not empty
//					  path.pop() - remove item from top of stack
//*******************************************************************************
template <class V, class W>
void Graph<V, W>::DFTraversal(V& v)
{
	int index, ok = 0;
	std::stack<int> path;
	for (int i = 0; i < G.size(); i++)
	{
		G[i].visited = 0;
	}


	cout << "The DFTraversal from start " << v << " is: " << endl;

	path.push(isVertex(v));

	do
	{
		ok = 0;
		while (!path.empty())
		{
			index = path.top();
			if (G[index].visited == 0)
			{
				G[index].visited = 1;
				path.pop();
				for (typename list<edgeRep<V, W>>::reverse_iterator it = G[index].edgelist.rbegin();
					it != G[index].edgelist.rend(); it++)
				{
					path.push(isVertex(it->name));
				}
				cout << G[index].name << " ";
			}
			else
			{
				path.pop();
			}
		}

		for (int i = 0; i < G.size(); i++)
		{
			if (G[i].visited == 0)
			{
				cout << endl << "Here are verticies unreachable by given input, in DFTraversal: " << endl;
				ok = 1;
				path.push(i);
				break;
			}
		}


	} while (ok == 1);


}

//*******************************************************************************
//	Function Name: DepthFirstTraversal
//	Purpose: Aux function to be called by DFT function. Used recursively to  
//				traverse all edges of an index.
//	Parameters: Reference to variable v of datatype V.
//	Return value: void/none.
//	Data Members Accessed/Altered: 
//	Functions Called: isVertex(V& v) - to check if vertex exists, if yes return
//				the current index of vertex in the Graph.
//					  DepthFirstTraversal(V& v) - recursive call
//*******************************************************************************
template <class V, class W>
void Graph<V, W>::DepthFirstTraversal(V& v)
{
	int index = isVertex(v); //gets index of v

	G[index].visited = 1; //sets visited of index to 1

	cout << v << " "; //prints v

	for (typename list<edgeRep<V, W>>::iterator it = G[index].edgelist.begin();
		it != G[index].edgelist.end(); it++) //iterator used to access edgelists
	{
		int temp = isVertex(it->name);

		if (G[temp].visited == 0) //
		{
			DepthFirstTraversal(it->name);
		}
	}
}

//*******************************************************************************
//	Function Name: DFT
//	Purpose: Performs (recusive) Depth First Traversal of the graph starting at 
//				specified vertex (parameter); prints trace information.
//	Parameters: Reference to variable v of datatype V.
//	Return value: void/none.
//	Data Members Accessed/Altered: G[i].visited - to track if visited or not
//	Functions Called: G.size() -  to check current size of the Graph.
//					  DepthFirstTraversal(V& v) - calls aux function to perform
//				recursive traversal of edges of each index of vertices.
//*******************************************************************************
template <class V, class W>
void Graph<V, W>::DFT(V& v)
{
	for (int i = 0; i < G.size(); i++)
	{
		G[i].visited = 0; 
	}

	DepthFirstTraversal(v); //recursive call for DepthFirstTraversal
	cout << endl;
	cout << "\nNo path found for the following vertices: " << endl;

	for (int i = 0; i < G.size(); i++)
	{
		if (G[i].visited == 0) //if no path has been found (sparse graph)
		{
			cout << G[i].name << " ";
			break;
		}
	}
	cout << endl << endl;
}

#endif
