#pragma once

class Vector2 {
public:
	float x, y;

	Vector2() {
		x = y = 0.f;
	}

	Vector2(float newX, float newY) {
		x = newX;
		y = newY;
	}

	Vector2(int newX, int newY) { /* lets stop getting warnings :p */
		x = (float)newX;
		y = (float)newY;
	}

	Vector2 operator+(float fInput) {
		return Vector2{ x + fInput, y + fInput };
	}

	Vector2 operator-(float fInput) {
		return Vector2{ x - fInput, y - fInput };
	}

	Vector2 operator/(float fInput) {
		return Vector2{ x / fInput, y / fInput };
	}

	Vector2 operator*(float fInput) {
		return Vector2{ x * fInput, y * fInput };
	}

	Vector2 operator+(Vector2 vInput) {
		return Vector2{ x + vInput.x, y + vInput.y };
	}

	Vector2 operator-(Vector2 vInput) {
		return Vector2{ x - vInput.x, y - vInput.y };
	}

	Vector2 operator*(Vector2 vInput) {
		return Vector2{ x * vInput.x, y * vInput.y };
	}

	Vector2 operator/(Vector2 vInput) {
		return Vector2{ x / vInput.x, y / vInput.y };
	}

	Vector2& operator-=(Vector2 vInput) {
		x -= vInput.x;
		y -= vInput.y;

		return *this;
	}

	Vector2& operator+=(Vector2 vInput) {
		x += vInput.x;
		y += vInput.y;

		return *this;
	}

	Vector2& operator*=(Vector2 vInput) {
		x *= vInput.x;
		y *= vInput.y;

		return *this;
	}

	Vector2& operator/=(Vector2 vInput) {
		x /= vInput.x;
		y /= vInput.y;

		return *this;
	}

	Vector2& operator/=(float fInput) {
		x /= fInput;
		y /= fInput;

		return *this;
	}

	Vector2& operator*=(float fInput) {
		x *= fInput;
		y *= fInput;

		return *this;
	}

	Vector2& operator-=(float fInput) {
		x -= fInput;
		y -= fInput;

		return *this;
	}

	Vector2& operator+=(float fInput) {
		x += fInput;
		y += fInput;

		return *this;
	}

	bool operator==(Vector2& vInput) {
		return x == vInput.x && y == vInput.y;
	}

	bool operator!=(Vector2& vInput) {
		if (x != vInput.x || y != vInput.y)
			return true;

		return false;
	}

	void Abs();
	float Length();
	float Distance(Vector2 vInput);
	float Distance2D(Vector2 vInput);
	Vector2 Normalized();
	bool Empty();
};