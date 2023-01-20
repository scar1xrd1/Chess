#include "Field.h"
#include "Figure.h"

//void Fieloperator=(vector<string>& first)
//{
//    vector<string> temp;
//    for (string n : first) {
//        temp.push_back(n);
//    }
//    return temp;
//}

int main() {
    RenderWindow app(VideoMode(400, 400), "chess");
    //app.setFramerateLimit(60);
    
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

    //field.calculateMoves("e1");

    while (app.isOpen()) {
        //app.clear();
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
            else if (e.type == Event::MouseButtonPressed) {
                if (e.key.code == Mouse::Left) {
                    if (field.getPawnUpgrade() == "none") {
                        cout << Mouse::getPosition(app).x << endl;
                        field.mouseClick(Mouse::getPosition(app));
                    }
                    else {
                        //cout << Mouse::getPosition(app).x;
                        int mouseX = Mouse::getPosition(app).x - 145;
                        int mouseY = Mouse::getPosition(app).y - 145;//mouse position within the choosing square
                        cout << mouseX << endl;
                        cout << mouseY << endl;
                        cout << (50 < mouseX && mouseX < 60) << endl;
                        cout << (50 < mouseY && mouseY < 60) << endl;
                        Figure* curr = &field.getFigure(field.getPawnUpgrade());
                        if (!(50 < mouseX && mouseX < 60) && !(50 < mouseY && mouseY < 60)
                            && (0 < mouseX && mouseX < 110) && (0 < mouseY && mouseY < 110)) {//if gaps aren`t hit
                            curr->pawnUpgrade(mouseY / 60 * 2 + mouseX / 60 + 1);//set new figure type
                            cout << "bebra" << endl;
                            field.setPawnUpgrade("none");
                        }
                    }
                }
            }

        }
        app.draw(background);
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
            {
                Figure f = field.getFigure(Vector2i(i, j));
                if (f.getType() != 6 && f.getType() != 7) {
                    figure.setTextureRect(IntRect(50 * f.getType(), f.getSide() * 50, 50, 50));
                    //figure.scale(0.5f, 0.5f);
                    //figure.setColor(Color(255, 255, 255, p.alpha));
                    figure.setPosition(j * 50, i * 50);
                    //gems.move(offset.x - ts, offset.y - ts);
                    //cout << i << j << endl;
                    app.draw(figure);
                }

            }
        if (field.getPawnUpgrade() != "none") {//choosing square drawing
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

    //app.display();

}