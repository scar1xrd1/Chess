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
public:
    Figure board[8][8];

    Field();

    vector<string>& CalculateMoves(string pos);
    vector<string>& CalculateMoves(int i, int j);
};

