#include <iostream>
#include "Screen.hpp"
#include "Preview.hpp"

using namespace std;

int main()
{
	Screen s;
	Preview p(s);

	int t = 0;
	while(true) {
		t++;

		for(int x = 0; x < Screen::width; x++)
			for(int y = 0; y < Screen::height; y++)
				s.setPixel((x+y+t/4) % 10 >= 5, x, y);

		s.swapBuffers();
		p.update();
	}


	return 0;
}

