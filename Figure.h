#pragma once
#include <iostream>
#include <vector>

using namespace std;

const string types[7] = { "king", "queen", "bishop", "horse", "rook", "pawn" , "empty" };
class Figure
{
private:
    int type;
    int side;//white is 0
    string position;//like e2
public:

    

    Figure();
    void add(string type, int side, string pos);

    int getType() { return type; };
    int getSide() { return side; };
    string getPos() { return position; };
};

