#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "ArgumentManager.h"
using namespace std;

int fun(int lastIndex, int sum, string decodedLine)
{
	for(int a = 0; a < decodedLine.length(); a++)
	{
		sum = sum + (decodedLine[a] - '0');
	}
	return sum;
}

int main(int argc, char *argv[])
{
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ofstream out(am.get("output"));
  string in = "";
  int count = 0;
  vector<string> lines;
  vector<string> ids;
  vector<string> lineChars;
  vector<string> decodedLines;
	if (input.peek() != EOF)
  {
    while (getline(input, in)) // Clean up blank spaces, \n and \r, and skip blank lines
    {
      in.erase(remove(in.begin(), in.end(), '\n'), in.end());
      in.erase(remove(in.begin(), in.end(), '\r'), in.end());
      in.erase(remove(in.begin(), in.end(), ' '), in.end());
      if (in.size() == 0)
        continue; // continue to process the input below
      int count = 0;
      if (in.find(";id:") != string::npos)  // Ensuring the entry is valid, if valid add to lines vector
      {
        if (isalpha(in[0]))
        {
          for (auto entry : in)
          {
            if (!isalpha(entry) && !isdigit(entry) && entry != ';' && entry != ':' && entry != '+')
              count++;
          }
            if (count == 0)
              lines.push_back(in);
        }
      }
    }
    for (auto line : lines) // Cutting up the lines and putting ids into their own vectors
    {
      string id = line.substr(line.find(";id:") + 4, line.length() - 1);
      ids.push_back(id);
      string lineChar = line.substr(0, line.find("id:"));
      lineChars.push_back(lineChar);
    }
    for (int x = 0; x < ids.size(); x++) // Decoding the ids and characters and putting them into a vector
    {
      string decodedLine = "";
      for (int y = 0; y < ids.at(x).length(); y++)
      {
        char selectedChar = ids.at(x).at(y);
        if (isdigit(selectedChar))
        {
          decodedLine += selectedChar;
        }
        else if (isalpha(selectedChar))
        {
          if (lineChars.at(x).find(selectedChar) != string::npos)
          {
            int startIndex = lineChars.at(x).find(selectedChar) + 2;
            int endIndex = lineChars.at(x).find(';', startIndex);
            decodedLine += lineChars.at(x).substr(startIndex, endIndex - startIndex);
          }
        }
        else if (selectedChar == '+')
          decodedLine += "+";
      }
      vector<int> plusIndex; // Replacing the + with the repeated sum of the previous digits
      int lastIndex = 0, sum = 0, total = 0, totalTwo = 0;
			string smallLine = decodedLine.substr(0, decodedLine.find('+'));
      while (decodedLine.find('+'/*, lastIndex*/) != string::npos)
      {
				  smallLine = decodedLine.substr(0, decodedLine.find('+'));
					sum = fun(0, 0, smallLine);
					string sumString = to_string(sum);
					lastIndex++;
					total = 0;
					do
					{
						total = 0;
						for(int i = 0; i < sumString.length(); i++)
							{
								total += sumString[i] - '0';
							}
						sumString = to_string(total);
						plusIndex.push_back(total);
					} while(total > 9);
				decodedLine[decodedLine.find('+')] = (char)(total + '0');
      }
			decodedLines.push_back(decodedLine);
    }
    for (int x = 0; x < decodedLines.size(); x++)
      (x == decodedLines.size() - 1) ? (out << decodedLines.at(x)) : (out << decodedLines.at(x) << endl);
		out << endl;
  }
}
