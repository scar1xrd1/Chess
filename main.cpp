#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Field.h"
#include "Figure.h"

using namespace sf;
using namespace std;

int main() {
    
    RenderWindow app(VideoMode(400, 400), "chess");
    //app.setFramerateLimit(60);

    Texture t1, t2;
    t1.loadFromFile("images/board.png");

    t2.loadFromFile("images/figures.png");

    Sprite figure(t2);

    Sprite background(t1);
    background.setTextureRect(IntRect(100, 100, 900, 900));
    background.scale(0.5f, 0.5f);

    Field field;
    field.CalculateMoves("e2")[1];
    while (app.isOpen()) {
        //app.clear();
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();

        }
        app.draw(background);
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
            {
                Figure f = field.board[i][j];
                if (f.getType() != 6) {
                    figure.setTextureRect(IntRect(50 * f.getType(), f.getSide() * 50, 50, 50));
                    //figure.scale(0.5f, 0.5f);
                    //figure.setColor(Color(255, 255, 255, p.alpha));
                    figure.setPosition(j * 50, i * 50);
                    //gems.move(offset.x - ts, offset.y - ts);
                    //cout << i << j << endl;
                    app.draw(figure);
                }
                
            }

        app.display();
    }

        //app.display();
    
}