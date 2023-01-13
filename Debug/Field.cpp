#include "Field.h"

Vector2i Field::posToInts(string pos){
    int i = 7 - (pos[1] - '0' - 1);
    int j = (int)pos[0] - 97;
    return Vector2i(i, j);
}

Field::Field(){
    pawnUpgrade = "none";
    //ОТРИСОВКА ФИГУР И ПУСТЫХ КЛЕТОЧЕК
    for (int i = 0; i < 2; i++) { 
        for (int j = 0; j < 2; j++){
            board[j * 7][abs(i * 7 - 0)].add("rook", 1 - j, (char)(97 + abs(i * 7 - 0)) + to_string((1 - j) * 7 + 1));
            board[j * 7][abs(i * 7 - 1)].add("horse", 1 - j, (char)(97 + abs(i * 7 - 1)) + to_string((1 - j) * 7 + 1));
            board[j * 7][abs(i * 7 - 2)].add("bishop", 1 - j, (char)(97 + abs(i * 7 - 2)) + to_string((1 - j) * 7 + 1));
        }
        board[i * 7][3].add("queen", 1 - i, (char)(100) + to_string((1 - i) * 7 + 1));
        board[i * 7][4].add("king", 1 - i, (char)(101) + to_string((1 - i) * 7 + 1));
        for (int k = 0; k < 8; k++){
            board[1 + 5 * i][k].add("pawn", 1 - i, (char)(97 + k) + to_string((1 - i) * 5 + 2));
        }
    } 
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 8; j++){
            board[2 + i][j].add("empty", -1, (char)(97 + j) + to_string((5 - i) + 1));
        }
    }
}

vector<string> Field::CalculateMoves(Vector2i pos){
    int i = pos.x;
    int j = pos.y;
    vector<string> possible, temp;

    int direction;
    int n = 1;

    switch (board[i][j].getType()) {

    case 4: // ЛАДЬЯ

        direction = board[i][j].getSide() * 2 - 1;

        if (board[i + n * direction][j].getType() == 6) {// если квадрат ВПЕРЕДИ пустой
            temp.push_back(board[i + n * direction][j].getPos());
        }
        if (board[i - n * direction][j].getType() == 6) {// если квадрат СЗАДИ пустой
            temp.push_back(board[i - n * direction][j].getPos());
        }
        if (board[i][j + n * direction].getType() == 6) {// если квадрат СЛЕВА пустой
            temp.push_back(board[i][j + n * direction].getPos());
        }
        if (board[i][j - n * direction].getType() == 6) {// если квадрат СПРАВА пустой
            temp.push_back(board[i][j - n * direction].getPos());
        }

       for (int k = 0; k < 2; k++) {
            if ((j - 1 + k * 2) >= 0 && (j - 1 + k * 2) <= 7) {

                //если ВПЕРЕДИ фигура и это фигура противника
                if (board[i + n * direction][j].getType() != 6 && board[i + n * direction][j].getSide() != board[i][j].getSide()) {
                    temp.push_back(board[i + n * direction][j].getPos());
                }
                //если СЗАДИ фигура и это фигура противника
                if (board[i - n * direction][j].getType() != 6 && board[i - n * direction][j].getSide() != board[i][j].getSide()) {
                    temp.push_back(board[i - n * direction][j].getPos());
                }
                //если СЛЕВА фигура и это фигура противника
                if (board[i][j + n * direction].getType() != 6 && board[i][j + n * direction].getSide() != board[i][j].getSide()) {
                    temp.push_back(board[i][j + n * direction].getPos());
                }
                //если СПРАВА фигура и это фигура противника
                if (board[i][j - n * direction].getType() != 6 && board[i][j - n * direction].getSide() != board[i][j].getSide()) {
                    temp.push_back(board[i][j - n * direction].getPos());
                }
            }
        }

         
        

    case 5:// ПЕШКА
        direction = board[i][j].getSide() * 2 - 1;
        //moves
        if (board[i + direction][j].getType() == 6) {//if the square ahead is free
            temp.push_back(board[i + direction][j].getPos());

            if (i == 7 - (board[i][j].getSide() * 5 + 1)) { //if the pawn haven`t made a move yet then it can move by 2 ahead
                if (board[i + 2 * direction][j].getType() == 6) {   //if the square ahead is free
                    temp.push_back(board[i + 2 * direction][j].getPos());
                }
            }
        }
        //beats
        for (int k = 0; k < 2; k++){
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
    if (clickedX.size() == 0) {//ПЕРВЫЙ КЛИК
        if (board[i][j].getType() != 6) {//И ОН НЕ ПУСТОЙ
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

            board[clickedY[0]][clickedX[0]].setPos(temp);//МЕНЯЕМ КООРДИНАТЫ КНОПОК

            Figure newPos = board[i][j];
            if (newPos.getType() == 5 && (newPos.getPos()[1] == '1' || newPos.getPos()[1] == '8')) {  //it`s pawn on the edge line
                pawnUpgrade = newPos.getPos();
            }
        }
    }
    clickedX.clear();
    clickedY.clear();
}