#ifndef PREVIEW_HPP
#define PREVIEW_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Screen.hpp>

class Preview
{
	public:
		Preview(Screen& s);
		void update();

	private:
		Screen& s;
		sf::RenderWindow window;
};

#endif // PREVIEW_HPP
