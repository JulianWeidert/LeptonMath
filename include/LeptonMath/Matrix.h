#pragma once

#include <ostream>

#include <span>
#include <initializer_list>
#include <concepts>

#include "Vector.h"

namespace lm {

	// Forward declarations that are not related to Matrix

	template<typename T, size_t size> requires std::is_arithmetic_v<T>
	class Vector;

	// Forwaed declarations for Matrix

	template<typename T, size_t rows, size_t cols> requires std::is_arithmetic_v<T>
	class Matrix;

	template<typename T, size_t rows, size_t cols>
	std::ostream& operator<<(std::ostream& s, const Matrix<T, rows, cols>& mat);

	template<typename T, size_t m, size_t n, size_t k>
	Matrix<T, m, k> operator*(const Matrix<T, m, n>& left, const  Matrix<T, n, k>& right);

	template<typename T, size_t rows, size_t cols>
	Vector<T, rows> operator*(Matrix<T, rows, cols>& m, Vector<T, cols>& v);

	// Matrix Row

	template<typename T, size_t size>
	class MatrixRow {
	private:
		T* data;
	public:
		MatrixRow() = default;
		MatrixRow(T* data);

		T& operator[](size_t index);
		const T& operator[](size_t index) const;
	};

	template<typename T, size_t size>
	MatrixRow<T, size>::MatrixRow(T* data) : data(data) {};

	template<typename T, size_t size>
	T& MatrixRow<T, size>::operator[](size_t index) {
		assert(index < size && index >= 0);
		return data[index];
	}

	template<typename T, size_t size>
	const T& MatrixRow<T, size>::operator[](size_t index) const {
		assert(index < size&& index >= 0);
		return data[index];
	}

	// ConstMatrixRow

	template<typename T, size_t size>
	class ConstMatrixRow {
	private:
		const T* data;
	public:
		ConstMatrixRow() = default;
		ConstMatrixRow(const T* data);

		const T& operator[](size_t index) const;
	};

	template<typename T, size_t size>
	ConstMatrixRow<T, size>::ConstMatrixRow(const T* data) : data(data) {};

	template<typename T, size_t size>
	const T& ConstMatrixRow<T, size>::operator[](size_t index) const {
		assert(index < size&& index >= 0);
		return data[index];
	}

	// Matrix 

	template<typename T, size_t rows, size_t cols> requires std::is_arithmetic_v<T>
	class Matrix {
	private:
		T data[rows * cols];
	public:

		// Constructors

		Matrix() = default;
		Matrix(std::initializer_list<std::initializer_list<T>> init);


		// Operators

		MatrixRow<T, cols> operator[](size_t index);

		ConstMatrixRow<T, cols> operator[](size_t index) const;


		Matrix<T, rows, cols> getTransposed() const;
		void transpose();

		friend std::ostream& operator<< <>(std::ostream& s, const Matrix<T, rows, cols>& mat);

		template<typename T, size_t m, size_t n, size_t k>
		friend Matrix<T, m, k> operator* <>(const Matrix<T, m, n>& left,const Matrix<T, n, k>& right);

		// Matrix Vector multipication
		template<typename T, size_t rows, size_t cols>
		friend Vector<T, rows> operator* <>(Matrix<T, rows, cols>& m, Vector<T, cols>& v);

	};

	// Common type defintions

	using Matrix2x2f = Matrix<float, 2, 2>;
	using Matrix3x3f = Matrix<float, 3, 3>;
	using Matrix4x4f = Matrix<float, 4, 4>;

	// Constructors

	template<typename T, size_t rows, size_t cols> requires std::is_arithmetic_v<T>
	Matrix<T, rows, cols>::Matrix(std::initializer_list<std::initializer_list<T>> init) {
		assert(init.size() == rows);
		int i = 0;
		for (const auto& elem : init) {
			assert(elem.size() == cols);
			std::copy(elem.begin(), elem.end(), data + i * elem.size());
			i++;
		}
	}


	// Operators

	template<typename T, size_t rows, size_t cols> requires std::is_arithmetic_v<T>
	MatrixRow<T, cols> Matrix<T, rows, cols>::operator[](size_t index) {
		assert(index < rows && index >= 0);
		return MatrixRow<T, cols>(this->data + index * cols);
	}

	template<typename T, size_t rows, size_t cols> requires std::is_arithmetic_v<T>
	ConstMatrixRow<T, cols> Matrix<T, rows, cols>::operator[](size_t index) const {
		assert(index < rows&& index >= 0);
		return ConstMatrixRow<T, cols>(this->data + index * cols);
	}

	template<typename T, size_t rows, size_t cols> requires std::is_arithmetic_v<T>
	Matrix<T, rows, cols> Matrix<T, rows, cols>::getTransposed() const {
		Matrix<T, cols, rows> transposed{};

		for (size_t i = 0; i < rows; ++i) {
			for (size_t j = 0; j < cols; ++j) {
				transposed[j][i] = this->operator[](i)[j];
			}
		}

		return transposed;
	}

	template<typename T, size_t rows, size_t cols> requires std::is_arithmetic_v<T>
	void Matrix<T, rows, cols>::transpose() {
		*this = this->getTransposed();
	}

	template<typename T, size_t rows, size_t cols>
	std::ostream& operator<<(std::ostream& s, const Matrix<T, rows, cols>& mat) {
		
		for (size_t row = 0; row < rows; ++row) {
			s << "[";
			if (cols > 0) s << mat.data[row * cols];
			for (size_t col = 1; col < cols; ++col) {
				s << "," << mat.data[row * cols + col];
			}
			s << "]";
			if (row < rows - 1) s << "\n";
		}
		
		return s;
	}


	template<typename T, size_t m, size_t n, size_t k>
	Matrix<T, m, k> operator*(const Matrix<T, m, n>& left,const Matrix<T, n, k>& right) {
		Matrix<T, m, k> out{};

		for (size_t row = 0; row < m; ++row) {
			const auto& r1 = left[row];
			for (size_t i = 0; i < k; ++i) {
				const auto& r2 = right[i];
				const auto val = r1[i];
				for (size_t col = 0; col < n; ++col) out[row][col] += val * r2[col];
			}
		}

		return out;
	}

	// Matrix Vector multipication

	template<typename T, size_t rows, size_t cols>
	Vector<T, rows> operator* (Matrix<T, rows, cols>& m, Vector<T, cols>& v) {
		Vector<T, rows> out{};

		for (size_t row = 0; row < rows; ++row) {
			const auto& r = m[row];
			for (size_t col = 0; col < cols; ++col) out[row] += r[col] * v.data[col];
		}

		return out;
	}

}
