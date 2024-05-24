#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(400, 550), "Arkanoid");

	RectangleShape line(Vector2f(400, 1));
	line.setFillColor(Color::Black);
	line.setPosition(0, 50);

	RectangleShape block[24];
	for (int j = 0; j < 3; j++)
		for (int i = 0; i < 8; i++) {
			block[j * 8 + i].setSize(Vector2f(50, 50));
			block[j * 8 + i].setFillColor(Color::Blue);
			block[j * 8 + i].setPosition(50 * i, 50 * (j + 1));
		}

	RectangleShape man(Vector2f(100, 10));
	man.setFillColor(Color::Black);
	man.setPosition(150, 530);

	CircleShape ball(10.f);
	ball.setFillColor(Color::Red);
	ball.setPosition(190, 510);
	int p = 0, kx = -1, ky = -1, q = 0, l = 2;

	CircleShape life[3];
	for (int i = 0; i < 3; i++) {
		life[i].setRadius(20.f);
		life[i].setFillColor(Color::Red);
		life[i].setPosition(10 + 45 * i, 5);
	}

	double spin = 0.2;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		Vector2f m = man.getPosition();

		if (q != 24) {
			if (Keyboard::isKeyPressed(Keyboard::D))
				if (m.x < 300) {
					man.move(spin, 0);

					if (p == 0)
						ball.move(spin, 0);
				}
			if (Keyboard::isKeyPressed(Keyboard::A))
				if (m.x > 0) {
					man.move(-spin, 0);

					if (p == 0)
						ball.move(-spin, 0);
				}

			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
					p = 1;
		}

		else if (q == 24)
			p = 0;

		if (p == 1) {
			ball.move(spin * kx, spin * ky);

			Vector2f b = ball.getPosition();

			if (b.x < 0 || b.x > 380)
				kx = -kx;
			if (b.y < 50)
				ky = -ky;

			if (b.x >= m.x - 15 && b.x <= m.x + 100 && b.y == 510)
				ky = -ky;

			if (b.y > 560) {
				p = 0;
				ky = -ky;

				man.setPosition(150, 530);
				ball.setPosition(190, 510);

				life[l].setFillColor(Color::White);
				l--;
			}

			if (l == -1) {
				q = 24;

				ball.setFillColor(Color::White);
				man.setFillColor(Color::White);
			}

			Vector2f bl[24];
			for (int i = 0; i < 24; i++) {
				bl[i] = block[i].getPosition();

				if (b.x >= bl[i].x && b.x <= bl[i].x + 50)
					if (b.y < bl[i].y + 50 && b.y > bl[i].y) {
						ky = -ky;

						block[i].setPosition(500, 500);

						q++;
					}
			}
		}

		window.clear(Color::White);
		window.draw(line);
		for (int i = 0; i < 24; i++)
			window.draw(block[i]);
		window.draw(man);
		window.draw(ball);
		for (int i = 0; i < 3; i++)
			window.draw(life[i]);
		window.display();
	}

	return 0;
}