#pragma once

#include <ostream>

#include <span>
#include <initializer_list>
#include <concepts>


namespace lm {

	template<typename T, size_t rows, size_t cols> requires std::is_arithmetic_v<T>
	class Matrix;

	template<typename T, size_t rows, size_t cols>
	std::ostream& operator<<(std::ostream& s, const Matrix<T, rows, cols>& mat);

	template<typename T, size_t rows, size_t cols> requires std::is_arithmetic_v<T>
	class Matrix {
	private:
		T data[rows * cols];
	public:

		// Constructors

		Matrix() = default;
		Matrix(std::initializer_list<std::initializer_list<T>> init);


		// Operators

		std::span<T, cols> operator[](size_t index);

		friend std::ostream& operator<< <>(std::ostream& s, const Matrix<T, rows, cols>& mat);


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
	std::span<T, cols> Matrix<T, rows, cols>::operator[](size_t index) {
		assert(index < rows && index >= 0);
		return std::span<T, cols>(this->data + index * cols, cols);
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


}
