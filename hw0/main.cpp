#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "ArgumentManager.h"
using namespace std;

int cardCheck(string card, int cardsDealt[][4])
{
		if(card.length() == 0)
		{
			return 0;
		}
    if(card.length() == 3)
    {
        if(card.find("S") == 2) //if it a spades card
        {
            cardsDealt[9][0] = 1;
            return 1;
        }
        else if(card.find("H") == 2) //if it is a hearts card
        {
            cardsDealt[9][1] = 1;
            return 1;
        }
        else if(card.find("C") == 2) //if it is a clubs card
        {
            cardsDealt[9][2] = 1;
            return 1;
        }
        else if(card.find("D") == 2) //if it is a diamonds card
        {
            cardsDealt[9][3] = 1;
            return 1;
        }
        return 1;
    }
    else if(card.length() == 2)
    {
        if(isdigit(card[0])) //if it is ace of diamonds, 2 of diamonds, 3 of diamonds, etc.
        {
            int x = stoi(card);
            if(card.find("S") == 1) //if it a spades card
            {
                cardsDealt[x-1][0] = 1;
                return 1;
            }
            else if(card.find("H") == 1) //if it is a hearts card
            {
                cardsDealt[x-1][1] = 1;
                return 1;
            }
            else if(card.find("C") == 1) //if it is a clubs card
            {
                cardsDealt[x-1][2] = 1;
                return 1;
            }
            else if(card.find("D") == 1) //if it is a diamonds card
            {
                cardsDealt[x-1][3] = 1;
                return 1;
            }
        }
        else if(card.find("J") == 0) //if it is a jack of diamonds, jack of hearts, etc.
        {
            if(card.find("S") == 1)
            {
                cardsDealt[10][0] = 1;
                return 1;
            }
            else if(card.find("H") == 1)
            {
                cardsDealt[10][1] = 1;
                return 1;
            }
            else if(card.find("C") == 1)
            {
                cardsDealt[10][2] = 1;
                return 1;
            }
            else if(card.find("D") == 1)
            {
                cardsDealt[10][3] = 1;
                return 1;
            }
        }
        else if(card.find("Q") == 0) //same as jack but for queen
        {
            if(card.find("S") == 1)
            {
                cardsDealt[11][0] = 1;
                return 1;
            }
            else if(card.find("H") == 1)
            {
                cardsDealt[11][1] = 1;
                return 1;
            }
            else if(card.find("C") == 1)
            {
                cardsDealt[11][2] = 1;
                return 1;
            }
            else if(card.find("D") == 1)
            {
                cardsDealt[11][3] = 1;
                return 1;
            }
        }
        else if(card.find("K") == 0) //same as jack but for king
        {
            if(card.find("S") == 1)
            {
                cardsDealt[12][0] = 1;
                return 1;
            }
            else if(card.find("H") == 1)
            {
                cardsDealt[12][1] = 1;
                return 1;
            }
                else if(card.find("C") == 1)
            {
                cardsDealt[12][2] = 1;
                return 1;
            }
            else if(card.find("D") == 1)
            {
                cardsDealt[12][3] = 1;
                return 1;
            }
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);
    ifstream input(am.get("input"));
    ifstream command(am.get("command"));
    ofstream out(am.get("output"));

    //ifstream input("input1.txt");
    //ofstream out("output1.txt");

    string in = "";
		string card = "";
    int cardsDealt[13][4];
    for(int a = 0; a < 13; a++) //rows
    {
        for(int b = 0; b < 4; b++) //columns
        {
            cardsDealt[a][b] = 0; //initialize the 2d array
        }
    }
    if (input.peek() != EOF)
    {
        while (getline(input, in))
        {
            // Clean up blank spaces, \n and \r, and skip blank lines
            in.erase(remove(in.begin(), in.end(), '\n'), in.end());
            in.erase(remove(in.begin(), in.end(), '\r'), in.end());
            in.erase(remove(in.begin(), in.end(), ' '), in.end());
            if (in.size() == 0)
                continue;
        }
		int nextComma = in.find(",");
		if(nextComma > 2)
		{
			card = in.substr(0,3); //prepare the next card, reset while loop until master string is empty
		} else {
			card = in.substr(0,2); //prepare the next card, reset while loop until master string is empty
		}
        int value = cardCheck(card, cardsDealt);
        in = in.substr(nextComma+1, in.size()-1);
		while(value == 1)
        {
			nextComma = in.find(",");
			if(nextComma > 2) //if the card is 3 length (i.e. 10S)
			{
				card = in.substr(0,3); //prepare the next card, reset while loop until master string is empty
			} else { //if the card is 2 length (i.e. 9S)
				card = in.substr(0,2); //prepare the next card, reset while loop until master string is empty
			}
            value = cardCheck(card, cardsDealt);
			in = in.substr(nextComma+1, in.size()-1);
        }
        for(int c = 0; c < 13; c++) //rows
        {
            for(int d = 0; d < 4; d++) //column
            {
                out << cardsDealt[c][d] << " ";
            }
            out << endl;
        }
    }
    return 0;
}