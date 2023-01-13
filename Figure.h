#pragma once
#include <iostream>
#include <vector>

using namespace std;

const string types[8] = { "king", "queen", "bishop", "horse", "rook", "pawn" , "empty", "en passant"};
class Figure
{
private:
    int type;
    int side;//white is 0
    string position;//like e2
public:

    

    Figure();
    void add(string type, int side, string pos);
    void enPassant() { this->type = 7;}
    void pawnUpgrade(int type) { this->type = type; }

    int getType() { return type; };
    int getSide() { return side; };
    string getPos() { return position; };

    void setPos(string newPos) { position = newPos; }

    void makeEmpty() { side = -1; type = 6; }
};

