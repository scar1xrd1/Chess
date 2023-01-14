#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Field.h"
#include "Figure.h"

using namespace sf;
using namespace std;

int main() {

    RenderWindow app(VideoMode(400, 400), "chess");

    Texture t1, t2, t3;
    t1.loadFromFile("images/board.png");

    t2.loadFromFile("images/figures.png");

    t3.loadFromFile("images/square.png");

    Sprite figure(t2);

    Sprite background(t1);
    background.setTextureRect(IntRect(100, 100, 900, 900));
    background.scale(0.5f, 0.5f);

    Sprite square(t3);
    Field field;
    field.CalculateMoves("e2");

    while (app.isOpen()) {

        Event e;
        while (app.pollEvent(e)) {

            if (e.type == Event::Closed)
                app.close();
            else if (e.type == Event::MouseButtonPressed) {

                if (e.key.code == Mouse::Left) {

                    if (field.getPawnUpgrade() == "none") {
                        cout << Mouse::getPosition(app).x << endl;
                        field.mouseClick(Mouse::getPosition(app));
                    }
                    else {
                        int mouseX = Mouse::getPosition(app).x - 145;
                        int mouseY = Mouse::getPosition(app).y - 145;

                        cout << (50 < mouseX && mouseX < 60) << endl;
                        cout << (50 < mouseY && mouseY < 60) << endl;

                        Figure* curr = &field.getFigure(field.getPawnUpgrade());
                        if (!(50 < mouseX && mouseX < 60) && !(50 < mouseY && mouseY < 60)
                            && (0 < mouseX && mouseX < 110) && (0 < mouseY && mouseY < 110)) { // If borders are not affected
                            curr->pawnUpgrade(mouseY / 60 * 2 + mouseX / 60 + 1); // Set the new figure type
                            cout << "Figure changed" << endl;
                            field.setPawnUpgrade("none");
                        }
                    }
                }
            }

        }
        app.draw(background);
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++) {
                Figure f = field.getFigure(Vector2i(i, j));
                if (f.getType() != 6) {
                    figure.setTextureRect(IntRect(50 * f.getType(), f.getSide() * 50, 50, 50));
                    figure.setPosition(j * 50, i * 50);
                    app.draw(figure);
                }
            }
        if (field.getPawnUpgrade() != "none") {// Selecting a square to draw
            square.setPosition(135, 135);
            app.draw(square);
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    figure.setTextureRect(IntRect(50 * (i * 2 + 1 + j), 50 * field.getFigure(field.getPawnUpgrade()).getSide(), 50, 50));
                    figure.setPosition(145 + j * 60, 145 + i * 60);
                    app.draw(figure);
                }
            }
        }
        app.display();
    }
}