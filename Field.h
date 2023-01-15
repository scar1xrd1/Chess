#pragma once
#include "Figure.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using namespace sf;
using namespace std;



class Field
{
private:
    Figure board[8][8];
    vector<int> clickedX;
    vector<int> clickedY;
    string pawnUpgrade;//contains position of the pawn that reached the edge

    int turn;//which side is moving
    string enPassant;//en passant position; "none" by default

public:
    Vector2i posToInts(string pos);
    Figure& getFigure(Vector2i pos) { return board[pos.x][pos.y]; }
    Figure& getFigure(string pos) { return getFigure(posToInts(pos)); };
    string getPawnUpgrade() { return pawnUpgrade; }
    int getTurn() { return turn; }

    void setPawnUpgrade(string val) { pawnUpgrade = val; }

    Field();

    vector<string> CalculateMoves(string pos) { return CalculateMoves(posToInts(pos)); };
    vector<string> CalculateMoves(Vector2i pos);

    void mouseClick(Vector2i pos);
    //void operator = (vector<string>& first, vector<string>& second);

};
