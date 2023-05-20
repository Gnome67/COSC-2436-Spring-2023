#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include "ArgumentManager.h"
#include <ctype.h>
#include <stdio.h>
#include <limits.h>
using namespace std;

int findVertexWithMinimumDistance(int output[], bool processedVertices[], int V)
{
  int min = INT_MAX, min_index;
  for (int v = 0; v < V; v++) { if (processedVertices[v] == false && output[v] <= min) { min = output[v], min_index = v; } }
  return min_index;
}

void printSolution(int output[], int V, ofstream& out)
{
  for (int i = 0; i < V; i++) { out << i << " " << output[i] << endl; }
}

void dijkstra(int V, vector<vector<int>> &graph, int src, ofstream& out)
{
  int output[V];
  bool processedVertices[V]; // processedVertices[i] will be true if vertex i is included in shortest path tree or shortest distance from src to i is finalized

  for (int i = 0; i < V; i++) { output[i] = INT_MAX, processedVertices[i] = false; }
  output[src] = 0;  
  for (int count = 0; count < V - 1; count++)
	{
  	int u = findVertexWithMinimumDistance(output, processedVertices, V);
    processedVertices[u] = true;
    // Update output value of the adjacent vertices of the picked vertex.
    for (int v = 0; v < V; v++) { if (!processedVertices[v] && graph[u][v] && output[u] != INT_MAX && output[u] + graph[u][v] < output[v]) { output[v] = output[u] + graph[u][v]; } }
    // Update output[v] only if is not in processedVertices, there is an edge from u to v, and total weight of path from src to  v through u is smaller than current value of output[v]
    }
    printSolution(output, V, out);
}

int main(int argc, char *argv[])
{
	ArgumentManager am(argc, argv);
	ifstream in(am.get("input"));
	ofstream out(am.get("output"));
	//ifstream in("input1.txt");
	//ofstream out("output1.txt");
	
	int n = 0, x = 0;
	in >> n;
	vector<vector<int>> graph;
	for (int i = 0; i < n; i++) 
	{ 
  	vector<int> row;
  	for(int j = 0; j < n; j++)
  	{
    	in >> x;
    	row.push_back(x);
  	}
  	graph.push_back(row);
	}
	dijkstra(n, graph, 0, out);
	return 0;
}