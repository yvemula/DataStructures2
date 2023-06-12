#pragma once
#ifndef __Matrix_h_
#define __Matrix_h_
#include <iostream>
class Matrix {
public:
	// Constructor
	Matrix(unsigned int r = 0,
		unsigned int c = 0,
		double f = 0) {
		create(r, c, f);
	}
	Matrix(const Matrix& matri) { copy(matri); }
	Matrix& operator=(const Matrix& m);
	~Matrix() { destroy(); }
	// Accessors
	bool get(const unsigned int& r,
		const unsigned int& c,
		double& val) const;
	const unsigned int& num_rows() const { return rows; };
	const unsigned int& num_cols() const { return cols; };
	double* get_row(const unsigned int& row) const;
	double* get_column(const unsigned int& col) const;
	// Modifier
	bool set(const unsigned int& row, const unsigned int& col, double value);
	// Member functions
	void transpose();
	bool add(const Matrix& matri );
	void multiply_by_coefficient(const double& coefficient);
	bool swap_row(const unsigned int& s, const unsigned int& t);
	void clear() { destroy(); }
	bool subtract(const Matrix& matri);
	Matrix* quarter();
	// Operators 
	bool operator== (const Matrix& m) const;
	bool operator!= (const Matrix& m) const;
	// Extra Credit
	void resize(const unsigned int& new_rows,
		const unsigned int& new_cols,
		const double& value);
private:
	unsigned int rows, cols;
	double** data_;
	void copy(const Matrix& matri);
	void destroy();
	bool valid_pos(const unsigned int& row,
		const unsigned int& col) const {
		return row < rows&& col <
			cols;
	}
	void create(const unsigned int& rows,
		const unsigned int& cols,
		const double& fill);
	bool same_dim(const unsigned int& row,
		const unsigned int& col) const {
		return row == rows && col ==
			cols;
	}
	bool valid_row(const unsigned int& row) const { return row < rows; }
	bool valid_col(const unsigned int& col) const { return col < cols; }
};
// Overloaded output operator
std::ostream& operator<< (std::ostream& out, const Matrix& m);
#endif


