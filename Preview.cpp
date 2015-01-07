#include "Preview.hpp"

const int pxsize = 16;
const int pxrad = 7;

Preview::Preview(Screen& s) : s(s), window(sf::VideoMode(Screen::width*pxsize, Screen::height*pxsize), "Preview") {
}

void Preview::update() {
	if(!window.isOpen())
		exit(0);

	sf::Event event;

	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			exit(0);
		if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			exit(0);
	}

	window.clear(sf::Color::Black);

	for(int x = 0; x < Screen::width; x++)
		for(int y = 0; y < Screen::height; y++) {
			sf::CircleShape circle(pxrad);
			circle.setPointCount(20);
			if(s.getPixel(x, y))
				circle.setFillColor(sf::Color(255, 0, 0));
			else
				circle.setFillColor(sf::Color(40, 40, 40));
			circle.setPosition(x*pxsize, y*pxsize);
			window.draw(circle);
		}
	window.display();
}
