#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "ArgumentManager.h"
using namespace std;

bool found(int r, int c, char **wordSoup, bool **visited, int row, int column, string word, int counter)
{
  if (r < 0 || c < 0 || r >= row || c >= column || visited[r][c] == true || wordSoup[r][c] != word[counter]) {
    return false; //base case
  }
  visited[r][c] = true; //mark visited
	if(counter == word.length()-1)
	{
		return true;
	}
	if(found(r - 1, c, wordSoup, visited, row, column, word, counter+1) || found(r + 1, c, wordSoup, visited, row, column, word, counter+1) || found(r, c - 1, wordSoup, visited, row, column, word, counter+1) || found(r, c + 1, wordSoup, visited, row, column, word, counter+1))
	{
		return true;
	} else {
  	visited[r][c] = false; //unmark visited
		return false;
	}
}

int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);
    ifstream input(am.get("input"));
    ofstream out(am.get("output"));

    string in = "";
    string m = "";
    string n = "";
    string word = "";
	int counter = 0;
	bool isPossible = false;
	bool check = false;
    if (input.peek() != EOF)
    {
        input >> m;
        input >> n;
        int rows = stoi(m);
        int columns = stoi(n);
        char** wordSoup = new char*[rows];
        bool** visited = new bool*[rows];
		for(int a = 0; a < rows; a++)
		{
			wordSoup[a] = new char[columns];
			visited[a] = new bool[columns];
		}
        for(int x = 0; x < rows; x++)
        {
            for(int y = 0; y < columns; y++)
            {
              input >> wordSoup[x][y];
            }
        }
		for(int x = 0; x < rows; x++)
        {
            for(int y = 0; y < columns; y++)
            {
              visited[x][y] = false;
            }
        }
        input >> word;
		for (int i = 0; i < rows; i++)
		{
    	    for (int j = 0; j < columns; j++)
			{
      	        if (wordSoup[i][j] == word[counter] && found(i, j, wordSoup, visited, rows, columns, word, counter) && !(check))
				{
        		    isPossible = true;
					check = true;
      			}
    		}
  		}
    }
		if(isPossible == true)
    {
        out << "true";
    } else {
        out << "false";
    }
    return 0;
}