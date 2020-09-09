#include <iostream>
using namespace std;

#include "Matrix.h"
#include "Draw.h"
#include "Screen.h"
class Cell
{
public:
	int Value;
public:
	Cell(int v = 0) : Value(v) { }
	int IsEmpty() const { return this->Value == 0; }
	friend ostream& operator<<(ostream& left, const Cell& cell)
	{
		if (cell.IsEmpty())
			return left << ' ';
		return left << (char)cell.Value;
	}
};
class CellCollection : public Matrix<Cell>
{
public:
	CellCollection(int rows, int cols): Matrix(rows, cols){}
	int GetAt(int row, int col) 
	{ 
		if (row < 0 || row >= this->GetRows() || col < 0 || col >= this->GetColumns())
			return 0;
		return (*this)(row, col).Value; 
	}
	int Calculate(int side, int row, int col, int dr, int dc);
};

int CellCollection::Calculate(int side, int row, int col, int dr, int dc)
{
	int r = row, c = col;
	int count = 0;
	int s = side < 0 ? -side : side;
	while (this->GetAt(r += dr, c += dc) == s)
		count++;
	if (side > 0)
		count += Calculate(-side, row, col, -dr, -dc);
	return count;
}
class Indicator
{
	int row, col;
	CSize bound;
	CPoint O;
	Cursor cursor;
	void printOut(char left, char right = ' ')
	{
		int x = O.X + col * 2 + 2;
		int y = O.Y + row + 1;
		cursor.MoveTo(x - 1, y);
		cout << left;
		cursor.MoveTo(x + 1, y);
		cout << right;
	}
public:
	int Side;
public:
	Indicator(const CSize& bound, const CPoint& org) : bound(bound), Side('x'), O(org)
	{
		row = bound.Height / 2;
		col = bound.Width / 2;

		cursor.Hide();
	}
	~Indicator() {}

	Indicator& operator+=(const CSize& s)
	{
		row += s.Height;
		col += s.Width;
		return *this;
	}
	void Hide() { printOut(' '); }
	void Show() 
	{ 
		printOut('[', ']');
		cout << char(8) << char(8);
	}
	void Move(int x, int y)
	{
		this->Hide();
		row = (row + y + bound.Height) % bound.Height;
		col = (col + x + bound.Width) % bound.Width;
		this->Show();
	}

	bool PutPiece(CellCollection& cells)
	{
		auto& c = cells(row, col);
		if (!c.IsEmpty())
			return false;
		c.Value = Side;
		cout << char(Side);
		CSize s[] = { CSize(1, 1), CSize(-1, 1), CSize(0, 1), CSize(1, 0) };
		for (auto x: s)
		{
			if (cells.Calculate(Side, row, col, x.Height, x.Width) >= 4)
				return true;
		}
		Side = (Side == 'x' ? 'o' : 'x');
		return false;
	}
};

class Board : public Rect
{
	CellCollection cells;
	Indicator indicator;
private:
	void DrawFrame(int left, int middle, int right)
	{
		cout << char(left);
		for (int i = 0; i < this->Size.width() - 1; i++)
			cout << char(middle);
		cout << char(right);
	}
public:
	Board(int rows, int cols);
	enum { None, MoveCursor, Signed, Win };
public:
	void Draw();
public:
	int GetAction()
	{
		if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
		{
			indicator.Move(-1, 0);
			return MoveCursor;
		}
		if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
		{
			indicator.Move(1, 0);
			return MoveCursor;
		}
		if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))
		{
			indicator.Move(0, -1);
			return MoveCursor;
		}
		if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
		{
			indicator.Move(0, 1);
			return MoveCursor;
		}
		if (GetAsyncKeyState(VK_SPACE))
		{
			if (indicator.PutPiece(cells))
				return Win;
		}
		return None;
	}
	char Start()
	{
		system("CLS");
		Draw();
		while (1)
		{
			Sleep(150);
			int a = GetAction();

			if (a == Win)
				break;
		}
		return char(indicator.Side);
	}
};
Board::Board(int rows, int cols)
	: Rect(CPoint(2, 1), CSize(2 * cols + 2, rows + 1))
	, cells(rows, cols)
	, indicator(CSize(cols, rows), Location)
{
	cells.Fill(0);
}

void Board::Draw()
{
	Cursor cursor;

	int x = TopLeft.X, y = TopLeft.Y;
	cursor.MoveTo(x, y);
	this->DrawFrame(201, 205, 187);
	for (int i = 0; i < this->Size.height() - 1; i++)
	{
		cursor.MoveTo(x, ++y);
		this->DrawFrame(186, 32, 186);
	}
	cursor.MoveTo(x, y + 1);
	this->DrawFrame(200, 205, 188);
	indicator.Show();
}

void main()
{
	while (1)
	{
		Board board(15, 25);
		char c = board.Start();

		Cursor cursor;
		cursor.MoveTo(board.Location.X, 0);
		cout << ' ' << c << " wined! Try again (Y/N)?";

		while (1)
		{
			Sleep(100);
			SHORT flag[] = {
				GetAsyncKeyState('Y'),
				GetAsyncKeyState('N')
			};

			if (flag[0]) break;
			if (flag[1]) return;
		}
	}
}
