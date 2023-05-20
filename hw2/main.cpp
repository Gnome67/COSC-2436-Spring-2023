#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include "ArgumentManager.h"

using namespace std;

int partition(int arr[], int low, int high)
{
  int pivot = arr[high];
  int l = low;
  int h = high-1;
  while(l <= h)
	{
    while(arr[l] < pivot) { l++; }
    while(h >= low && arr[h] >= pivot) { h--; }
    if(l <= h) { swap(arr[l++],arr[h--]); }
  }
  swap(arr[l],arr[high]);
  return l;
}

void quickSort(int arr[], int low, int high, int size, int& count)
{
	if (low < high)
	{
		int pivotIndex = partition(arr, low, high);
    	count++;
    	if(pivotIndex == ((size-1)/2)) { return; }
    	if(pivotIndex < ((size-1)/2)) { quickSort(arr, pivotIndex + 1, high, size, count); }
    	if(pivotIndex > ((size-1)/2)) { quickSort(arr, low, pivotIndex - 1, size, count); }
	} else { count++; }
}

int main(int argc, char *argv[]) {
	ArgumentManager am(argc, argv);
	ifstream input(am.get("input"));
	ofstream out(am.get("output"));
	string in = "";
	int seed = 0, size = 0, count = 0;
	if (input.peek() != EOF)
	{
		input >> seed;
		input >> size;
		int* dynamic = new int[size];
		srand(seed);
		int randNum = random();
		for(int x = 0; x < size; x++)
		{
			dynamic[x] = randNum;
			randNum = random();
		}
		quickSort(dynamic, 0, size-1, size, count);
		out << dynamic[(size-1)/2] << endl;
		out << count << endl;
	}
}