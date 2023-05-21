#include <vector>

using namespace std;

bool moveVector(int x, int y, int rows, int cols, const vector<vector<int>> &beenTo) { return (x >= 0) && (x < rows) && (y >= 0) && (y < cols) && (beenTo[x][y] == 0); }

int CountOfMoves(int x, int y, int rows, int cols, const vector<vector<int>> &beenTo, const vector<int> &moving_x, const vector<int> &moving_y)
{
  int sum = 0;
  for (int i = 0; i < 8; i++) { if (moveVector(x + moving_x[i], y + moving_y[i], rows, cols, beenTo)) { sum++; } }
  return sum;
}

bool isPossible(int rows, int cols)
{
  vector<vector<int>> beenTo(rows, vector<int>(cols, 0));
  beenTo[0][0] = 1;
    vector<int> moving_x = {2, 1, -1, -2, -2, -1, 1, 2};
    vector<int> moving_y = {1, 2, 2, 1, -1, -2, -2, -1};
    int x = 0, y = 0, moving_count = 1;
    while (moving_count < rows * cols)
		{
      int minimumIndex = -1, minimumDigit = 9;
      for (int i = 0; i < 8; i++)
			{
        int after_x = x + moving_x[i], after_y = y + moving_y[i];
        if (moveVector(after_x, after_y, rows, cols, beenTo))
				{
          int digit = CountOfMoves(after_x, after_y, rows, cols, beenTo, moving_x, moving_y);
          if (digit < minimumDigit)
					{
            minimumDigit = digit;
          	minimumIndex = i;
          }
				}
    	}
      if (minimumIndex == -1) { break; }
      x += moving_x[minimumIndex];
      y += moving_y[minimumIndex];
      moving_count++;
      beenTo[x][y] = moving_count;
  	}
  return moving_count == rows * cols;
}