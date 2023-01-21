#pragma once
#include "Figure.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
using namespace sf;
using namespace std;

class Field
{
private:
    Figure board[8][8];
    vector<int> clickedX;
    vector<int> clickedY;

    int turn;//which side is moving
    bool checked;//whether current side cecked or not
    int gameEnd;//which side won; 2 in case of draw

    int move_king = 0, move_rook = 0; // for castling

    string pawnUpgrade;//contains position of the pawn that reached the edge
    string enPassant;//en passant position; "none" by default
    string kingPos[2];//king positions for check
public:
    Vector2i posToInts(string pos);
    Figure& getFigure(Vector2i pos) { return board[pos.x][pos.y]; }
    Figure& getFigure(string pos) { return getFigure(posToInts(pos)); };
    string getPawnUpgrade() { return pawnUpgrade; }
    int getTurn() { return turn; }

    void setPawnUpgrade(string val) { pawnUpgrade = val; }

    Field();

    vector<string> calculateMoves(string pos, bool checkLook) { return calculateMoves(posToInts(pos), checkLook); };
    vector<string> calculateMoves(Vector2i pos, bool checkLook);
    bool check(int side);//look if this side checked
    bool endCheck();//mate checking after the last move

    bool moveIsPossible(string current, bool boolCheck);;//check if selected move is possible
    bool moveIsPossible(Vector2i clicked, string current, bool boolCheck);//check if selected move is possible

    void mouseClick(Vector2i pos);
    void swapFigures(Figure& moving, Figure& beaten);
    //void operator = (vector<string>& first, vector<string>& second);

};