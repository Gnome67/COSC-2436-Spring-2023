#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "ArgumentManager.h"
#include "LinkedList.h"

using namespace std;

bool cmp(pair<string, int>& a, pair<string, int>& b)
{
  return a.second != b.second ?  a.second > b.second : a.first < b.first;
}

void sort(map<string, int> &M, vector<pair<string, int>> &container)
{
    vector<pair<string, int> > A;
    for (auto &it : M) {
        A.push_back(it);
    }
    sort(A.begin(), A.end(), cmp);
    for (auto& it : A) 
    {
      container.push_back(it);
    }
}

int main(int argc, char *argv[])
{
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ofstream ofs(am.get("output"));
  if (input.peek() != EOF)
  {
    string in, type;
    bool headOrTail;
    vector<string> lines;
		map<string, int> wordMap;
    while (input >> in)
    {
      in.erase(remove(in.begin(), in.end(), '\n'), in.end());
    	in.erase(remove(in.begin(), in.end(), '\r'), in.end());
    	in.erase(remove(in.begin(), in.end(), ' '), in.end());
			in.erase(remove(in.begin(), in.end(), ','), in.end());
			in.erase(remove(in.begin(), in.end(), '.'), in.end());
			in.erase(remove(in.begin(), in.end(), '!'), in.end());
			in.erase(remove(in.begin(), in.end(), '?'), in.end());
			in.erase(remove(in.begin(), in.end(), '('), in.end());
			in.erase(remove(in.begin(), in.end(), ')'), in.end());
			in.erase(remove(in.begin(), in.end(), '"'), in.end());
      if (in.size() == 0)
        continue;
      lines.push_back(in);
    }
    LinkedList list1;
    for(int i = 0; i < lines.size(); i++)
    {
      for(int j = 0; j < lines[i].length(); j++)
        {
          lines[i][j] = toupper(lines[i][j]);
        }
    }
    for (auto w : lines) 
    {
      if(wordMap.find(w) == wordMap.end()) 
      {
        wordMap.insert(pair<string, int>(w, 1));
    	}  else  {
        int num = wordMap[w] + 1;
        wordMap.erase(w);
        wordMap.insert(pair<string, int>(w, num));
      }
    }
    vector<pair<string, int>> sortedValues;
		sort(wordMap, sortedValues);
    for (auto x : sortedValues) 
    {
      list1.AddAtTail(x.first, x.second);
    }
		list1.Print(ofs);
	}
}