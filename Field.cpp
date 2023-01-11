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
}
