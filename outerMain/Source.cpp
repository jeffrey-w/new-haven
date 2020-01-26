
#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::vector;

// A utility function to add an edge in an 
// undirected graph. 
void addEdge(vector<int> adj[], int u, int v)
{
	adj[u].push_back(v);
	adj[v].push_back(u);
}

// A utility function to print the adjacency list 
// representation of graph 
void printGraph(vector<int> adj[], int V)
{
	for (int v = 1; v < V; ++v)
	{
		cout << "\n Adjacency list of vertex "
			<< v << "\n" << v;
		for (auto x : adj[v])
			cout << "-> " << x;
		printf("\n");
	}
}

int main()
{
	cout << "Hi New Haven!\n";

	// for a 3 X 3 game board with nodes labeled 1 to 9

	int V = 10;
	vector<int> adj[10];
	addEdge(adj, 1, 2);
	addEdge(adj, 1, 4);
	addEdge(adj, 2, 3);
	addEdge(adj, 2, 5);
	addEdge(adj, 3, 6);
	addEdge(adj, 4, 5);
	addEdge(adj, 4, 7);
	addEdge(adj, 5, 6);
	addEdge(adj, 5, 8);
	addEdge(adj, 6, 9);
	addEdge(adj, 8, 7);
	addEdge(adj, 8, 9);

	printGraph(adj, V);

	system("pause");

	return 0;
}