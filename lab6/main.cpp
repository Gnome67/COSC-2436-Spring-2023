#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>

#include "ArgumentManager.h"

using namespace std;

const int maxNum = 10000;
int n, m;
vector<int> adjacent[maxNum];
int inputDegrees[maxNum];

int main(int argc, char *argv[])
{
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ofstream out(am.get("output"));
  
	int n, u, v;
  input >> n;
  unordered_map<int, vector<int>> adjacent_list;
  unordered_map<int, int> incoming_edges;
	
  while (input >> u >> v)
	{
    adjacent_list[u].push_back(v);
    incoming_edges[v]++;
  }

  queue<int> q;
  for (int i = 0; i < n; i++) { if (incoming_edges[i] == 0) { q.push(i); } }
	vector<int> sorted_vertices;
	
  while (!q.empty())
	{
  	int curr_vertex = q.front();
    q.pop();
    sorted_vertices.push_back(curr_vertex);
    for (int neighbor : adjacent_list[curr_vertex])
		{
      incoming_edges[neighbor]--;
      if (incoming_edges[neighbor] == 0) { q.push(neighbor); }
		}
  }
	
  if (sorted_vertices.size() != n)
	{
  	out << "No Topological Sorting Exists!" << endl;
  	return 0;
  }
	
  for (int vertex : sorted_vertices) { out << vertex << " "; }
  out << endl;
  return 0;
}