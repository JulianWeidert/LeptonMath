#pragma once

#include <ostream>

#include <initializer_list>
#include <concepts>
#include <cmath>

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

	template<typename TScalar, typename TVec, size_t size> requires std::is_arithmetic_v<TScalar>
	Vector<TVec, size> operator*(const TScalar& s, const  Vector<TVec, size>& v);

	template<typename T, size_t size>
	Vector<T, size> cross(const  Vector<T, size>& a, const  Vector<T, size>& b);

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

		explicit Vector(const Vector<T, size - 1>& vec,const T& val) requires (size > 0);
		explicit Vector(const T& val, const Vector<T, size - 1>& vec) requires (size > 0);

		explicit Vector(const Vector<T, size - 2>& vec, const T& val1, const T& val2) requires (size > 1);
		explicit Vector(const T& val1, const T& val2, const Vector<T, size - 2>& vec) requires (size > 1);

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

		T getLength() const;

		Vector<T, size> getNormalized() const;
		void normalize();
		

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
		template<typename TScalar, typename TVec, size_t size> requires std::is_arithmetic_v<TScalar>
		friend Vector<TVec, size> operator* <>(const TScalar& s, const  Vector<TVec, size>& v);

		template<typename T, size_t size>
		friend Vector<T, size> cross<>(const  Vector<T, size>& a, const  Vector<T, size>& b) requires (size == 3);

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

	template<typename T, size_t size> requires std::is_arithmetic_v<T>
	Vector<T, size>::Vector(const Vector<T, size - 1>& vec, const T& val) requires (size > 0) {
		for (int i = 0; i < size - 1; ++i) this->data[i] = vec[i];
		this->data[size - 1] = val;
	}

	template<typename T, size_t size> requires std::is_arithmetic_v<T>
	Vector<T, size>::Vector(const T& val, const Vector<T, size - 1>& vec) requires (size > 0) {
		this->data[0] = val;
		for (int i = 1; i < size; ++i) this->data[i] = vec[i - 1];
	}

	template<typename T, size_t size> requires std::is_arithmetic_v<T>
	Vector<T, size>::Vector(const Vector<T, size - 2>& vec, const T& val1, const T& val2) requires (size > 1) {
		for (int i = 0; i < size - 2; ++i) this->data[i] = vec[i];
		this->data[size - 2] = val1;
		this->data[size - 1] = val2;
	}

	template<typename T, size_t size> requires std::is_arithmetic_v<T>
	Vector<T, size>::Vector(const T& val1, const T& val2, const Vector<T, size - 2>& vec) requires (size > 1) {
		this->data[0] = val1;
		this->data[1] = val2;
		for (int i = 2; i < size; ++i) this->data[i] = vec[i - 2];
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

	template<typename T, size_t size> requires std::is_arithmetic_v<T>
	T Vector<T, size>::getLength() const {
		T sum{};
		for (size_t i = 0; i < size; ++i) sum += this->data[i] * this->data[i];
		return static_cast<T>(std::sqrt(sum));
	}

	template<typename T, size_t size> requires std::is_arithmetic_v<T>
	Vector<T, size> Vector<T, size>::getNormalized() const {
		Vector<T, size> out{};

		double invLen = 1.0 / this->getLength();
		for (size_t i = 0; i < size; ++i) out.data[i] = this->data[i] * invLen;

		return out;
	}

	template<typename T, size_t size> requires std::is_arithmetic_v<T>
	void Vector<T, size>::normalize() {
		double invLen = 1.0/this->getLength();
		for (size_t i = 0; i < size; ++i) this->data[i] *= invLen;
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
	Vector<T, size> operator- (const Vector<T, size>& v1, const  Vector<T, size>& v2) {
		Vector<T, size> out{};

		for (size_t i = 0; i < size; ++i) {
			out.data[i] = v1.data[i] - v2.data[i];
		}

		return out;
	}

	// neg
	template<typename T, size_t size>
	Vector<T, size> operator- (const Vector<T, size>& v) {
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
	template<typename TScalar, typename TVec, size_t size> requires std::is_arithmetic_v<TScalar>
	Vector<TVec, size>  operator* (const TScalar& s, const  Vector<TVec, size>& v) {
		Vector<TVec, size> out{};

		for (size_t i = 0; i < size; ++i) {
			out.data[i] = static_cast<const TVec>(s) * v.data[i];
		}

		return out;
	}

	template<typename T, size_t size> 
	Vector<T, size> cross(const  Vector<T, size>& a, const  Vector<T, size>& b) requires (size == 3)  {
		Vector<T, size> out{};

		out.data[0] = a.data[1] * b.data[2] - a.data[2] * b.data[1];
		out.data[1] = a.data[2] * b.data[0] - a.data[0] * b.data[2];
		out.data[2] = a.data[0] * b.data[1] - a.data[1] * b.data[0];

		return out;
	}

}
