#ifndef GRAPH_H     //file Graph.h
#define GRAPH_H     //Graph, ADT definition
#include <vector>
using std::vector;
#include <list>
using  std::list;
//*******************************************************************************
//	Programmer: Patrick Sadowy
//	Instructor: Professor Streller
//	Course: cs232
//	Date: 3/6/2021
//	ADT name: Graph
//	ADT file: Graph.h
//
//	Class Name: Graph
//
//	Data Elements: A Graph is comprised of an edgerep, vertex, and a vector
//                 of type vertex.
//
//
//	A Graph object has 0 private data members.
//
//
//	A Graph object has no friend functions.
//		
//	An Graph object has the following public functions:
//		Graph() - 
//		~Graph() - the destructor
//		int isVertex(V& v) - Tests whether v is a vertex in the graph and returns
//              the index
//		int isUniEdge(V& v1, V& v2) - Tests whether edge <v1,v2> in graph
//		int isBiDirEdge(V& v1, V& v2) - Tests whether edge (v1,v2) in graph
//      int AddVertex(V& v) - Adds vertex with name v to the graph, if v 
//              is not already in graph, and returns the index where the vertex 
//              is stored.
//      int DeleteVertex(V& v) - Deletes vertex with name v from the graph, 
//              if v is in the graph. If there are any edges incident on the
//              vertex, these edges are deleted also.
//      int AddUniEdge(V& v1, V& v2, W& wt) - Adds the directed edge <v1,v2,wt>
//              to the graph; adds the vertices to the graph if the vertices are
//              not already part of the graph    
//      int  DeleteUniEdge(V& v1, V& v2) - Deletes the directed edge <v1,v2> 
//              (any weight) from the graph, if it is in the graph. The vertices
//              are not deleted from the graph, only the edge.
//      int AddBiDirEdge(V& v1, V& v2, W& wt) - Adds the bi-directional edge 
//              (v1,v2,wt) to the graph; adds the vertices to the graph if the 
//              vertices are not already part of the graph
//     int DeleteBiDirEdge(V& v1, V& v2) - Deletes the bi-directional edge (v1,v2) 
//              (any weight) from the graph, if it is in the graph. The vertices are
//              not deleted from the graph, only the edge.
//      void SimplePrintGraph() - Prints the list of vertices in the graph, and for 
//              each vertex, prints the list of edges in proper parenthesized 
//              notation, namely (v1,v2,wt) or <v1,v2,wt>.  NOTE: This is not a 
//              traversal.
//      double ShortestDistance(V& v1, V& v2) - returns the shortest distance from 
//              vertex 1 to vertex 2 informs user of the path too. use Dijkstra
//      void GetGraph() - Retrieves a graph from a special file and sets up the 
//              adjacency list for the graph.
//      void BFTraversal(V& v) - Performs Breadth First Traversal of the graph 
//              starting at specified vertex (parameter); prints trace information.  
//      void DFTraversal(V& v) - Performs (non-recusive) Depth First Traversal of the 
//              graph starting at specified vertex (parameter); prints trace 
//              information.
//					   
//*******************************************************************************
//		Class Graph DEFINITION SECTION
//*******************************************************************************

template <class V, class W> // V is the vertex class; W is edge weight class
struct edgeRep
{
    V name;               // Vertex name
    W weight;             // Edge weight
};

template <class V, class W>
struct vertex           // Array cell structure for graph 
{
    typedef edgeRep<V, W> edge;
    V name;               // Vertex name
    int visited;          // Used during traversal, Breadth-First or Depth-First
    list<edge> edgelist; 	// Pointer to edge list
};

template <class V, class W>
class Graph
{
protected:
  //  vertex<V, W> G[MAX]; // Main graph array for adjacency list representation
                       //  protected member functions
    vector<vertex<V, W>> G;

public:
    Graph();   // Constructor
    // . . . other constructors
    ~Graph();  // Destructor
    //Predicates:
    int isVertex(V& v);
    int isUniEdge(V& v1, V& v2);
    int isBiDirEdge(V& v1, V& v2);
    int AddVertex(V& v);
    int DeleteVertex(V& v);
    int AddUniEdge(V& v1, V& v2, W& wt);   
    int  DeleteUniEdge(V& v1, V& v2);
    int AddBiDirEdge(V& v1, V& v2, W& wt);
    int DeleteBiDirEdge(V& v1, V& v2);
    void SimplePrintGraph();
    double ShortestDistance(V& v1, V& v2);
    void BFTraversal(V& v); 
    void DFTraversal(V& v);
    void GetGraph(); // Professor is supplying 1 such files. The program
    // will be able to read any graph that is in the same format:
    // graph node followed by any adjacent nodes with followed by distance/weight 
    // to the node.The adjacency entry is terminated by #


};  //end class Graph defention section



#include "Graph.t"


#endif // !GRAPH_H_
