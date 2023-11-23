#include "../Hooks.hpp"
#include "../../Features/Visuals/Visuals.hpp"

void Hooks::Methods::VisualizeTexelDensity::hkOnGUI(SDK::VisualizeTexelDensity* _this) {
	Cheat::drawCallTime = -1.f; /* let MainMenuSystem know that we dont need another object */

	/* dont render anything on anything other than repaint */
	static SDK::UnityEngine::Event* currentEvent = SDK::UnityEngine::Event::GetCurrent();
	if (!currentEvent)
		return;

	SDK::UnityEngine::Event::EventType eventType = currentEvent->GetType();
	if (eventType != SDK::UnityEngine::Event::EventType::Repaint)
		return;

	static int frames = 0;
	if (frames % 128 == 0 || !Cheat::mainCamera) { /* Getting the Main Camera over and over again rips fps(atleast on my side) so i'll just get it every 128 repaint frames */
		Cheat::mainCamera = SDK::UnityEngine::Camera::GetMain();
		frames = 0;
	}
	
	/* Loop Entities and Render ESP */
	Visuals::LoopEntities();

	/* Render Watermark After ESP */
	Renderer::DrawLabel(Vector2(50.f, 50.f), SDK::System::String::New("Rust Internal"), Color(255.f, 255.f, 255.f, 255.f), false, 10);


	frames++;
}