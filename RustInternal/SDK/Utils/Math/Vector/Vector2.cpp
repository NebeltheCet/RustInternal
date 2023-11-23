#include "Vector2.hpp"

#include <cmath>

void Vector2::Abs() {
	this->x = abs(this->x);
	this->y = abs(this->y);
}

float Vector2::Length() {
	return sqrt((this->x * this->x) + (this->y * this->y));
}

float Vector2::Distance(Vector2 vInput) {
	return (*this - vInput).Length();
}

float Vector2::Distance2D(Vector2 vInput) {
	return sqrt(powf(this->x - vInput.x, 2) + powf(this->y - vInput.y, 2));
}

Vector2 Vector2::Normalized() {
	return Vector2(this->x / Length(), this->y / Length());
}

bool Vector2::Empty() {
	return this->x == 0.f && this->y == 0.f;
}