#pragma once

#include "Utils/Renderer/Color/Color.hpp"
#include "Utils/Math/Vector/Vector2.hpp"
#include "Utils/Math/Vector/Vector3.hpp"

/* Pre-define classes because i am a retard */
namespace SDK {
	namespace UnityEngine {
		class Camera;
	}

	class BasePlayer;
}

/* File for storing Global Variables. */
namespace Cheat {
	inline SDK::UnityEngine::Camera* mainCamera;
	inline SDK::BasePlayer* localPlayer;

	inline float drawCallTime = 0.f;
}