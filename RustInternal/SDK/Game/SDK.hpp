#pragma once

#include "../Utils/Dissector/Dissector.hpp"
#include "../Cheat.hpp"

#include "System.hpp"
#include "UnityEngine.hpp"

namespace SDK {
	class FacepunchBehaviour : public UnityEngine::MonoBehaviour {
	public:

	};

	class BaseMonoBehaviour : public FacepunchBehaviour {
	public:

	};

	class Bounds {
	public:
		Vector3 m_Center; // 0x0
		Vector3 m_Extents; // 0xC

		bool InsideBounds(Vector3 targetPoint) {
			Vector3 minBound(
				this->m_Center.x - this->m_Extents.x,
				this->m_Center.y - this->m_Extents.y,
				this->m_Center.z - this->m_Extents.z
			);

			Vector3 maxBound(
				this->m_Center.x + this->m_Extents.x,
				this->m_Center.y + this->m_Extents.y,
				this->m_Center.z + this->m_Extents.z
			);

			/* is our targetPoint inside of our Bounds */
			if (targetPoint.x >= minBound.x && targetPoint.x <= maxBound.x && targetPoint.y >= minBound.y && targetPoint.y <= maxBound.y && targetPoint.z >= minBound.z && targetPoint.z <= maxBound.z)
				return true;

			return false;
		}
	};

	class OBB {
	public:
		CLASS("", "OBB");

		UnityEngine::Quaternion rotation; // 0x0
		Vector3 position; // 0x10
		Vector3 extents; // 0x1C
		Vector3 forward; // 0x28
		Vector3 right; // 0x34
		Vector3 up; // 0x40
		float reject; // 0x4C

		METHOD(ToBounds, "ToBounds", Bounds);
	};

	class MainMenuSystem : public UnityEngine::Component { /* Doesnt inherit it in Il2CPPDumper but whatever */
	public:

	};

	class VisualizeTexelDensity : public UnityEngine::MonoBehaviour {
	public:
		CLASS("", "VisualizeTexelDensity");

		FIELD(showHUD, "showHUD", bool);
	};

	class BaseNetworkable : public BaseMonoBehaviour {
	public:
		CLASS("", "BaseNetworkable");
		class EntityRealm {
		public:
			CLASS("", "BaseNetworkable/EntityRealm");

			FIELD(entityList, "entityList", System::ListDictionary*);
		};

		STATIC_FIELD(clientEntities, "clientEntities", EntityRealm*);

		METHOD(GetShortPrefabName, "get_ShortPrefabName", System::String*);
	};

	class BaseEntity : public BaseNetworkable {
	public:
		CLASS("", "BaseEntity");

		METHOD(WorldSpaceBounds, "WorldSpaceBounds", OBB);
	};

	class BaseCombatEntity : public BaseEntity {
	public:
		enum LifeState : int {
			Alive = 0,
			Dead = 1
		};

		CLASS("", "BaseCombatEntity");

		FIELD(lifeState, "lifestate", LifeState);
		FIELD(health, "_health", float);
		FIELD(maxHealth, "_maxHealth", float);
	};

	class PlayerModel {
	public:
		CLASS("", "PlayerModel");

		METHOD(IsNPC, "get_IsNpc", bool);
	};

	class BasePlayer : public BaseCombatEntity {
	public:
		enum PlayerFlags : int {
			Unused1 = 1,
			Unused2 = 2,
			IsAdmin = 4,
			ReceivingSnapshot = 8,
			Sleeping = 16,
			Spectating = 32,
			Wounded = 64,
			IsDeveloper = 128,
			Connected = 256,
			ThirdPersonViewmode = 1024,
			EyesViewmode = 2048,
			ChatMute = 4096,
			NoSprint = 8192,
			Aiming = 16384,
			DisplaySash = 32768,
			Relaxed = 65536,
			SafeZone = 131072,
			ServerFall = 262144,
			Incapacitated = 524288,
			Workbench1 = 1048576,
			Workbench2 = 2097152,
			Workbench3 = 4194304,
			VoiceRangeBoost = 8388608
		};

		CLASS("", "BasePlayer");

		FIELD(displayName, "_displayName", System::String*);
		FIELD(playerModel, "playerModel", PlayerModel*);
		FIELD(playerFlags, "playerFlags", int);

		METHOD(WorldSpaceBounds, "WorldSpaceBounds", OBB);
	};

	class LocalPlayer {
	public:
		CLASS("", "LocalPlayer");

		STATIC_METHOD(GetEntity, "get_Entity", BasePlayer*);
	};
}