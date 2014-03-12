#ifndef JOSHOENGINE_VECTOR2_H_
#define JOSHOENGINE_VECTOR2_H_

#include "JoshoEngine.h"
#include "Matrix.h"

#include <iostream>

namespace JoshoEngine
{
	struct JOSHO_API Vector2
	{
		// Instantiates a vector with both components set to whatever scalar is.
		// scalar is the value each component is initialized to.
		Vector2(float scalar = 0.0f);

		// Instantiates a vector with both x and y set to their respective parameters.
		Vector2(float x, float y);

		// Copy constructor.
		Vector2(const Vector2& other);

		// Destructor.
		~Vector2();

		// Assignment operator.
		Vector2& operator=(const Vector2& vec);

		// Arithmetic operators.
		Vector2& operator+=(const Vector2& vec);
		Vector2& operator+=(float amount);
		Vector2& operator-=(const Vector2& vec);
		Vector2& operator-=(float amount);
		Vector2& operator*=(float scale);
		Vector2& operator/=(float scale);

		// Comparison operators
		bool operator<(const Vector2& r) const;
		bool operator>(const Vector2& r) const;
		bool operator<=(const Vector2& r) const;
		bool operator>=(const Vector2& r) const;
		bool operator==(const Vector2& r) const;
		bool operator!=(const Vector2& r) const;

		bool operator>=(float mag) const;
		bool operator<(float mag) const;
		bool operator>(float mag) const;
		bool operator<=(float mag) const;

		// Negation operator.
		Vector2 operator-() const;

		//Calculates the vector's magnitude, squared.
		float magnitudeSquared() const;

		// Calculates the vector's magnitude.
		float magnitude() const;

		// Calculates the angle between two vectors.
		float angle(const Vector2& other) const;

		// Calculates the angle between two normalized vectors.
		float angleNormalized(const Vector2& other) const;

		// Returns a unit vector in the same direction as the current one.
		const Vector2 normalize() const;

		// Converts this vector to a unit vector, preserving direction.
		Vector2& normalizeInPlace();

		/*! Project the vector along another.
		@param target Vector to project onto.
		@return Projected vector.
		*/
		Vector2 project(const Vector2& target) const;

		/*! Project the vector along another, in-place.
		@param target Vector to project onto.
		@return Reference to modified vector.
		*/
		Vector2& projectInPlace(const Vector2& target);

		/*! Reflects the vector over `normal`.
		@param normal The vector over which to reflect.
		*/
		Vector2 reflect(Vector2 normal) const;

		/*! Reflects the vector over `normal` in-place.
		@param normal The vector over which to reflect.
		*/
		Vector2& reflectInPlace(Vector2 normal);

		/*! Rotate the vector around the origin
		@param radians Angle in radians to rotate.
		@return New rotated vector.
		*/
		Vector2 rotate(float radians) const;

		/*! Rotate the vector around the origin, in-place.
		@param radians Angle in radians to rotate.
		@return Reference to modified vector.
		*/
		Vector2& rotateInPlace(float radians);

		/*!
		Calculates the distance between the vectors, squared.
		@note Faster than `distance`.
		*/
		float distanceSquared(const Vector2& other) const;

		/*! Calculates the distance between the vectors. */
		float distance(const Vector2& other) const;

		// Calculates the length of the vector.
		float length() const;
		
		// Calculates the length of the vector and squares it.
		float lengthSquared() const;

		/*! Calculates the dot product of the vectors. */
		float dot(const Vector2& other) const;

		/*! Transforms the vector using a transformation matrix.
		@param mat Transformation matrix to apply to the vector.
		@return Newly transformed vector.
		*/
		Vector2 transform(const Matrix& mat) const;

		/*! Transforms the vector in-place using a transformation matrix.
		@param mat Transformation matrix to apply to the vector.
		@return Reference to the modified vector.
		*/
		Vector2& transformInPlace(const Matrix& mat);

		float x;
		float y;
	};

	// Arithmetic operators.
	const JOSHO_API Vector2 operator+(const Vector2& vec, const Vector2& other);
	const JOSHO_API Vector2 operator+(const Vector2& vec, float amount);
	const JOSHO_API Vector2 operator+(float amount, const Vector2& vec);
	const JOSHO_API Vector2 operator-(const Vector2& vec, const Vector2& other);
	const JOSHO_API Vector2 operator-(const Vector2& vec, float amount);
	const JOSHO_API Vector2 operator-(float amount, const Vector2& vec);
	const JOSHO_API Vector2 operator*(const Vector2& a, const Vector2& b);
	const JOSHO_API Vector2 operator*(const Vector2& vec, float scale);
	const JOSHO_API Vector2 operator*(float scale, const Vector2& vec);
	const JOSHO_API Vector2 operator/(const Vector2& a, const Vector2& b);
	const JOSHO_API Vector2 operator/(const Vector2& vec, float scale);

	// Prints the vector the form of (x, y).
	JOSHO_API std::ostream& operator<<(std::ostream& stream, const Vector2& vec);
}

#endif
