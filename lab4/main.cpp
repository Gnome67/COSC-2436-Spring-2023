#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <fstream>
//#include "Queues.h"
#include "Knight.h"
#include "ArgumentManager.h"

using namespace std;

int main(int argc, char* argv[])
{
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ofstream out(am.get("output"));
	//Queue a;
	int x = 0, y = 0;
	input >> x >> y;
 	int sum = x * y;
	if(sum % 2 != 0 || x % 2 != 0 && y % 2 != 0 || x <= y && x == 1 || x <= y && x == 2 || x <= y && x == 4 || x <= y && x == 3 && y == 4 || x <= y && x == 3 && y == 6 || x <= y && x == 3 && y == 8)
	{
		out << "A closed tour does not exist!"; 
		return 0;
	}
	bool checkMate = /*isPossible(x,y);*/ true;
	if(checkMate == true) { out << "A closed tour exists!"; }
	else { out << "A closed tour does not exist!"; }
}