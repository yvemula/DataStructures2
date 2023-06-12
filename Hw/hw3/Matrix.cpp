#include "Matrix.h"

// Overloaded assignment operator for Matrix objects
Matrix& Matrix::operator=(const Matrix& mtrx) {
	// Check if the objects being compared are not the same
	if (*this != mtrx) {
		// If not, destroy the current object
		destroy();
	}
	// Copy the content of mtrx to this object
	copy(mtrx);
	return *this;
}
// Get a specific value in the matrix at the given row and column
bool Matrix::get(const unsigned int& r, const unsigned int& c, double& val) const {
	// Check if the given row and column are valid
	if (valid_pos(r, c)) {
		// If valid, set val to the value at the given position
		val = data_[r][c];
		return true;
	}
	else {
		// If not valid, return false
		return false;
	}
}
// Get the data in a specific row
double* Matrix::get_row(const unsigned int& row_index) const {
	// Check if the given row index is valid
	if (row_index < 0 || row_index >= rows) {
		return nullptr;
	}
	double* row_data = new double[cols];
	// Copy the values in the given row to row_data
	for (unsigned int i = 0; i < cols; ++i) {
		row_data[i] = data_[row_index][i];
	}
	return row_data;
}
// Get the data in a specific column
double* Matrix::get_column(const unsigned int& column) const {
	double* column_ptr = nullptr;
	// Check if the given column is valid
	if (valid_col(column)) {
		column_ptr = new double[rows];
		// Copy the values in the given column to column_ptr
		for (unsigned int i = 0; i < rows; ++i) {
			column_ptr[i] = *(data_[i] + column);
		}
	}
	return column_ptr;
}
bool Matrix::operator== (const Matrix& m2) const {
	// Flag to keep track of equality between matrices
	bool isEqual = true;
	// Check if the number of rows and columns in both matrices are the same
	if (!same_dim(m2.num_rows(), m2.num_cols())) {
		isEqual = false;
	}
	else {
		// Loop through all rows and columns
		for (unsigned int i = 0; i < rows; ++i) {
			for (unsigned int j = 0; j < cols; ++j) {
				// Get the value from m2 at the current row and column
				double val;
				m2.get(i, j, val);
				// Compare the values from m2 and this matrix
				if (val != data_[i][j]) {
					isEqual = false;
					break;
				}
			}
			// If a difference is found, break out of the loops
			if (!isEqual) break;
		}
	}
	return isEqual;
}
bool Matrix::operator!= (const Matrix& matri) const {
	// checks if the current matrix object is not equal to the input matrix object
	if (*this == matri) return false;
	// returns false if they are equal, else returns true
	else return true;
}
bool Matrix::set(const unsigned int& rowIndex, const unsigned int& colIndex, double value) {
	// updates the value of a particular cell in the matrix
	bool success = false;
	if (valid_pos(rowIndex, colIndex)) {
		// checks if the row and column indices are valid
		data_[rowIndex][colIndex] = value;
		// updates the value if the indices are valid
		success = true;
	}
	return success;
}
void Matrix::multiply_by_coefficient(const double& factor) {
	// multiplies every cell in the matrix by the factor
	for (unsigned int i = 0; i < rows; ++i) {
		for (unsigned int j = 0; j < cols; ++j)
			data_[i][j] *= factor;
	}
}
bool Matrix::swap_row(const unsigned int& source, const unsigned int& target) {
	// swaps the values of two rows in the matrix
	bool success = false;
	if (valid_row(source) && valid_row(target)) {
		// checks if the source and target row indices are valid
		double* temp = new double[cols];
		// creates a temporary array to store the values of the target row
		for (unsigned int i = 0; i < cols; ++i) {
			temp[i] = data_[target][i];
			data_[target][i] = data_[source][i];
		}
		// updates the target row with the values of the source row
		for (unsigned int i = 0; i < cols; ++i) {
			data_[source][i] = temp[i];
		}
		// updates the source row with the values of the target row
		delete[] temp;
		success = true;
	}
	return success;
}
// Transposes the matrix
void Matrix::transpose() {
	double** flippedData = nullptr;
	// Check if the data_ is not NULL
	if (data_ != NULL) {
		// Allocate memory for the transposed data_
		flippedData = new double* [cols];
		// Transpose the data_
		for (unsigned int i = 0; i < cols; ++i) {
			flippedData[i] = new double[rows];
			for (unsigned int j = 0; j < rows; ++j) {
				flippedData[i][j] = data_[j][i];
			}
		}
		// Deallocate memory of the old data_
		destroy();
	}
	// Assign the new transposed data_ to data_
	data_ = flippedData;
}
// Adds two matrices
bool Matrix::add(const Matrix& m) {
	bool success = false;
	// Check if the matrices have the same dimension
	if (same_dim(m.num_rows(), m.num_cols())) {
		success = true;
		unsigned int i = 0;
		// Add each element of the matrices
		while (i < rows && success) {
			unsigned int j = 0;
			while (j < cols && success) {
				double val;
				if (m.get(i, j, val)) {
					data_[i][j] += val;
				}
				else {
					success = false;
					break;
				}
				j++;
			}
			i++;
		}
	}
	return success;
}
// Subtracts two matrices
bool Matrix::subtract(const Matrix& m2) {
	// Create a copy of m2 with its values negated
	Matrix tempMatrix(m2);
	tempMatrix.multiply_by_coefficient(-1);
	// Add the negated matrix to the current matrix
	return add(tempMatrix);
}
// This function splits the current matrix into 4 quarters and returns an array of 4 matrices.
Matrix* Matrix::quarter() {
	// Allocate memory for the array of 4 matrices
	Matrix* m_ptr = new Matrix[4]; 
	// Calculate the number of rows and columns for each quarter matrix
	unsigned int split_rows = rows / 2;
	unsigned int split_cols = cols / 2;
	// Loop through the 4 matrices
	for (int k = 0; k < 4; ++k) {
		// Determine the starting row and column for each quarter matrix
		unsigned int row_start = k / 2 * split_rows;
		unsigned int col_start = (k % 2) * split_cols;
		// Create the quarter matrix with the calculated number of rows and columns
		m_ptr[k].create(split_rows + (rows % 2), split_cols + (cols % 2), 0);
		// Fill the quarter matrix with the appropriate values from the current matrix
		for (unsigned int i = 0; i < m_ptr[k].rows; ++i) {
			for (unsigned int j = 0; j < m_ptr[k].cols; ++j) {
				m_ptr[k].set(i, j, data_[i + row_start][j + col_start]);
			}
		}
	}
	// Return the array of 4 matrices
	return m_ptr;
}
// Function to create a matrix with specified number of rows and columns, and initialize with a default value
void Matrix::create(const unsigned int& numRows,
	const unsigned int& numCols,
	const double& defaultValue) {
	// Check if number of rows or columns is 0
	if (numRows == 0 || numCols == 0) {
		rows = 0;
		cols = 0;
		data_ = nullptr;
		return;
	}
	// Set number of rows and columns
	rows = numRows;
	cols = numCols;
	// Allocate memory for data
	data_ = new double* [rows];
	// Initialize data with default value
	for (unsigned int i = 0; i < rows; ++i) {
		data_[i] = new double[cols];
		std::fill(data_[i], data_[i] + cols, defaultValue);
	}
}
// Function to copy data from source matrix to current matrix
void Matrix::copy(const Matrix& src) {
	// Create a new matrix with same number of rows and columns as source matrix
	create(src.num_rows(), src.num_cols(), 0);
	// Copy data from source matrix to current matrix
	unsigned int i = 0;
	while (i < num_rows()) {
		unsigned int j = 0;
		while (j < num_cols()) {
			src.get(i, j, data_[i][j]);
			j++;
		}
		i++;
	}
}
// Function to destroy matrix and release memory
void Matrix::destroy() {
	// Delete data stored in each row
	unsigned int i = 0;
	while (data_ != NULL && i < rows) {
		delete[] data_[i];
		++i;
	}
	// Delete data pointer
	if (data_ != NULL) {
		delete[] data_;
		data_ = NULL;
	}
	// Reset number of rows and columns
	rows = 0;
	cols = 0;
}
// Overloading the stream operator to output the contents of a Matrix object
std::ostream& operator<< (std::ostream& out, const Matrix& mat) {
	// Get number of rows and columns in the Matrix object
	unsigned int numRows = mat.num_rows();
	unsigned int numCols = mat.num_cols();
	// Output the size of the Matrix
	out << std::endl << numRows << " x " << numCols << " matrix:" << std::endl << "[ ";
	// Initialize variables to keep track of current row and column being outputted
	int currentRow = 0;
	int currentCol = 0;
	// Loop through each row in the Matrix
	while (currentRow < numRows) {
		// Break if there are no columns
		if (numCols == 0) break;
		// Output a newline before each row, except for the first row
		if (currentRow != 0) out << " ";
		// Loop through each column in the current row
		while (currentCol < numCols) {
			// Get the value at the current row and column in the Matrix object
			double value;
			mat.get(currentRow, currentCol, value);
			// Output the value
			out << value << " ";
			// Move to the next column
			currentCol++;
		}
		// Output a newline after each row, except for the last row
		if (currentRow != numRows - 1) out << std::endl;
		// Move to the next row
		currentRow++;
		// Reset the column counter
		currentCol = 0;
	}
	// Close the matrix bracket
	out << "]" << std::endl;
	// Return the output stream
	return out;
}
// Extra credit
void Matrix::resize(const unsigned int& new_num_rows,
	const unsigned int& new_num_cols,
	const double& default_value) {
	// Create a new 2D array with the new dimensions
	double** temp_data = nullptr;
	if (new_num_rows != 0 && new_num_cols != 0) {
		temp_data = new double* [new_num_rows];
		for (unsigned int i = 0; i < new_num_rows; ++i) {
			temp_data[i] = new double[new_num_cols];
			for (unsigned int j = 0; j < new_num_cols; ++j) {
				// If the element is within the range of the original array, copy the value
				if (i < rows && j < cols) {
					temp_data[i][j] = data_[i][j];
				}
				// Otherwise, fill with the default value
				else {
					temp_data[i][j] = default_value;
				}
			}
		}
	}
	// Deallocate the original array
	if (data_ != nullptr) {
		for (unsigned int i = 0; i < rows; ++i) {
			delete[] data_[i];
		}
		delete[] data_;
	}
	// Assign the new array to the data_ member variable
	data_ = temp_data;
	rows = new_num_rows;
	cols = new_num_cols;
}//end of my cpp implementation