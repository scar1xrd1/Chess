
#include "Figure.h"

Figure::Figure() {}

void Figure::add(string type, int side, string pos) {
    this->side = side;
    this->position = pos;
    for (int i = 0; i < 7; i++) {
        if (types[i] == type) {
            this->type = i;
            break;
        }
    }
}
