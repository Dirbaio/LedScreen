#include <iostream>
#include "Screen.hpp"
#include "Preview.hpp"

using namespace std;

const int w = Screen::width;
const int h = Screen::height;

int main()
{
	Screen s;
	Preview p(s);

	int t = 0;
	while(true) {
		t++;

		s.fillRect(1, 0, 0, w, h);
		s.drawLine(t%2, 0, 0, w, h);

		s.swapBuffers();
		p.update();
	}


	return 0;
}

