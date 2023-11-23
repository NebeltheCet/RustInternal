#include "Color.hpp"

Color::Color(float newR, float newG, float newB, float newA) {
	this->r = newR;
	this->g = newG;
	this->b = newB;
	this->a = newA;
}

Color Color::ToUnityColor() {
	return Color(this->r / 255.f, this->g / 255.f, this->b / 255.f, this->a / 255.f);
}