#ifndef SCREEN_HPP
#define SCREEN_HPP


class Screen
{
	public:
		static const int width = 40;
		static const int height = 28;

		Screen();
		void swapBuffers();

		void setPixel(int p, int x, int y);
		int getPixel(int x, int y);

		void drawRect(int p, int x, int y, int w, int h);
		void fillRect(int p, int x, int y, int w, int h);
		void drawLine(int p, int x, int y, int x2, int y2);
		void drawCircle(int p, int x, int y, int r);
		void fillCircle(int p, int x, int y, int r);
		void drawOval(int p, int x, int y, int rx, int ry);
		void fillOval(int p, int x, int y, int rx, int ry);

	private:
		int fd;
		bool screen[width][height];
};

#endif // SCREEN_HPP
