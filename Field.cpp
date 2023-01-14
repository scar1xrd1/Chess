#include "Field.h"

Vector2i Field::posToInts(string pos) {
    int i = 7 - (pos[1] - '0' - 1);
    int j = (int)pos[0] - 97;
    return Vector2i(i, j);
}

Field::Field() {
    pawnUpgrade = "none";
    //DRAWING FIGURES AND EMPTY CELLS
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            board[j * 7][abs(i * 7 - 0)].add("rook", 1 - j, (char)(97 + abs(i * 7 - 0)) + to_string((1 - j) * 7 + 1));
            board[j * 7][abs(i * 7 - 1)].add("horse", 1 - j, (char)(97 + abs(i * 7 - 1)) + to_string((1 - j) * 7 + 1));
            board[j * 7][abs(i * 7 - 2)].add("bishop", 1 - j, (char)(97 + abs(i * 7 - 2)) + to_string((1 - j) * 7 + 1));
        }
        board[i * 7][3].add("queen", 1 - i, (char)(100) + to_string((1 - i) * 7 + 1));
        board[i * 7][4].add("king", 1 - i, (char)(101) + to_string((1 - i) * 7 + 1));
        for (int k = 0; k < 8; k++) {
            board[1 + 5 * i][k].add("pawn", 1 - i, (char)(97 + k) + to_string((1 - i) * 5 + 2));
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            board[2 + i][j].add("empty", -1, (char)(97 + j) + to_string((5 - i) + 1));
        }
    }
}

vector<string> Field::CalculateMoves(Vector2i pos) {
    int i = pos.x;
    int j = pos.y;
    vector<string> possible, temp;

    int direction;

    int dir = board[i][j].getSide() * 2 - 1; // for king and bishop
    int dirRev = -(board[i][j].getSide() * 2 - 1);
    int enemySide = board[i][j].getSide();
    enemySide = (board[i][j].getSide() + 1) % 2;
    bool canRev = false;

    if (enemySide == 1 && 8 <= i + dirRev <= 0) canRev = true; // if !out_of_range
    else if (enemySide == 0 && 0 >= i + dirRev >= 8) canRev = true;

    int len = (int)board[i][j].getPos()[0] - 97;
    int iter = 2;
    int iterVert = 2;

    switch (board[i][j].getType()) {

    case 1: // QUEEN

        direction = board[i][j].getSide() * 2 - 1;

        for (int n = 0; n < 8; n++) { // Square AHEAD

            if (board[i + n * direction][j].getSide() == board[i][j].getSide() && n != 0)
                break;

            if (board[i + n * direction][j].getType() == 6)
                temp.push_back(board[i + n * direction][j].getPos());

            if (board[i + n * direction][j].getSide() == enemySide) {
                temp.push_back(board[i + n * direction][j].getPos());
                break;
            }
        }

        for (int n = 0; n < 8; n++) { // square BACK

            if (board[i - n * direction][j].getSide() == board[i][j].getSide() && n != 0)
                break;

            if (board[i - n * direction][j].getType() == 6)
                temp.push_back(board[i - n * direction][j].getPos());

            if (board[i - n * direction][j].getSide() == enemySide) {
                temp.push_back(board[i - n * direction][j].getPos());
                break;
            }
        }

        for (int n = 0; n < 8; n++) { // LEFT square 

            if (board[i][j + n * direction].getSide() == board[i][j].getSide() && n != 0)
                break;

            if (board[i][j + n * direction].getType() == 6)
                temp.push_back(board[i][j + n * direction].getPos());

            if (board[i][j + n * direction].getSide() == enemySide) {
                temp.push_back(board[i][j + n * direction].getPos());
                break;
            }
        }

        for (int n = 0; n < 8; n++) { // RIGHT square 

            if (board[i][j - n * direction].getSide() == board[i][j].getSide() && n != 0)
                break;

            if (board[i][j - n * direction].getType() == 6)
                temp.push_back(board[i][j - n * direction].getPos());

            if (board[i][j - n * direction].getSide() == enemySide) {
                temp.push_back(board[i][j - n * direction].getPos());
                break;
            }
        }

        for (int n = 0; n < 8; n++) {// LEFT UP square
            if (board[i - n][j - n].getType() == 6)
                temp.push_back(board[i - n][j - n].getPos());

            if (board[i - n][j - n].getSide() == board[i][j].getSide() && n != 0)
                break;

            if (board[i - n][j - n].getSide() == enemySide) {
                temp.push_back(board[i - n][j - n].getPos());
                break;
            }
        }

        for (int n = 0; n < 8; n++) { // RIGHT DOWN square            
            if (board[i + n][j + n].getType() == 6)
                temp.push_back(board[i + n][j + n].getPos());

            if (board[i + n][j + n].getSide() == board[i][j].getSide() && n != 0)
                break;

            if (board[i + n][j + n].getSide() == enemySide) {
                temp.push_back(board[i + n][j + n].getPos());
                break;
            }
        }

        for (int n = 0; n < 8; n++) { // RIGHT UP square           
            if (board[i + n][j - n].getType() == 6)
                temp.push_back(board[i + n][j - n].getPos());

            if (board[i + n][j - n].getSide() == board[i][j].getSide() && n != 0)
                break;

            if (board[i + n][j - n].getSide() == enemySide) {
                temp.push_back(board[i + n][j - n].getPos());
                break;
            }
        }

        for (int n = 0; n < 8; n++) { // LEFT DOWN square        
            if (board[i - n][j + n].getType() == 6)
                temp.push_back(board[i - n][j + n].getPos());

            if (board[i - n][j + n].getSide() == board[i][j].getSide() && n != 0)
                break;

            if (board[i - n][j + n].getSide() == enemySide) {
                temp.push_back(board[i - n][j + n].getPos());
                break;
            }
        }

    case 4: // ROOK

        direction = board[i][j].getSide() * 2 - 1;

        for (int n = 0; n < 8; n++) { // Square AHEAD

            if (board[i + n * direction][j].getSide() == board[i][j].getSide() && n != 0)
                break;

            if (board[i + n * direction][j].getType() == 6)
                temp.push_back(board[i + n * direction][j].getPos());

            if (board[i + n * direction][j].getSide() == enemySide) {
                temp.push_back(board[i + n * direction][j].getPos());
                break;
            }
        }

        for (int n = 0; n < 8; n++) { // square BACK

            if (board[i - n * direction][j].getSide() == board[i][j].getSide() && n != 0)
                break;

            if (board[i - n * direction][j].getType() == 6)
                temp.push_back(board[i - n * direction][j].getPos());

            if (board[i - n * direction][j].getSide() == enemySide) {
                temp.push_back(board[i - n * direction][j].getPos());
                break;
            }
        }

        for (int n = 0; n < 8; n++) { // LEFT square 

            if (board[i][j + n * direction].getSide() == board[i][j].getSide() && n != 0)
                break;

            if (board[i][j + n * direction].getType() == 6)
                temp.push_back(board[i][j + n * direction].getPos());

            if (board[i][j + n * direction].getSide() == enemySide) {
                temp.push_back(board[i][j + n * direction].getPos());
                break;
            }
        }

        for (int n = 0; n < 8; n++) { // RIGHT square 

            if (board[i][j - n * direction].getSide() == board[i][j].getSide() && n != 0)
                break;

            if (board[i][j - n * direction].getType() == 6)
                temp.push_back(board[i][j - n * direction].getPos());

            if (board[i][j - n * direction].getSide() == enemySide) {
                temp.push_back(board[i][j - n * direction].getPos());
                break;
            }
        }


    case 5:// PAWN
        direction = board[i][j].getSide() * 2 - 1;
        //moves
        if (board[i + direction][j].getType() == 6) {// if the square AHEAD is empty
            temp.push_back(board[i + direction][j].getPos());

            if (i == 7 - (board[i][j].getSide() * 5 + 1)) { //if the pawn haven`t made a move yet then it can move by 2 ahead
                if (board[i + 2 * direction][j].getType() == 6) {   //if the square ahead is free
                    temp.push_back(board[i + 2 * direction][j].getPos());
                }
            }
        }
        //beats
        for (int k = 0; k < 2; k++) {
            if (0 <= j - 1 + k * 2 <= 7) {
                if (board[i + direction][j - 1 + k * 2].getType() != 6/*if there`s a figure*/
                    && board[i + direction][j - 1 + k * 2].getSide() != board[i][j].getSide())//and its the opponent`s figure
                    temp.push_back(board[i + direction][j - 1 + k * 2].getPos());
            }
        }
    }

    for (string n : temp) {
        if (true) {//here must be a function that looks for check if this move made
            if (getFigure(n).getType() != 0) {//you can`t bet the king
                possible.push_back(n);
                cout << n << endl;
            }
        }
    }
    if (possible.size() == 0) return { "none" };
    return possible;
}

void Field::mouseClick(Vector2i pos) {
    int i = pos.y / 50;
    int j = pos.x / 50;
    if (clickedX.size() == 0) {//������ ����
        if (board[i][j].getType() != 6) {//� �� �� ������
            clickedX.push_back(j);
            clickedY.push_back(i);//push the button position in board to vector
            return;
        }
    }
    else if (!(i == clickedY[0] && j == clickedX[0])) { //the second clicked tile is not the same as first
        vector<string> possible = CalculateMoves(Vector2i(clickedY[0], clickedX[0]));
        if (find(possible.begin(), possible.end(), board[i][j].getPos()) != possible.end()) {
            if (board[i][j].getType() != 6) {
                board[i][j].makeEmpty();
            }

            std::swap(board[i][j], board[clickedY[0]][clickedX[0]]);

            string temp = board[i][j].getPos();

            board[i][j].setPos(board[clickedY[0]][clickedX[0]].getPos());

            board[clickedY[0]][clickedX[0]].setPos(temp);//������ ���������� ������

            Figure newPos = board[i][j];
            if (newPos.getType() == 5 && (newPos.getPos()[1] == '1' || newPos.getPos()[1] == '8')) {  //it`s pawn on the edge line
                pawnUpgrade = newPos.getPos();
            }
        }
    }
    clickedX.clear();
    clickedY.clear();
}