#ifndef GRAPH_T
#define GRAPH_T

#include "Graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>
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
	if((isUniEdge(v1, v2) == 1) && (isUniEdge(v2, v1) == 1))
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
		G.erase(G.begin()+(isVertex(v)));
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
	edgeRep<V,W> temp;
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
			cout  << ", " << it->name << ", " << it->weight << ")";
		}
		cout << endl << endl;
	}
}


//*******************************************************************************
//	Function Name: ShortestDistance
//	Purpose: returns the shortest distance from vertex 1 to vertex 2, informs user 
//				of the path too. uses Dijkstra's algorthim.
//	Parameters: Reference to variable v1, and v2; both of datatype V. 
//	Return value: double
//	Data Members Accessed/Altered: all members - to find shortest route of all verticies
//				and weights of desired start->end path.
//	Functions Called: G.size() -  to check current size of the Graph.
//					  isVertex(V& v) - to check if vertex exists, if yes return
//				the current index of vertex in the Graph.
//					  size.push_back(int) - push to back of vector array
//					  size.size() - return size of vector array
//					  list<edgeRep<V, W>> .begin() - return iterator to beginning of edgelist
//					  list<edgeRep<V, W>> .end() - return iterator to end of edgelist
//*******************************************************************************
template <class V, class W>
double Graph<V, W>::ShortestDistance(V& v1, V& v2)
{
	int* pred = new int[G.size()];
	int* cd = new int[G.size()];
	int temp, id;
	vector<int> size;


	for (int i = 0; i < G.size(); i++)
	{
		G[i].visited = 0;
		pred[i] = isVertex(v1);
		cd[i] = (INT_MAX - 1);
	}
	cd[isVertex(v1)] = 0;

	temp = INT_MAX;

	for (int i = 0; i < G.size(); i++)
	{
		for (int j = 0; j < G.size(); j++)
		{
			if (G[j].visited == 0 && cd[j] < temp)
			{
				temp = cd[j];
				id = j;
			}
		}
		G[id].visited = 1;

		for (typename list<edgeRep<V, W>>::iterator it = G[id].edgelist.begin();
			it != G[id].edgelist.end(); it++)
		{

			if ((G[isVertex(it->name)].visited == 0) && (cd[isVertex(it->name)] > (cd[id] + it->weight)))
			{
				cd[isVertex(it->name)] = (cd[id] + it->weight);
				pred[isVertex(it->name)] = id;
			}
		}
		temp = INT_MAX;
	}

	temp = isVertex(v2);

	if (cd[temp] != (INT_MAX - 1))
	{
		while (temp != isVertex(v1))
		{
			size.push_back(temp);
			temp = pred[temp];
		}
		cout << endl << "The shortest distance from " << v1 << " to " << v2 << " is: " << endl;
		cout << v1 << ' ';
		for (int k = (size.size() - 1); k >= 0; k--)
		{
			cout << G[size[k]].name << ' ';
		}
		cout << ". " << "The weight of selected path is: " << cd[isVertex(v2)] << endl;

	}
	else
	{
		cout << "There is no path available to selected destination. " << endl;
	}
	
	
	return 0;
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
#endif