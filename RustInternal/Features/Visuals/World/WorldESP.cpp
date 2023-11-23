#include "../Visuals.hpp"

void Visuals::World::AddESPObject(Visuals::World::ObjectInfo objectInfo) {
	if (!objectInfo.objectEntity)
		return;

	if (!objectInfo.objectEntity->IsFrom(objectInfo.className)) {
		wchar_t* shortPrefabName = objectInfo.objectEntity->GetShortPrefabName()->stringBuffer;
		int len = (int)wcslen(shortPrefabName);
		static char valueBuf[256] = { NULL };
		
		for (int charIndex = 0; charIndex <= len; ++charIndex) {
			valueBuf[charIndex] = static_cast<char>(shortPrefabName[charIndex]);
		}

		if (strcmp(valueBuf, objectInfo.className) != NULL) {
			return;
		}
	}

	/* Get Entity Bounds */
	Bounds entityBounds;
	if (!entityBounds.GetBoundingBox(objectInfo.objectEntity))
		return;

	int fontSize = 10;
	Color espColor = Color(255.f, 255.f, 255.f, 255.f);

	Vector2 topMiddle = Vector2((entityBounds.left + entityBounds.right) / 2.f, entityBounds.top);
	Vector2 bottomMiddle = Vector2((entityBounds.left + entityBounds.right) / 2.f, entityBounds.bottom);

	float yAdd = 5.f;
	if (objectInfo.boxESP) {
		float boxWidth = entityBounds.right - entityBounds.left;
		float boxHeight = entityBounds.bottom - entityBounds.top;

		Renderer::DrawRect(Vector2(entityBounds.left, entityBounds.top), Vector2(boxWidth, boxHeight), espColor);
	}

	if (objectInfo.nameESP) {
		Renderer::DrawLabel(topMiddle - Vector2(0.f, yAdd), SDK::System::String::New(objectInfo.objectName), espColor, true, fontSize);
	}
}

void Visuals::World::DrawVisuals(SDK::BaseEntity* entity) {
	if (!entity)
		return;

	AddESPObject(ObjectInfo(entity, "stone-ore", "Stone Ore", true, true));
	AddESPObject(ObjectInfo(entity, "sulfur-ore", "Sulfur Ore", true, true));
	AddESPObject(ObjectInfo(entity, "metal-ore", "Metal Ore", true, true));
}