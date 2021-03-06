#pragma once

template <class T>
class Matrix
{
	T** _data;
	int _rows, _cols;
	void createData(int rows, int cols);
	void deleteData();
	void copyData(const T** src);

public:
	Matrix() : _data(0) { }
	Matrix(int rows, int cols = 0) { this->createData(rows, cols == 0 ? rows : cols); }
	Matrix(const Matrix& M)
	{
		this->createData(M._rows, M._cols);
		this->copyData(M._data);
	}
	~Matrix() { this->deleteData(); }
public:
	void Fill(const T& value);

	int GetRows() const { return _rows; }
	int GetColumns() const { return _cols; }

	T* operator[](int i) { return _data[i]; }
	T& operator()(int i, int j) { return _data[i][j]; }
public:
	class Iterator
	{
		int rowIndex, colIndex;
		Matrix<T>* container;
	public: 
		Iterator(Matrix& container, int i, int j) : rowIndex(i), colIndex(j)
		{
			this->container = &container;
		}		
		Iterator& operator++()
		{
			if (++colIndex == container->_cols)
			{
				colIndex = 0;
				rowIndex++;
			}
			return *this;
		}
		bool operator!=(const Iterator& it) { return rowIndex != it.rowIndex || colIndex != it.colIndex; }
		T& operator *() { return container->_data[rowIndex][colIndex]; }

		int Row() const { return rowIndex; }
		int Column() const { return colIndex; }
		void Offset(int row, int col)
		{
			rowIndex += row;
			colIndex += col;
		}
	};
	friend Iterator begin(Matrix& m) { return Iterator(m, 0, 0); }
	friend Iterator end(Matrix& m) { return Iterator(m, m._rows, 0); }
};

template <class T> void Matrix<T>::createData(int rows, int cols)
{
	_rows = rows;
	_cols = cols;
	_data = new T *[rows];
	for (int i = 0; i < rows; i++)
		_data[i] = new T[cols];
}
template <class T> void Matrix<T>::deleteData()
{
	if (_data)
	{
		for (int i = 0; i < _rows; i++)
			delete[] _data[i];
		delete[] _data;

		_data = 0;
	}
}

template <class T> void Matrix<T>::copyData(const T** src)
{
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			_data[i][j] = src[i][j];
}
template <class T> void Matrix<T>::Fill(const T& value)
{
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			_data[i][j] = value;
}

