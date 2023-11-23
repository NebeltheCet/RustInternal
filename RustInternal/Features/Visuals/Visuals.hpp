#pragma once
#include "../../SDK/Utils/Renderer/Renderer.hpp"

namespace Visuals {
	class Bounds {
	public:
		float left = 10000.f;
		float right = -10000.f;

		float top = 10000.f;
		float bottom = -10000.f;
		Bounds() {
			left = 10000.f;
			right = -10000.f;

			top = 10000.f;
			bottom = -10000.f;
		}

		bool IsInvalid() {
			bool isZero = left == 0.f || right == 0.f || top == 0.f || bottom == 0.f;
			bool isDefault = left == 10000.f || right == -10000.f || top == 10000.f || bottom == -10000.f;
			return isZero || isDefault;
		}

		bool GetBoundingBox(SDK::BaseEntity* entity);
	};

	namespace Player {
		void DrawVisuals(SDK::BasePlayer* playerEntity);
	}

	namespace World {
		class ObjectInfo {
		public:
			SDK::BaseEntity* objectEntity = nullptr;
			const char* objectName = "";
			const char* className = "";
			bool boxESP = false;
			bool nameESP = false;

			ObjectInfo(SDK::BaseEntity* objectEnt, const char* wantedClassName, const char* wantedObjectName, bool enableBoxESP, bool enableNameESP) {
				this->objectEntity = objectEnt;
				this->objectName = wantedObjectName;
				this->className = wantedClassName;
				this->boxESP = enableBoxESP;
				this->nameESP = enableNameESP;
			}
		};

		void AddESPObject(ObjectInfo objectInfo);
		void DrawVisuals(SDK::BaseEntity* entity);
	}

	void LoopEntities();
}