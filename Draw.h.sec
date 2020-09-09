#pragma once

class CSize
{
public:
	int Width, Height;
public:
	CSize() { Width = Height = 0; }
	CSize(int width, int height) : Width(width), Height(height) { }
public:
	friend CSize operator+(const CSize& t, const CSize& s)
	{
		return CSize(t.Width + s.Width, t.Height + s.Height);
	}
	friend CSize& operator+=(CSize& t, const CSize& s)
	{
		t.Width += s.Width;
		t.Height += s.Height;
		return t;
	}
};
class CPoint
{
public:
	int X, Y;
public:
	CPoint() { X = Y = 0; }
	CPoint(int x, int y) : X(x), Y(y) { }
public:
	CPoint& Offset(int x, int y)
	{
		X += x; Y += y;
		return *this;
	}
	friend CPoint operator+(const CPoint& p, const CSize& s)
	{
		return CPoint(p.X + s.Width, p.Y + s.Height);
	}
	friend CPoint& operator+=(CPoint& p, const CSize& s)
	{
		p.X += s.Width;
		p.Y += s.Height;
		return p;
	}
};

class CRect
{
public:
	CPoint Location;
	CSize Size;
public:
	CRect() { }
	CRect(int x1, int y1, int x2, int y2)
		: Location(x1, y1)
		, Size(x2 - x1 + 1, y2 - y1 + 1)	{}
	CRect(const CPoint& p1, const CPoint& p2)
		: Location(p1)
		, Size(p2.X - p1.X + 1, p2.Y - p1.Y + 1)	{}
	CRect(const CPoint& topLeft, const CSize& size)
		: Location(topLeft)
		, Size(size)	{}
};
