#include <DxLib.h>
#include <cmath>
#include <algorithm>
#include <utility>
#include "Geometry.h"





void
Vector2::operator*=(float scale) {
	x *= scale;
	y *= scale;
}

void Vector2::rotate90()
{
	std::swap(x,y);
	x -= x;
}

Vector2 Vector2::Rotated90() const
{
	return {-y,x};
}


Vector2
Vector2::operator*(float scale) {
	return Vector2(x * scale, y * scale);
}

Vector2 operator+(const Vector2& va, const Vector2 vb) {
	return Vector2(va.x + vb.x, va.y + vb.y);
}

Vector2 operator-(const Vector2& va, const Vector2 vb) {
	return Vector2(va.x - vb.x, va.y - vb.y);
}

float
Vector2::Magnitude()const {
	return hypot(x, y);
}


void
Vector2::Normalize() {
	float mag = Magnitude();
	x /= mag;
	y /= mag;
}


Vector2
Vector2::Normalized()const {
	float mag = Magnitude();
	return Vector2(x / mag, y / mag);
}

float Vector2::SQMagnitude()const
{
	return x * x + y * y;
}


///���ς�Ԃ�
float
Dot(const Vector2& va, const Vector2& vb) {
	return va.x * vb.x + va.y * vb.y;
}

///�O�ς�Ԃ�
float
Cross(const Vector2& va, const Vector2& vb) {
	return va.x * vb.y - vb.x * va.y;
}

///���ω��Z�q
float
operator*(const Vector2& va, const Vector2& vb) {
	return Dot(va, vb);
}

///�O�ω��Z�q
float
operator%(const Vector2& va, const Vector2& vb) {
	return Cross(va, vb);
}


bool Vector2::operator==(const Vector2& v) const
{
	return x == v.x && y == v.y;
}

bool Vector2::operator!=(const Vector2 v) const
{
	return !(x == v.x && y == v.y);
}

void
Vector2::operator+=(const Vector2& v) {
	x += v.x;
	y += v.y;
}
void
Vector2::operator-=(const Vector2& v) {
	x -= v.x;
	y -= v.y;
}
