#include "stdafx.h"

#include "JoshoEngine.h"
#include "Vector2.h"
#include "Matrix.h"

#include <string>
#include <iostream>
#include <sstream>

using namespace JoshoEngine;

Vector2::Vector2(float scalar)
: x(scalar), y(scalar)
{
}

Vector2::Vector2(float x, float y)
: x(x), y(y)
{
}

Vector2::Vector2(const Vector2& other)
: x(other.x), y(other.y)
{
}

Vector2::~Vector2()
{
}

Vector2& Vector2::operator=(const Vector2& other)
{
	x = other.x;
	y = other.y;
	return *this;
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vector2& Vector2::operator+=(float amount)
{
	x += amount;
	x += amount;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2& Vector2::operator-=(float amount)
{
	x -= amount;
	y -= amount;
	return *this;
}

Vector2& Vector2::operator*=(float scale)
{
	x *= scale;
	y *= scale;
	return *this;
}

Vector2& Vector2::operator/=(float scale)
{
	x /= scale;
	y /= scale;
	return *this;
}

Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

float Vector2::magnitudeSquared() const
{
	return x*x + y*y;
}

float Vector2::magnitude() const
{
	return sqrt(x*x + y*y);
}

float Vector2::angle(const Vector2& other) const
{
	return acosf(dot(other) / (magnitude() * other.magnitude()));
}

float Vector2::angleNormalized(const Vector2& other) const
{
	return acosf(dot(other));
}

const Vector2 Vector2::normalize() const
{
	Vector2 ret;
	float mag = magnitude();

	if (mag != 0.0f) {
		ret.x = x / mag;
		ret.y = y / mag;
	}

	return ret;
}

Vector2& Vector2::normalizeInPlace()
{
	float mag = magnitude();

	if (mag != 0.0f) {
		x /= mag;
		y /= mag;
	}

	return *this;
}

Vector2 Vector2::project(const Vector2& target) const
{
	return target * (dot(target) / target.dot(target));
}

Vector2& Vector2::projectInPlace(const Vector2& target)
{
	return *this = project(target);
}

Vector2 Vector2::reflect(Vector2 normal) const
{
	normal.normalizeInPlace();
	return *this - 2.0f * normal * dot(normal);
}

Vector2& Vector2::reflectInPlace(Vector2 normal)
{
	normal.normalizeInPlace();
	return *this -= 2.0f * normal * dot(normal);
}

Vector2 Vector2::rotate(float radians) const
{
	return Vector2(x * cosf(radians) - y * sinf(radians),
		y * cosf(radians) + x * sinf(radians));
}

Vector2& Vector2::rotateInPlace(float radians)
{
	float tmp = x * cosf(radians) - y * sinf(radians);
	y = y * cosf(radians) + x * sinf(radians);
	x = tmp;
	return *this;
}

float Vector2::distanceSquared(const Vector2& other) const
{
	float dx = other.x - x;
	float dy = other.y - y;
	return dx*dx + dy*dy;
}

float Vector2::distance(const Vector2& other) const
{
	float dx = other.x - x;
	float dy = other.y - y;
	return sqrt(dx*dx + dy*dy);
}

float Vector2::length() const
{
	return (sqrtf((this->x * this->x) + (this->y * this->y)));
}

float Vector2::lengthSquared() const
{
	return (this->x * this->x) + (this->y * this->y);
}

float Vector2::dot(const Vector2& other) const
{
	return x * other.x + y * other.y;
}

Vector2 Vector2::transform(const JoshoEngine::Matrix& mat) const
{
	return Vector2(x * mat.m11 + y * mat.m21 + mat.m41,
		x * mat.m12 + y * mat.m22 + mat.m42);
}

Vector2& Vector2::transformInPlace(const JoshoEngine::Matrix& mat)
{
	float tmp = x * mat.m11 + y * mat.m21 + mat.m41;
	y = x * mat.m12 + y * mat.m22 + mat.m42;
	x = tmp;
	return *this;
}

bool Vector2::operator<(const Vector2& r) const
{
	return this->magnitudeSquared() < r.magnitudeSquared();
}

bool Vector2::operator>(const Vector2& r) const
{
	return this->magnitudeSquared() > r.magnitudeSquared();
}

bool Vector2::operator<=(const Vector2& r) const
{
	return this->magnitudeSquared() <= r.magnitudeSquared();
}

bool Vector2::operator>=(const Vector2& r) const
{
	return this->magnitudeSquared() >= r.magnitudeSquared();
}

bool Vector2::operator==(const Vector2& r) const
{
	return this->x == r.x && this->y == r.y;
}

bool Vector2::operator!=(const Vector2& r) const
{
	return this->x != r.x || this->y != r.y;
}

// Left side
bool Vector2::operator<(float mag) const
{
	return this->magnitude() < mag;
}

bool Vector2::operator>(float mag) const
{
	return this->magnitude() > mag;
}

bool Vector2::operator<=(float mag) const
{
	return this->magnitude() <= mag;
}

bool Vector2::operator>=(float mag) const
{
	return this->magnitude() >= mag;
}

const Vector2 JoshoEngine::operator+(const Vector2& vec, const Vector2& other)
{
	return Vector2(vec.x + other.x, vec.y + other.y);
}

const Vector2 JoshoEngine::operator+(const Vector2& vec, float amount)
{
	return Vector2(vec.x + amount, vec.y + amount);
}

const Vector2 JoshoEngine::operator+(float amount, const Vector2& vec)
{
	return Vector2(vec.x + amount, vec.y + amount);
}

const Vector2 JoshoEngine::operator-(const Vector2& vec, const Vector2& other)
{
	return Vector2(vec.x - other.x, vec.y - other.y);
}

const Vector2 JoshoEngine::operator-(const Vector2& vec, float amount)
{
	return Vector2(vec.x - amount, vec.y - amount);
}

const Vector2 JoshoEngine::operator-(float amount, const Vector2& vec)
{
	return Vector2(amount - vec.x, amount - vec.y);
}

const Vector2 JoshoEngine::operator*(const Vector2& a, const Vector2& b)
{
	return a.dot(b);
}

const Vector2 JoshoEngine::operator*(const Vector2& vec, float scale)
{
	return Vector2(vec.x * scale, vec.y * scale);
}

const Vector2 JoshoEngine::operator*(float scale, const Vector2& vec)
{
	return Vector2(vec.x * scale, vec.y * scale);
}

const Vector2 JoshoEngine::operator/(const Vector2& a, const Vector2& b)
{
	return Vector2(a.x / b.x, a.y / b.y);
}

const Vector2 JoshoEngine::operator/(const Vector2& vec, float scale)
{
	return Vector2(vec.x / scale, vec.y / scale);
}

std::ostream& JoshoEngine::operator<<(std::ostream& stream, const Vector2& vec)
{
	std::stringstream ss;
	ss << "(" << vec.x << ", " << vec.y << ")";
	stream << ss.str();
	return stream;
}
