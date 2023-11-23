#include "Renderer.hpp"

void Renderer::DrawLabel(Vector2 textPos, SDK::System::String* text, Color textColor, bool centeredText, int fontSize) {
	Vector2 tempVec = textPos;
	static SDK::UnityEngine::GUISkin* skin = SDK::UnityEngine::GUI::GetSkin();
	if (!skin)
		return;

	static SDK::UnityEngine::GUIStyle* style = skin->GetLabel();
	if (!style)
		return;

	SDK::UnityEngine::GUIContent* content = SDK::UnityEngine::GUIContent::Temp(text);
	if (!content)
		return;

	style->SetFontSize(fontSize);
	style->SetAlignment(SDK::UnityEngine::TextAnchor::UpperLeft);
	Vector2 textSize = style->CalcSize(content);
	if (centeredText)
		tempVec -= textSize / 2.0f;

	/* "shadow" */
	SDK::UnityEngine::GUI::SetColor(Color(10.f, 10.f, 10.f, 255.f).ToUnityColor());
	SDK::UnityEngine::GUI::Label(SDK::UnityEngine::Rect(tempVec + Vector2(1.f, 1.f), Vector2(textSize.x, textSize.y)), text);

	SDK::UnityEngine::GUI::SetColor(textColor.ToUnityColor());
	SDK::UnityEngine::GUI::Label(SDK::UnityEngine::Rect(tempVec, Vector2(textSize.x, textSize.y)), text);
}

void Renderer::DrawFilledRect(Vector2 rectPos, Vector2 rectSize, Color rectColor) {
	static SDK::UnityEngine::Texture* whiteTexture = SDK::UnityEngine::Texture2D::GetWhiteTexture();
	if (!whiteTexture)
		return;

	SDK::UnityEngine::GUI::SetColor(rectColor.ToUnityColor());
	SDK::UnityEngine::GUI::DrawTexture(SDK::UnityEngine::Rect(rectPos, rectSize), whiteTexture);
}

void Renderer::DrawRect(Vector2 rectPos, Vector2 rectSize, Color rectColor) {
	float thickness = 1.f;

	DrawFilledRect(Vector2(rectPos.x, rectPos.y), Vector2(thickness, rectSize.y), rectColor);
	DrawFilledRect(Vector2(rectPos.x + rectSize.x, rectPos.y), Vector2(thickness, rectSize.y + thickness), rectColor);
	DrawFilledRect(Vector2(rectPos.x, rectPos.y), Vector2(rectSize.x, thickness), rectColor);
	DrawFilledRect(Vector2(rectPos.x, rectPos.y + rectSize.y), Vector2(rectSize.x, thickness), rectColor);
}