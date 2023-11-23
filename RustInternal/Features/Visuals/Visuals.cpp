#include "Visuals.hpp"

bool Visuals::Bounds::GetBoundingBox(SDK::BaseEntity* entity) {
	if (!entity)
		return false;

	/* Not sure if it automatically does this */
	/* Reset the bounds every time */
	this->left = this->top = 10000.f;
	this->right = this->bottom = -10000.f;

	/* Get our Bound Positions */
	SDK::OBB rotatedOBB = entity->WorldSpaceBounds();
	if (entity->IsFrom("BasePlayer")) {
		rotatedOBB = ((SDK::BasePlayer*)entity)->WorldSpaceBounds();
	}

	SDK::Bounds entityBounds = rotatedOBB.ToBounds();
	Vector3 boundCenter = entityBounds.m_Center; /* center is only the addition from the transform position */
	Vector3 boundExtents = entityBounds.m_Extents;

	Vector3 boundPositions[8] = {
		// bottom corners
		Vector3(boundCenter.x - boundExtents.x, boundCenter.y - boundExtents.y, boundCenter.z - boundExtents.z),
		Vector3(boundCenter.x + boundExtents.x, boundCenter.y - boundExtents.y, boundCenter.z - boundExtents.z),
		Vector3(boundCenter.x - boundExtents.x, boundCenter.y - boundExtents.y, boundCenter.z + boundExtents.z),
		Vector3(boundCenter.x + boundExtents.x, boundCenter.y - boundExtents.y, boundCenter.z + boundExtents.z),

		// top corners
		Vector3(boundCenter.x - boundExtents.x, boundCenter.y + boundExtents.y, boundCenter.z - boundExtents.z),
		Vector3(boundCenter.x + boundExtents.x, boundCenter.y + boundExtents.y, boundCenter.z - boundExtents.z),
		Vector3(boundCenter.x - boundExtents.x, boundCenter.y + boundExtents.y, boundCenter.z + boundExtents.z),
		Vector3(boundCenter.x + boundExtents.x, boundCenter.y + boundExtents.y, boundCenter.z + boundExtents.z)
	};

	/* Do Our Bounds */
	for (Vector3 boundPos : boundPositions) {
		Vector2 boundPos2D = SDK::UnityEngine::Camera::WorldToScreen(boundPos);
		if (boundPos2D.x < this->left) {
			this->left = boundPos2D.x;
		}

		if (boundPos2D.y < this->top) {
			this->top = boundPos2D.y;
		}

		if (boundPos2D.x > this->right) {
			this->right = boundPos2D.x;
		}

		if (boundPos2D.y > this->bottom) {
			this->bottom = boundPos2D.y;
		}
	}

	if (this->IsInvalid())
		return false;

	/* Increase this so that it increases while being far away */
	float boundExpansion = 2.f;

	this->left -= boundExpansion + 1.f;
	this->right += boundExpansion + 1.f;

	this->top -= boundExpansion;
	this->bottom += boundExpansion;

	return true;
}

void Visuals::LoopEntities() {
	Cheat::localPlayer = SDK::LocalPlayer::GetEntity();
	if (!Cheat::localPlayer)
		return;

	SDK::BaseNetworkable::EntityRealm* clientEntities = SDK::BaseNetworkable::clientEntities();
	if (!clientEntities)
		return;

	SDK::System::ListDictionary* entityList = clientEntities->entityList();
	if (!entityList)
		return;

	SDK::System::BufferList* entityListValues = entityList->GetValues();
	if (!entityListValues)
		return;

	int entityAmount = entityListValues->GetSize();
	if (entityAmount <= 0)
		return;

	for (int entIndex = 0; entIndex < entityAmount; ++entIndex) {
		SDK::BaseEntity* entity = (SDK::BaseEntity*)entityListValues->GetArray(entIndex);
		if (!entity)
			continue;

		if (entity == Cheat::localPlayer)
			continue;

		if (entity->IsFrom("BasePlayer")) {
			Player::DrawVisuals((SDK::BasePlayer*)entity);
			continue;
		}

		World::DrawVisuals(entity);
	}
}