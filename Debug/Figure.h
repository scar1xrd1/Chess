#pragma once
#include <iostream>
#include <vector>

using namespace std;

const string types[7] = { "king", "queen", "bishop", "horse", "rook", "pawn" , "empty" };

class Figure{
private:
    int type;
    int side;// ÖÂÅÒ ÔÈÃÓÐÛ (0 - áåëûå, 1 - ÷¸ðíûå)
    string position;//Òèï e2
public:

    Figure();
    void add(string type, int side, string pos);
    void pawnUpgrade(int type) { this->type = type; }

    int getType() { return type; };
    int getSide() { return side; };
    string getPos() { return position; };

    void setPos(string newPos) { position = newPos; }

    void makeEmpty() { side = -1; type = 6; }
};
