#include "../Visuals.hpp"

void Visuals::Player::DrawVisuals(SDK::BasePlayer* playerEntity) {
	if (!playerEntity)
		return;

	if (playerEntity->lifeState() != SDK::BaseCombatEntity::LifeState::Alive)
		return;

	if (!playerEntity->playerModel())
		return;

	if (playerEntity->playerModel()->IsNPC())
		return;

	//if (playerEntity->playerFlags() & SDK::BasePlayer::PlayerFlags::Sleeping)
		//return;

	/* Get Player Bounds */
	Bounds playerBounds;
	if (!playerBounds.GetBoundingBox(playerEntity))
		return;

	Color espColor = Color(255.f, 255.f, 255.f, 255.f);
	Vector2 topMiddle = Vector2((playerBounds.left + playerBounds.right) / 2.f, playerBounds.top);
	Vector2 bottomMiddle = Vector2((playerBounds.left + playerBounds.right) / 2.f, playerBounds.bottom);

	float yAdd = 5.f;
	int fontSize = 10;
	if (true) { /* box esp */
		float boxWidth = playerBounds.right - playerBounds.left;
		float boxHeight = playerBounds.bottom - playerBounds.top;

		Renderer::DrawRect(Vector2(playerBounds.left, playerBounds.top), Vector2(boxWidth, boxHeight), espColor);
	}

	if (true) { /* name esp */
		SDK::System::String* playerName = playerEntity->displayName();
		if (playerName) { /* we can use y add to negate it since it starts from 5 and wont increase here */
			Renderer::DrawLabel(topMiddle - Vector2(0.f, yAdd), playerName, espColor, true, fontSize);
		}
	}

	if (true) { /* health esp / healthbar */
		Vector2 healthbarPos = Vector2(playerBounds.left - 5.f, playerBounds.bottom);

		float healthRatio = min((playerEntity->health() / 100.f), 1.f);
		float redColor = 255.f * (1.f - healthRatio);
		float greenColor = 255.f * healthRatio;
		float blueColor = 0.f;

		float boxHeight = -(playerBounds.bottom - playerBounds.top);
		float healthHeight = (boxHeight * healthRatio);
		float healthWidth = 3.f;

		float lineThickness = 1.f;
		Color healthbarColor = Color(redColor, greenColor, blueColor, 255.f);

		Renderer::DrawFilledRect(healthbarPos - lineThickness, Vector2(healthWidth, boxHeight) + (lineThickness * 2.f), Color(10.f, 10.f, 10.f, 150.f)); /* Background */

		Renderer::DrawFilledRect(healthbarPos, Vector2(healthWidth, healthHeight), healthbarColor);
	}
}