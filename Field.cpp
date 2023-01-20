#include "Field.h"

Vector2i Field::posToInts(string pos)
{
    int i = 7 - (pos[1] - '0' - 1);
    int j = (int)pos[0] - 97;
    //cout << pos << " possible moves: " << endl;
    return Vector2i(i, j);
}

Field::Field() : pawnUpgrade("none"), turn(0), enPassant("none"), gameEnd(-1)
{
    kingPos[0] = "e1";//white king
    kingPos[1] = "e8";//black king
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
    //board[5][3].add("pawn", 1, "d3");
    //board[5][4].add("pawn", 1, "e3");
    //board[5][5].add("pawn", 1, "f3");
    //board[5][5].add("king", 1, "f3");
    //board[4][4].add("horse", 1, "e4");

}

vector<string> Field::calculateMoves(Vector2i pos, bool checkLook)
{
    int i = pos.x;
    int j = pos.y;
    vector<string> possible, temp;

    int direction;


    int dir = board[i][j].getSide() * 2 - 1; // for king and bishop
    int dirRev = -(board[i][j].getSide() * 2 - 1);
    int enemySide = board[i][j].getSide(); enemySide = (board[i][j].getSide() + 1) % 2;
    bool canRev = false;

    if (enemySide == 1 && 8 <= i + dirRev <= 0) canRev = true; // if !out_of_range
    else if (enemySide == 0 && 0 >= i + dirRev >= 8) canRev = true;

    switch (board[i][j].getType()) {
    case 0:// king
    {
        //moves
        //if (board[i + dir][j].getSide() == enemySide || board[i + dir][j].getType() >= 6) //if the square ahead is free
        //    temp.push_back(board[i + dir][j].getPos());
        //if (canRev && board[i + dirRev][j].getSide() == enemySide || board[i + dirRev][j].getType() >= 6) //if the square behind is free
        //    temp.push_back(board[i + dirRev][j].getPos());

        //for (int k = 0; k < 2; k++) {
        //    if (board[i][j - 1 + k * 2].getSide() == enemySide || board[i][j - 1 + k * 2].getType() >= 6) // if the flanks are free 
        //        temp.push_back(board[i][j - 1 + k * 2].getPos());

        //    if (board[i + dir][j - 1 + k * 2].getSide() == enemySide || board[i + dir][j - 1 + k * 2].getType() >= 6) // if the corners are free
        //        temp.push_back(board[i + dir][j - 1 + k * 2].getPos());
        //    if (canRev && board[i + dirRev][j - 1 + k * 2].getSide() == enemySide || board[i + dirRev][j - 1 + k * 2].getType() >= 6) // if the corners are free
        //        temp.push_back(board[i + dirRev][j - 1 + k * 2].getPos());
        //}

        //cout << i << " j: " << j << endl;
        for (int k = 0; k < 4; k++)
        {
            for (int l = 0; l < 2; l++)
            {
                int i1 = i + k % 2 - k / 3 * 2 - l * ((k - 1) % 2);
                int j1 = j - (k - 1) % 2 - l * ((k - ((k / 3) * 4)) % 2);
                if (0 <= i1 && i1 <= 7 && 0 <= j1 && j1 <= 7) {
                    if (board[i1][j1].getSide() == board[i][j].getSide()) continue;
                    temp.push_back(board[i1][j1].getPos());
                }
                
            }
        }
        cout << temp.size();
        break;
    }
    case 1:// QUEEN
    {
        direction = board[i][j].getSide() * 2 - 1;


        for (int n = 1; n <= 7; n++) { // Square AHEAD

            if (i + n * direction < 0 || j < 0 || i + n * direction > 7 || j > 7)
                break;

            if (board[i + n * direction][j].getSide() == board[i][j].getSide()  /*&& direction == -1*/)
                break;

            if (board[i + n * direction][j].getType() >= 6) {
                temp.push_back(board[i + n * direction][j].getPos());
            }

            if (board[i + n * direction][j].getSide() == enemySide) {
                temp.push_back(board[i + n * direction][j].getPos());
                break;
            }
        }

        for (int n = 1; n <= 7; n++) { // Square BACK

            if (i - n * direction < 0 || j < 0 || i - n * direction > 7 || j > 7)
                break;

            if (board[i - n * direction][j].getSide() == board[i][j].getSide())
                break;

            if (board[i - n * direction][j].getType() >= 6) {
                temp.push_back(board[i - n * direction][j].getPos());
            }

            if (board[i - n * direction][j].getSide() == enemySide) {
                temp.push_back(board[i - n * direction][j].getPos());
                break;
            }
        }

        for (int n = 1; n <= 7; n++) { // LEFT square 

            if (i < 0 || j + n * direction < 0 || i > 7 || j + n * direction > 7)
                break;

            if (board[i][j + n * direction].getSide() == board[i][j].getSide() && n != 0)
                break;

            if (board[i][j + n * direction].getType() >= 6)
                temp.push_back(board[i][j + n * direction].getPos());

            if (board[i][j + n * direction].getSide() == enemySide) {
                temp.push_back(board[i][j + n * direction].getPos());
                break;
            }
        }

        for (int n = 1; n <= 7; n++) { // RIGHT square 

            if (i < 0 || j - n * direction < 0 || i > 7 || j - n * direction > 7)
                break;

            if (board[i][j - n * direction].getSide() == board[i][j].getSide() && n != 0)
                break;

            if (board[i][j - n * direction].getType() >= 6)
                temp.push_back(board[i][j - n * direction].getPos());

            if (board[i][j - n * direction].getSide() == enemySide) {
                temp.push_back(board[i][j - n * direction].getPos());
                break;
            }
        }

        for (int n = 0; n < 8; n++) { // LEFT UP SQUARE 
            if (i - n < 0 || j - n < 0 || i - n > 7 || j - n > 7)
                break;

            if (board[i - n][j - n].getType() >= 6)
                temp.push_back(board[i - n][j - n].getPos());

            if (board[i - n][j - n].getSide() == board[i][j].getSide() && n != 0)
                break;

            if (board[i - n][j - n].getSide() == enemySide) {
                temp.push_back(board[i - n][j - n].getPos());
                break;
            }
        }

        for (int n = 0; n < 8; n++) { // RIGHT DOWN SQUARE    
            if (i + n > 7 || j + n > 7 || i + n < 0 || j + n < 0)
                break;

            if (board[i + n][j + n].getType() >= 6)
                temp.push_back(board[i + n][j + n].getPos());

            if (board[i + n][j + n].getSide() == board[i][j].getSide() && n != 0)
                break;

            if (board[i + n][j + n].getSide() == enemySide) {
                temp.push_back(board[i + n][j + n].getPos());
                break;
            }
        }

        for (int n = 0; n < 8; n++) { // RIGHT UP SQUARE       
            if (i + n < 0 || j - n > 7 || i + n > 7 || j - n < 0)
                break;

            if (board[i + n][j - n].getType() >= 6)
                temp.push_back(board[i + n][j - n].getPos());

            if (board[i + n][j - n].getSide() == board[i][j].getSide() && n != 0)
                break;

            if (board[i + n][j - n].getSide() == enemySide) {
                temp.push_back(board[i + n][j - n].getPos());
                break;
            }
        }

        for (int n = 0; n < 8; n++) { // LEFT DOWN SQUARE  
            if (i - n > 7 || j + n < 0 || i - n < 0 || j + n > 7)
                break;

            if (board[i - n][j + n].getType() >= 6)
                temp.push_back(board[i - n][j + n].getPos());

            if (board[i - n][j + n].getSide() == board[i][j].getSide() && n != 0)
                break;

            if (board[i - n][j + n].getSide() == enemySide) {
                temp.push_back(board[i - n][j + n].getPos());
                break;
            }
        }
        break;
    }
    case 2:// bishop (slon)
    {
        for (int n = 0; n < 8; n++) { // left up 
            cout << "n - " << n << endl;
            if (i - n < 0 || j - n < 0) break; // if out of range


            if (board[i - n][j - n].getType() == 6) temp.push_back(board[i - n][j - n].getPos()); // if the corners are free

            if (board[i - n][j - n].getSide() == board[i][j].getSide() && n != 0) break;

            if (board[i - n][j - n].getSide() == enemySide) { // if the square is occupied by a piece from his team
                temp.push_back(board[i - n][j - n].getPos());
                break;
            }
        }

        for (int n = 0; n < 8; n++) { // right down     
            if (i + n > 7 || j + n > 7) break; // if out of range

            if (board[i + n][j + n].getType() >= 6) temp.push_back(board[i + n][j + n].getPos()); // if the corners are free

            if (board[i + n][j + n].getSide() == board[i][j].getSide() && n != 0) break;

            if (board[i + n][j + n].getSide() == enemySide) { // if the square is occupied by a piece from his team
                temp.push_back(board[i + n][j + n].getPos());
                break;
            }
        }

        for (int n = 0; n < 8; n++) { // right up        
            if (i + n > 7 || j - n < 0) break; // if out of range

            if (board[i + n][j - n].getType() >= 6) temp.push_back(board[i + n][j - n].getPos()); // if the corners are free

            if (board[i + n][j - n].getSide() == board[i][j].getSide() && n != 0) break;

            if (board[i + n][j - n].getSide() == enemySide) { // if the square is occupied by a piece from his team
                temp.push_back(board[i + n][j - n].getPos());
                break;
            }
        }

        for (int n = 0; n < 8; n++) { // left down  
            if (i - n < 0 || j + n > 7) break; // if out of range

            if (board[i - n][j + n].getType() >= 6) temp.push_back(board[i - n][j + n].getPos()); // if the corners are free

            if (board[i - n][j + n].getSide() == board[i][j].getSide() && n != 0) break;

            if (board[i - n][j + n].getSide() == enemySide) { // if the square is occupied by a piece from his team
                temp.push_back(board[i - n][j + n].getPos());
                break;
            }
        }
        break;
    }
    case 3://horsey
    {
        for (int k = 0; k < 2; k++)//horizontal vertical
        {
            for (int l = 0; l < 2; l++)//front back
            {
                for (int m = 0; m < 2; m++)//2 branches
                {
                    int m1 = i * (1 - k) + j * k + 2 * m - 1;

                    int l1 = j * (1 - k) + i * k + 2 * (l * 2 - 1);
                    if (l1 >= 0 && m1 >= 0 && l1 <= 7 && m1 <= 7)
                        if (board[m1 * (1 - k) + l1 * k][l1 * (1 - k) + m1 * k].getSide() != board[i][j].getSide())
                            //variable k "turns" the checked combination by 90 degrees
                            temp.push_back(board[m1 * (1 - k) + l1 * k][l1 * (1 - k) + m1 * k].getPos());
                }
            }
        }
        break;
    }
    case 4: // ROOK
    {
        direction = board[i][j].getSide() * 2 - 1;


        for (int n = 1; n <= 7; n++) { // Square AHEAD

            if (i + n * direction < 0 || j < 0 || i + n * direction > 7 || j > 7)
                break;

            if (board[i + n * direction][j].getSide() == board[i][j].getSide()  /*&& direction == -1*/)
                break;

            if (board[i + n * direction][j].getType() >= 6) {
                temp.push_back(board[i + n * direction][j].getPos());
            }

            if (board[i + n * direction][j].getSide() == enemySide) {
                temp.push_back(board[i + n * direction][j].getPos());
                break;
            }
        }

        for (int n = 1; n <= 7; n++) { // Square BACK

            if (i - n * direction < 0 || j < 0 || i - n * direction > 7 || j > 7)
                break;

            if (board[i - n * direction][j].getSide() == board[i][j].getSide())
                break;

            if (board[i - n * direction][j].getType() >= 6) {
                temp.push_back(board[i - n * direction][j].getPos());
            }

            if (board[i - n * direction][j].getSide() == enemySide) {
                temp.push_back(board[i - n * direction][j].getPos());
                break;
            }
        }

        for (int n = 1; n <= 7; n++) { // LEFT square 

            if (i < 0 || j + n * direction < 0 || i > 7 || j + n * direction > 7)
                break;

            if (board[i][j + n * direction].getSide() == board[i][j].getSide() && n != 0)
                break;

            if (board[i][j + n * direction].getType() >= 6)
                temp.push_back(board[i][j + n * direction].getPos());

            if (board[i][j + n * direction].getSide() == enemySide) {
                temp.push_back(board[i][j + n * direction].getPos());
                break;
            }
        }

        for (int n = 1; n <= 7; n++) { // RIGHT square 

            if (i < 0 || j - n * direction < 0 || i > 7 || j - n * direction > 7)
                break;

            if (board[i][j - n * direction].getSide() == board[i][j].getSide() && n != 0)
                break;

            if (board[i][j - n * direction].getType() >= 6)
                temp.push_back(board[i][j - n * direction].getPos());

            if (board[i][j - n * direction].getSide() == enemySide) {
                temp.push_back(board[i][j - n * direction].getPos());
                break;
            }
        }
        break;
    }
    case 5://pawn (peshka)
    {
        int direction = board[i][j].getSide() * 2 - 1;
        //moves
        if (checkLook) {
            if (board[i + direction][j].getType() == 6) {//if the square ahead is free
                temp.push_back(board[i + direction][j].getPos());

                if (i == 7 - (board[i][j].getSide() * 5 + 1)) {//if the pawn haven`t made a move yet then it can move by 2 ahead
                    if (board[i + 2 * direction][j].getType() == 6) {//if the square ahead is free
                        temp.push_back(board[i + 2 * direction][j].getPos());
                    }
                }
            }
        }
        //beats
        for (int k = 0; k < 2; k++)
        {
            if (0 <= j - 1 + k * 2 <= 7) {
                if (board[i + direction][j - 1 + k * 2].getType() != 6/*if there`s a figure*/
                    && board[i + direction][j - 1 + k * 2].getSide() != board[i][j].getSide())//and its the opponent`s figure
                    temp.push_back(board[i + direction][j - 1 + k * 2].getPos());
            }
        }
    }
    }
    Figure beatenTemp;
    for (string n : temp) {//temp is ok, problem is here
        beatenTemp = getFigure(n);//remember the beaten figure
        //string n1 = n;
        swapFigures(board[i][j], getFigure(n));//make a move to check what happens
        if (checkLook) {
            if (check(getFigure(n).getSide())) {//here must be a function that looks for check if this move made
                swapFigures( getFigure(n), board[i][j]);//return to starting position
                getFigure(n) = beatenTemp;//return the beaten figure
                continue;
            }
        }
        
        swapFigures(getFigure(n), board[i][j]);//return to starting position
        getFigure(n) = beatenTemp;//return the beaten figure
        //break;
        if (checkLook && getFigure(n).getType() == 0) continue;//you can`t beat the king while making a move
        possible.push_back(n);
        cout << n << endl;
            //continue;
        
    }

    if (board[i][j].getType() == 0 && checkLook) {
        cout << temp.size() << endl;
        
    }

    cout << "------------------------\n";
    if (possible.size() == 0) return { "none" };
    
    return possible;
}

bool Field::check(int side)
{
    const int enemySide = (side + 1) % 2;
    for (int i = 0; i < 8; i++)//rows
    {
        for (int j = 0; j < 8; j++)//columns
        {
            if (board[i][j].getSide() == enemySide) {//enemy side
                if (moveIsPossible(posToInts(board[i][j].getPos()), kingPos[side], false))
                    return true;
            }
        }
    }
    return false;
}

bool Field::endCheck()
{
    int enemySide = (turn + 1) % 2;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j].getSide() == enemySide) continue;
            vector<string> possibleCurr = calculateMoves(Vector2i(i, j), true);
            if (possibleCurr[0] != "none") {
                return false;
            }
        }
    }
    //if there`s no possible moves
    bool checkTemp = check(turn);
    if (checkTemp) gameEnd = enemySide;//we have a winner!
    else gameEnd = 2;//draw
    return true;
}

inline bool Field::moveIsPossible(string current, bool boolCheck) { return moveIsPossible(Vector2i(clickedY[0], clickedX[0]), current, boolCheck); }

bool Field::moveIsPossible(Vector2i clicked, string current, bool boolCheck)
{
    vector<string> possibleMoves = calculateMoves(clicked, boolCheck);
    return find(possibleMoves.begin(), possibleMoves.end(), current) != possibleMoves.end();
}

void Field::mouseClick(Vector2i pos)
{
    if (gameEnd != -1) {
        cout << "game`s ended already!" << endl;
        return;
    }
    int i = pos.y / 50;
    int j = pos.x / 50;

    if (clickedX.size() == 0) {//the first click
        if (turn != board[i][j].getSide()) return;//you can`t move in the opponent`s turn
        if (board[i][j].getType() != 6) {//and it isn`t empty
            clickedX.push_back(j);
            clickedY.push_back(i);//push the button position in board to vector
            return;
        }
    }
    else if (!(i == clickedY[0] && j == clickedX[0])) {//the second clicked tile is not the same as first
        if (moveIsPossible(board[i][j].getPos(), true)) {//target is succesful
            if (board[clickedY[0]][clickedX[0]].getType() == 5) {//pawn
                if (board[i][j].getType() == 7) {
                    //board[i][j].getSide() * 2 - 1 converts 0 to - 1 and 1 to 1 to know direction of pawn moving
                    getFigure(Vector2i(i + ((turn + 1) % 2) * 2 - 1, j)).makeEmpty();
                }
            }
            swapFigures(board[clickedY[0]][clickedX[0]], board[i][j]);//move figure

            Figure newPos = board[i][j];
            if (newPos.getType() == 5 && (newPos.getPos()[1] == '1' || newPos.getPos()[1] == '8'))//it`s pawn on the edge line
                pawnUpgrade = newPos.getPos();

            if (newPos.getType() == 5) {//pawn
                int horizontalStart = posToInts(board[clickedY[0]][clickedX[0]].getPos()).x;//i coordinate of start position
                int horizontalNow = posToInts(newPos.getPos()).x;//i coordinate of current position

                if (horizontalNow == 4 - turn//pawn is 2 moves from start position
                    && horizontalStart == 1 + 5 * ((1 - turn))) {//and it moved from start
                    board[horizontalStart + ((turn)) * 2 - 1][j].enPassant();//make the middle square en passant
                    if (enPassant != "none") getFigure(enPassant).makeEmpty();
                    enPassant = board[horizontalStart + ((turn)) * 2 - 1][j].getPos();
                }
            }

            if (newPos.getType() == 0) kingPos[turn] = newPos.getPos();

            turn = (turn + 1) % 2;
            cout << turn << endl;
            if (enPassant != "none" && posToInts(enPassant).x / 3 != turn) {//on the next move after the en passant make it empty
                if (getFigure(enPassant).getType() == 7) getFigure(enPassant).makeEmpty();
                enPassant = "none";
            }
        }
    }
    clickedX.clear();
    clickedY.clear();///annulate the clicks

    if (endCheck()) cout << "result is " << gameEnd << endl;
    else checked = check(turn);
}

void Field::swapFigures(Figure& moving, Figure& beaten)
{
    if (beaten.getType() != 6) beaten.makeEmpty();

    std::swap(beaten, moving);

    string temp = beaten.getPos();

    beaten.setPos(moving.getPos());

    moving.setPos(temp);//swap button coordinates
    if (beaten.getType() == 0) {
        kingPos[beaten.getSide()] = beaten.getPos();
    }
}