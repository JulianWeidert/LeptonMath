#pragma once

#include <ostream>

#include <initializer_list>
#include <concepts>

#include <cassert>

namespace lm {

	// Forward declations that are not related to Vector

	template<typename T, size_t rows, size_t cols> requires std::is_arithmetic_v<T>
	class Matrix;

	// Forward declations for Vector

	template<typename T, size_t size> requires std::is_arithmetic_v<T>
	class Vector;

	template<typename T, size_t size>
	std::ostream& operator<<(std::ostream& s, const Vector<T, size>& vec);

	template<typename T, size_t size>
	Vector<T, size> operator+(const Vector<T, size>& v1, const  Vector<T, size>& v2);

	template<typename T, size_t size>
	Vector<T, size> operator-(const Vector<T, size>& v1, const  Vector<T, size>& v2);

	template<typename T, size_t size>
	Vector<T, size> operator-(const  Vector<T, size>& v);

	template<typename T, size_t size>
	T operator*(const Vector<T, size>& v1, const  Vector<T, size>& v2);

	template<typename T, size_t size>
	Vector<T, size> operator*(const T& s, const  Vector<T, size>& v);

	// Matrix Vector multipication
	template<typename T, size_t rows, size_t cols>
	Vector<T, rows> operator* (Matrix<T, rows, cols>& m, Vector<T, cols>& v);


	// Vector class

	template<typename T, size_t size> requires std::is_arithmetic_v<T>
	class Vector {
	private:
		T data[size];

	public:
		
		// Constructors

		Vector() = default;
		Vector(std::initializer_list<T> init);


		// Operators

		T& operator[](size_t index);
		const T& operator[](size_t index) const;

		T getX() const requires (size > 0);
		T getY() const requires (size > 1);
		T getZ() const requires (size > 2);
		T getW() const requires (size > 3);

		Vector<T, 2> getXY() const requires (size > 1);
		Vector<T, 3> getXYZ() const requires (size > 2);
		Vector<T, 4> getXYZW() const requires (size > 3);

		friend std::ostream& operator<< <>(std::ostream& s, const Vector<T, size>& vec);

		// add
		friend Vector<T, size> operator+ <>(const Vector<T, size>& v1, const  Vector<T, size>& v2);

		// sub
		friend Vector<T, size> operator- <>(const Vector<T, size>& v1, const  Vector<T, size>& v2);

		// neg
		friend Vector<T, size> operator- <>(const Vector<T, size>& v);

		// dot
		friend T operator* <>(const Vector<T, size>& v1, const  Vector<T, size>& v2);

		// scale
		friend Vector<T, size> operator* <>(const T& s, const  Vector<T, size>& v);

		// Matrix Vector Multipication
		template<typename T, size_t rows, size_t cols> 
		friend Vector<T, rows> operator* <>( Matrix<T, rows, cols>& m,  Vector<T, cols>& v);

	};

	// Common type defintions

	template<size_t size>
	using Vectorf = Vector<float, size>;

	template<size_t size>
	using Vectori = Vector<int, size>;

	using Vector2f = Vector<float, 2>;
	using Vector3f = Vector<float, 3>;
	using Vector4f = Vector<float, 4>;


	// Constructors

	template<typename T, size_t size> requires std::is_arithmetic_v<T>
	Vector<T, size>::Vector(std::initializer_list<T> init) {
		assert(init.size() == size);
		std::copy(init.begin(), init.end(), std::begin(data));
	}

	// Access operations

	template<typename T, size_t size> requires std::is_arithmetic_v<T>
	T& Vector<T, size>::operator[](size_t index) {
		assert(index < size && index >= 0);
		return data[index];
	}

	template<typename T, size_t size> requires std::is_arithmetic_v<T>
	const T& Vector<T, size>::operator[](size_t index) const {
		assert(index < size&& index >= 0);
		return data[index];
	}

	template<typename T, size_t size> requires std::is_arithmetic_v<T>
	T Vector<T, size>::getX() const requires (size > 0) {
		return data[0];
	}

	template<typename T, size_t size> requires std::is_arithmetic_v<T>
	T Vector<T, size>::getY() const requires (size > 1) {
		return data[1];
	}

	template<typename T, size_t size> requires std::is_arithmetic_v<T>
	T Vector<T, size>::getZ() const requires (size > 2) {
		return data[2];
	}


	template<typename T, size_t size> requires std::is_arithmetic_v<T>
	T Vector<T, size>::getW() const requires (size > 3) {
		return data[3];
	}


	template<typename T, size_t size> requires std::is_arithmetic_v<T>
	Vector<T, 2> Vector<T, size>::getXY() const requires (size > 1) {
		Vector<T, 2> out{};
		out[0] = this->data[0];
		out[1] = this->data[1];
		return out;
	}

	template<typename T, size_t size> requires std::is_arithmetic_v<T>
	Vector<T, 3> Vector<T, size>::getXYZ() const requires (size > 2) {
		Vector<T, 3> out{};
		out[0] = this->data[0];
		out[1] = this->data[1];
		out[2] = this->data[2];
		return out;
	}

	template<typename T, size_t size> requires std::is_arithmetic_v<T>
	Vector<T, 4> Vector<T, size>::getXYZW() const requires (size > 3) {
		Vector<T, 4> out{};
		out[0] = this->data[0];
		out[1] = this->data[1];
		out[2] = this->data[2];
		out[3] = this->data[3];
		return out;
	}


	// Other operations

	template<typename T, size_t size>
	std::ostream& operator<<(std::ostream& s, const Vector<T, size>& vec) {
		s << "[";
		if (size > 0) s << vec.data[0];
		for (size_t i = 1; i < size; ++i) {
			s << "," << vec.data[i];
		}
		s << "]";
		return s;
	}

	// add
	template<typename T, size_t size>
	Vector<T, size> operator+(const Vector<T, size>& v1, const  Vector<T, size>& v2) {
		Vector<T, size> out{};

		for (size_t i = 0; i < size; ++i) {
			out.data[i] = v1.data[i] + v2.data[i];
		}

		return out;
	}

	// sub
	template<typename T, size_t size>
	Vector<T, size> operator- <>(const Vector<T, size>& v1, const  Vector<T, size>& v2) {
		Vector<T, size> out{};

		for (size_t i = 0; i < size; ++i) {
			out.data[i] = v1.data[i] - v2.data[i];
		}

		return out;
	}

	// neg
	template<typename T, size_t size>
	Vector<T, size> operator- <>(const Vector<T, size>& v) {
		Vector<T, size> out{};

		for (size_t i = 0; i < size; ++i) {
			out.data[i] = -v.data[i];
		}

		return out;
	}

	// dot
	template<typename T, size_t size>
	T operator*(const Vector<T, size>& v1, const  Vector<T, size>& v2) {
		T out = T();

		for (size_t i = 0; i < size; ++i) {
			out += v1.data[i] * v2.data[i];
		}

		return out;
	}

	// scale
	template<typename T, size_t size>
	Vector<T, size>  operator* <>(const T& s, const  Vector<T, size>& v) {
		Vector<T, size> out{};

		for (size_t i = 0; i < size; ++i) {
			out.data[i] = s * v.data[i];
		}

		return out;
	}


}
