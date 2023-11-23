#pragma once

class Color {
public:
	float r, g, b, a;
	Color(float newR, float newG, float newB, float newA = 255.f);
	Color ToUnityColor();
};