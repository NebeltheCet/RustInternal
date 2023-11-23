#include "Vector3.hpp"

void Vector3::Abs() {
	this->x = abs(this->x);
	this->y = abs(this->y);
	this->z = abs(this->z);
}

float Vector3::LengthSqr() {
	return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
}

float Vector3::Length() {
	return sqrt(LengthSqr());
}

float Vector3::Length2D() {
	return sqrt((this->x * this->x) + (this->y * this->y));
}

float Vector3::Distance(Vector3 vInput) {
	return (*this - vInput).Length();
}

float Vector3::Distance2D(Vector3 vInput) {
	return (*this - vInput).Length2D();
}

float Vector3::Dot(Vector3 vInput) {
	return this->x * vInput.x + this->y * vInput.y + this->z * vInput.z;
}

Vector3 Vector3::Normalized() {
	return Vector3(this->x / Length(), this->y / Length(), this->z / Length());
}

bool Vector3::Empty() {
	return this->x == 0.f && this->y == 0.f && this->z == 0.f;
}

Vector3 Vector3::MoveTowards(Vector3 targetPos, float stepSize) {
	Vector3 currentPos = *this;

	return currentPos + ((targetPos - currentPos).Normalized() * stepSize);
}