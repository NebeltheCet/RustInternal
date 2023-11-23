#pragma once
#include <cmath>

class Vector3 {
public:
	float x, y, z;

	Vector3() {
		x = y = z = 0.f;
	}

	Vector3(float newX, float newY, float newZ) {
		x = newX;
		y = newY;
		z = newZ;
	}

	Vector3 operator+(float fInput) {
		return Vector3{ x + fInput, y + fInput, z + fInput };
	}

	Vector3 operator-(float fInput) {
		return Vector3{ x - fInput, y - fInput, z - fInput };
	}

	Vector3 operator/(float fInput) {
		return Vector3{ x / fInput, y / fInput, z / fInput };
	}

	Vector3 operator*(float fInput) {
		return Vector3{ x * fInput, y * fInput, z * fInput };
	}

	Vector3 operator+(Vector3 vInput) {
		return Vector3{ x + vInput.x, y + vInput.y, z + vInput.z };
	}

	Vector3 operator-(Vector3 vInput) {
		return Vector3{ x - vInput.x, y - vInput.y, z - vInput.z };
	}

	Vector3 operator*(Vector3 vInput) {
		return Vector3{ x * vInput.x, y * vInput.y, z * vInput.z };
	}

	Vector3 operator/(Vector3 vInput) {
		return Vector3{ x / vInput.x, y / vInput.y, z / vInput.z };
	}

	Vector3& operator-=(Vector3 vInput) {
		x -= vInput.x;
		y -= vInput.y;
		z -= vInput.z;

		return *this;
	}

	Vector3& operator+=(Vector3 vInput) {
		x += vInput.x;
		y += vInput.y;
		z += vInput.z;
		return *this;
	}

	Vector3& operator*=(Vector3 vInput) {
		x *= vInput.x;
		y *= vInput.y;
		z *= vInput.z;
		return *this;
	}

	Vector3& operator/=(Vector3 vInput) {
		x /= vInput.x;
		y /= vInput.y;
		z /= vInput.z;
		return *this;
	}

	Vector3& operator/=(float fInput) {
		x /= fInput;
		y /= fInput;
		z /= fInput;
		return *this;
	}

	Vector3& operator*=(float fInput) {
		x *= fInput;
		y *= fInput;
		z *= fInput;
		return *this;
	}

	Vector3& operator-=(float fInput) {
		x -= fInput;
		y -= fInput;
		z -= fInput;
		return *this;
	}

	Vector3& operator+=(float fInput) {
		x += fInput;
		y += fInput;
		z += fInput;
		return *this;
	}

	bool operator==(Vector3 vInput) {
		return x == vInput.x && y == vInput.y && z == vInput.z;
	}

	bool operator!=(Vector3 vInput) {
		if (x != vInput.x || y != vInput.y || z != vInput.z)
			return true;

		return false;
	}

	void Abs();
	float LengthSqr();
	float Length();
	float Length2D();
	float Distance(Vector3 vInput);
	float Distance2D(Vector3 vInput);
	float Dot(Vector3 vInput);
	Vector3 Normalized();
	bool Empty();
	Vector3 MoveTowards(Vector3 targetPos, float stepSize);
};