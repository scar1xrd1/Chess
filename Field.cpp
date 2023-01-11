#include "Field.h"

Field::Field()
{
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++)
        {
            board[j * 7][abs(i * 7 - 0)].add("rook", 1 - j, (char)(97 + abs(i * 7 - 0)) + to_string((1 - j) * 7 + 1));
            board[j * 7][abs(i * 7 - 1)].add("horse", 1 - j, (char)(97 + abs(i * 7 - 1)) + to_string((1 - j) * 7 + 1));
            board[j * 7][abs(i * 7 - 2)].add("bishop", 1 - j, (char)(97 + abs(i * 7 - 2)) + to_string((1 - j) * 7 + 1));

        }
        board[i * 7][3].add("queen", 1 - i, (char)(100) + to_string((1 - i) * 7 + 1));
        board[i * 7][4].add("king", 1 - i, (char)(101) + to_string((1 - i) * 7 + 1));
        for (int k = 0; k < 8; k++)
        {
            board[1 + 5 * i][k].add("pawn", 1 - i, (char)(97 + k) + to_string((1 - i) * 5 + 2));
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[2 + i][j].add("empty", -1, (char)(97 + j) + to_string((5 - i) + 1));
        }
    }

    //TEST
    board[5][3].add("pawn", 1, "d3");
    board[5][5].add("pawn", 1, "f3");
}

vector<string>& Field::CalculateMoves(string pos)
{
    int i = 7 - (pos[1] - '0' - 1);
    int j = (int)pos[0] - 97;
    cout << pos << " possible moves: " << endl;
    return CalculateMoves(i, j);
    
}

vector<string>& Field::CalculateMoves(int i, int j)
{
    vector<string> possible, temp;

    switch (board[i][j].getType()) {
    case 5://pawn (peshka)
        int direction = board[i][j].getSide() * 2 - 1;
        //moves
        if (board[i + direction][j].getType() == 6) {//if the square ahead is free
            temp.push_back(board[i + direction][j].getPos());

            if (i == 7 - (board[i][j].getSide() * 5 + 1)) {//if the pawn haven`t made a move yet then it can move by 2 ahead
                if (board[i + 2 * direction][j].getType() == 6) {//if the square ahead is free
                    temp.push_back(board[i + 2 * direction][j].getPos());
                }
            }
        }
        //beats
        for (int k = 0; k < 2; k++)
        {
            if (0 <= j - 1 + k * 2 <= 7) {
                if(board[i + direction][j - 1 + k * 2].getType() != 6/*if there`s a figure*/
                    && board[i + direction][j - 1 + k * 2].getSide() != board[i][j].getSide())//and its the opponent`s figure
                    temp.push_back(board[i + direction][j - 1 + k * 2].getPos());
            }
        }
    }
    
    for (string n : temp) {
        if (true) {//here must be a function that looks for check if this move made
            possible.push_back(n);
            cout << n << endl;
        }
    }
    return possible;
}
