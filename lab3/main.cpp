#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include "ArgumentManager.h"

using namespace std;

class Heap
{
	public:
  	Heap(int*, int, bool);
  	void Sort(int*, int, int);
  	void Heapify(int*, int);
  	void Print(ostream &fout, int c, int needValues);
	private:
  	int* data;
  	int count;
  	bool isMaxHeap;
};

Heap::Heap(int* values, int num, bool YorN)
{
  data = new int[num];
  data = values;
  count = num;
  isMaxHeap = YorN;
}
void Heap::Sort(int* values, int n, int needAmount)
{
  for(int j = count-1; j > n - needAmount -1; j--)
	{
    for(int i = count/2; i >= 0; i--) { Heapify(values, i); }
    int temp = data[0];
    data[0] = data[j];
    data[j] = temp;
    count--;
  }
}
void Heap::Heapify(int* values, int i)
{
  int left = 2 * i + 1, right = 2* i + 2;
  int max = i, min = i;
  if(isMaxHeap == true)
	{
    if(left< count and data[left] > data[max]) { max = left; }
    if(right < count and data[right] > data[max]) { max = right; }
    if(max != i)
		{
    	int temp = data[i];
    	data[i] = data[max];
    	data[max] = temp; 
    }
  } else {
    if(left< count and data[left] < data[min]) { min = left; }
    if(right < count and data[right] < data[min]) { min = right; }
    if(min != i)
		{
    	int temp = data[i];
   		data[i] = data[min];
    	data[min] = temp; 
    }
  }
}
void Heap::Print(ostream &out, int c,int needValues) { for(int i = c -1; i >= c - needValues; i--) { out << data[i] << endl; } }

int main(int argc, char* argv[])
{
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ofstream out(am.get("output"));
  string in = "", sizeCheck = ""; //input string, if we are looking for biggest or smallest
	int seed = 0, size = 0, k = 0; //the given seed, the size of heap, and how many of the k-th largest/smallest
	input >> seed >> size;
	srand(seed);
	int* dynamic = new int[size];
	for(int x = 0; x < size; x++) { dynamic[x] = random(); }
	input >> sizeCheck >> k;
	Heap heapMe(dynamic, size, sizeCheck == "largest");
	heapMe.Sort(dynamic, size, k);
	heapMe.Print(out, size, k);
	delete[] dynamic;
	return 0;
}