#pragma once
#include "Figure.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

class Field
{
public:
    Figure board[8][8];

    Field();
};

