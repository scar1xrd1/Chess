#include "Figure.h"

Figure::Figure() {}

void Figure::add(string type, int side, string pos)
{
    this->side = side;
    this->position = pos;
    for (int i = 0; i < 6; i++) {
        if (types[i] == type) {
            this->type = i;
            break;
        }
    }
}

vector<string>& Figure::CalculateMoves()
{
    vector<string> possible;
    switch (type) {
    case 5://pawn (peshka)
        cout << "bebra";
    }
    return possible;
    // TODO: вставьте здесь оператор return
}
