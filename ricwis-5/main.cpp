
#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include <queue>
#include <vector>
#include <stack>

#include <boost/graph/adjacency_list.hpp>
#include "heapV.h"
//#include "disjointSetV.h"

//#define LargeValue 99999999

using namespace std;
using namespace boost;

int const NONE = -1;  // Used to represent a node that does not exist

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

struct VertexProperties
{
	pair<int, int> cell; // maze cell (x,y) value
	Graph::vertex_descriptor pred;
	bool visited;
	bool marked;
	int weight;
};

// Create a struct to hold properties for each edge
struct EdgeProperties
{
	int weight;
	bool visited;
	bool marked;
};

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

void initializeGraph(Graph &g,
	Graph::vertex_descriptor &start,
	Graph::vertex_descriptor &end, ifstream &fin)
	// Initialize g using data from fin.  Set start and end equal
	// to the start and end nodes.
{
	EdgeProperties e;

	int n, i, j;
	int startId, endId;
	fin >> n;
	fin >> startId >> endId;
	Graph::vertex_descriptor v;

	// Add nodes.
	for (int i = 0; i < n; i++)
	{
		v = add_vertex(g);
		if (i == startId)
			start = v;
		if (i == endId)
			end = v;
	}

	while (fin.peek() != '.')
	{
		fin >> i >> j >> e.weight;
		add_edge(i, j, e, g);
	}
}

void findPathDFSStack(Graph &g, size_t vD)
{
	stack<Graph::vertex_descriptor> path;
	g[vD].visited = true;

	// Get a pair containing iterators pointing to the beginning and end of the
	// list of nodes adjacent to node v
	pair<Graph::adjacency_iterator, Graph::adjacency_iterator>
		aItrRange = adjacent_vertices(vD, g);

	// Loop over adjacent nodes in the graph
	for (Graph::adjacency_iterator aItr = aItrRange.first; aItr != aItrRange.second; ++aItr)
	{
		if (!g[*aItr].visited)
		{
			path.push(vD);
			g[*aItr].visited = true;
			findPathDFSStack(g, *aItr);
		}
	}
}

//Function to call other function
void findPathDFSStack(Graph &g)
{
	clearVisited(g);
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	findPathDFSStack(g, *vItrRange.first);
}

void clearVisited(Graph &g)
// Mark all nodes in g as not visited.
{
	// Get a pair containing iterators pointing the beginning and end of the
	// list of nodes
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);

	// Loop over all nodes in the graph
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		g[*vItr].visited = false;
	}
}

void findSpanningForest(Graph &g1, Graph &sf)
// Create a graph sf that contains a spanning forest on the graph g.
{
	
}

bool isConnected(Graph &g)
// Returns true if the graph g is connected. Otherwise returns false.
{
	findPathDFSStack(g);
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);

	// Loop over all nodes in the graph
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		if (!g[*vItr].visited)
		{
			return false;
		}
	}
	return true;
}

bool isCyclic(Graph &g)
// Returns true if the graph g contains a cycle. Otherwise, returns false.{
	return false;
}

int totalEdgeWeight(Graph &g)
// Returns the sum of all the edge weights
{
	int xReturn = 0;
	// Get a pair containing iterators pointing the beginning and end of the
	// list of edges
	pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);

	// Loop over all edges in the graph
	for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; ++eItr)
	{
		xReturn += g[*eItr].weight;
	}
	return xReturn;
}

int main()
{
	//char x;
	ifstream fin;
	stack <int> moves;
	string fileName;

	// Read the name of the graph from the keyboard or
	// hard code it here for testing.

	fileName = "";

	cout << "Enter filename" << endl;
	cin >> fileName;

	fin.open(fileName.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << endl;
		exit(1);
	}

	try

	{
		cout << "Reading graph" << endl;
		Graph g;

		Graph::vertex_descriptor start, end;

		initializeGraph(g, start, end, fin);
		cout << "Num nodes: " << num_vertices(g) << endl;
		cout << "Num edges: " << num_edges(g) << endl;
		cout << endl;

		//cout << g;

		bool connected = false;
		bool cyclic = false;

		cout << "Calling isCyclic" << endl;
		cyclic = isCyclic(g);

		if (cyclic)
			cout << "Graph contains a cycle" << endl;
		else
			cout << "Graph does not contain a cycle" << endl;

		cout << endl;

		cout << "Calling isConnected" << endl;
		connected = isConnected(g);

		if (connected)
			cout << "Graph is connected" << endl;
		else
			cout << "Graph is not connected" << endl;

		cout << endl;
		cout << "Finding spanning forest" << endl;

		// Initialize an empty graph to contain the spanning forest
		Graph sf(num_vertices(g));

		findSpanningForest(g, sf);

		cout << "Spanning forest weight: " << totalEdgeWeight(sf) / 2 << endl;
		cout << endl;

		cout << "Calling isConnected" << endl;
		connected = isConnected(sf);

		if (connected)
			cout << "Graph is connected" << endl;
		else
			cout << "Graph is not connected" << endl;
		cout << endl;

		cout << "Calling isCyclic" << endl;
		//cyclic = isCyclic(sf);

		if (cyclic)
			cout << "Graph contains a cycle" << endl;
		else
			cout << "Graph does not contain a cycle" << endl;
		cout << endl;
	}
	catch (indexRangeError &ex)
	{
		cout << ex.what() << endl; exit(1);
	}
	catch (rangeError &ex)
	{
		cout << ex.what() << endl; exit(1);
	}
	while (1);
}
