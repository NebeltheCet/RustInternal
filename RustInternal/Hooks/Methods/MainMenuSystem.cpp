#include "../Hooks.hpp"

void Hooks::Methods::MainMenuSystem::hkUpdate(SDK::MainMenuSystem* _this) {
	if (Cheat::drawCallTime == 0.f) {
		Cheat::drawCallTime = SDK::UnityEngine::Time::GetTime();
	}

	if (SDK::UnityEngine::Time::GetTime() >= Cheat::drawCallTime + 0.5f && Cheat::drawCallTime > 0.f) {
		static SDK::VisualizeTexelDensity* instance = (SDK::VisualizeTexelDensity*)_this->GetGameObject()->AddComponent(SDK::System::Type::GetType(SDK::System::String::New("VisualizeTexelDensity, Assembly-CSharp")));
	}

	mainMenuSystem.GetOriginal<decltype(&hkUpdate)>("Update")(_this);
}
