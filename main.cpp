#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int main()
{
	RenderWindow app(VideoMode(400, 400), "TicTacToe");

	Texture t1, t2, t3;
	t1.loadFromFile("image/x.png");



	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed) app.close();
		}
		app.clear();
		app.display();
	}
}