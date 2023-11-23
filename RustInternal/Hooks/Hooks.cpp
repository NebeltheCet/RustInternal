#include "Hooks.hpp"

void Hooks::Attach() {
	/* Initialize Hooks */
	mainMenuSystem.Initialize("", "MainMenuSystem");
	visualizeTexelDensity.Initialize("", "VisualizeTexelDensity");

	/* Attach Functions */
	mainMenuSystem.Attach("Update", &Methods::MainMenuSystem::hkUpdate);
	visualizeTexelDensity.Attach("OnGUI", &Methods::VisualizeTexelDensity::hkOnGUI);
}

void Hooks::Detach() {
	mainMenuSystem.Detach();
	visualizeTexelDensity.Detach();
}