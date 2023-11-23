#pragma once
#include "../../Game/SDK.hpp"

namespace Renderer {
	void DrawLabel(Vector2 textPos, SDK::System::String* text, Color textColor = Color(255.f, 255.f, 255.f, 255.f), bool centeredText = false, int fontSize = 12);
	void DrawFilledRect(Vector2 rectPos, Vector2 rectSize, Color rectColor = Color(255.f, 255.f, 255.f, 255.f));
	void DrawRect(Vector2 rectPos, Vector2 rectSize, Color rectColor = Color(255.f, 255.f, 255.f, 255.f));
}