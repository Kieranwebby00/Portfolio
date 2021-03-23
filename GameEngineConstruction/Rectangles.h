#pragma once
class Rectangle
{
	public:

		int m_left{ 0 }, m_right{ 0 }, m_top{ 0 }, m_bottom{ 0 };

		Rectangle(int left, int right, int top, int bottom) : m_left(left), m_right(right), m_top(top), m_bottom(bottom) {}

		void Translate(int dx, int dy)
		{
			m_left += dx;
			m_right += dx;
			m_top += dy;
			m_bottom += dy;
		};

		void ClipScreen(const Rectangle& screen)
		{
			if (m_left < screen.m_left) {
				m_left = screen.m_left;
			};

			if (m_right >= screen.m_right - 1) {
				m_right = screen.m_right - 1;
			};

			if (m_top < screen.m_top) {
				m_top = screen.m_top;
			};

			if (m_bottom >= screen.m_bottom - 1) {
				m_bottom = screen.m_bottom - 1;
			};
		};

		int width() const { return m_right - m_left; }
		int height() const { return m_bottom - m_top; }

};


