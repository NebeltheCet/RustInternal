#pragma once
#undef GetClassName

namespace SDK {
	namespace UnityEngine {
		enum TextAnchor {
			UpperLeft = 0,
			UpperCenter = 1,
			UpperRight = 2,
			MiddleLeft = 3,
			MiddleCenter = 4,
			MiddleRight = 5,
			LowerLeft = 6,
			LowerCenter = 7,
			LowerRight = 8
		};

		class Rect {
		public:
			float m_XMin; // 0x0
			float m_YMin; // 0x4
			float m_Width; // 0x8
			float m_Height; // 0xC

			Rect(float x, float y, float width, float height) {
				m_XMin = x;
				m_YMin = y;
				m_Width = width;
				m_Height = height;
			}

			Rect(Vector2 position, Vector2 size) {
				m_XMin = position.x;
				m_YMin = position.y;
				m_Width = size.x;
				m_Height = size.y;
			}
		};

		class Quaternion {
		public:
			CLASS("UnityEngine", "Quaternion");

			float x; // 0x0
			float y; // 0x4
			float z; // 0x8
			float w; // 0xC
		};

		class Event {
		public:
			CLASS("UnityEngine", "Event");
			enum class EventType {
				MouseDown = 0,
				MouseUp = 1,
				MouseMove = 2,
				MouseDrag = 3,
				KeyDown = 4,
				KeyUp = 5,
				ScrollWheel = 6,
				Repaint = 7,
				Layout = 8,
				DragUpdated = 9,
				DragPerform = 10,
				Ignore = 11,
				Used = 12,
				ValidateCommand = 13,
				ExecuteCommand = 14,
				DragExited = 15,
				ContextClick = 16,
				MouseEnterWindow = 20,
				MouseLeaveWindow = 21,
				TouchDown = 30,
				TouchUp = 31,
				TouchMove = 32,
				TouchEnter = 33,
				TouchLeave = 34,
				TouchStationary = 35
			};

			STATIC_METHOD(GetCurrent, "get_current", Event*);

			METHOD(GetType, "get_type", EventType);
		};

		class Screen {
		public:
			CLASS("UnityEngine", "Screen");

			STATIC_METHOD(GetWidth, "get_width", int);
			STATIC_METHOD(GetHeight, "get_height", int);
		};

		class Time {
		public:
			CLASS("UnityEngine", "Time");

			STATIC_METHOD(GetTime, "get_time", float);
		};

		class Object {
		public:
			CLASS("UnityEngine", "Object");

		};

		class Component;
		class GameObject : public Object {
		public:
			CLASS("UnityEngine", "GameObject");

			METHOD(AddComponent, "AddComponent", Component*, System::Type*);
			METHOD(GetComponent, "GetComponent", Component*, System::Type*);
		};

		class Transform;
		class Component : public Object {
		public:
			CLASS("UnityEngine", "Component");

			METHOD(GetGameObject, "get_gameObject", GameObject*);
			METHOD(GetTransform, "get_transform", Transform*);
			METHOD(GetComponent, "GetComponent", Component*, System::Type*);

			const char* GetClassName() {
				uintptr_t classPtr = *reinterpret_cast<uintptr_t*>(this);
				if (!classPtr)
					return "";

				return *reinterpret_cast<const char**>(classPtr + 0x10);
			}

			bool IsFrom(const char* fromClassName) {
				if (!this)
					return false;

				const char* className = this->GetClassName();
				if (strcmp(className, fromClassName) != NULL)
					return false;

				return true;
			}
		};

		class Transform : public Component {
		public:
			CLASS("UnityEngine", "Transform");

			METHOD(GetPosition, "get_position", Vector3);
		};

		class Behaviour : public Component {
		public:
			CLASS("UnityEngine", "Behaviour");

		};

		class MonoBehaviour : public Behaviour {
		public:
			CLASS("UnityEngine", "MonoBehaviour");

		};

		class Texture {
		public:
			CLASS("UnityEngine", "Texture");

		};

		class Texture2D : public Texture {
		public:
			CLASS("UnityEngine", "Texture2D");

			STATIC_METHOD(GetWhiteTexture, "get_whiteTexture", Texture2D*);
		};

		class GUIContent {
		public:
			CLASS("UnityEngine", "GUIContent");

			STATIC_METHOD(Temp, "Temp", GUIContent*, System::String*);
		};

		class GUIStyle {
		public:
			CLASS("UnityEngine", "GUIStyle");

			METHOD(SetAlignment, "set_alignment", void, Enums::TextAnchor);
			METHOD(SetFontSize, "set_fontSize", void, int);

			Vector2 CalcSize(GUIContent* content) {
				Vector2 ret;

				typedef void(*CalcSizeFN)(GUIStyle*, GUIContent*, Vector2*);
				static uintptr_t methodOff = (uintptr_t)Dissector::FindMethod(Dissector::FindClass("UnityEngine", "GUIStyle"), "Internal_CalcSize_Injected", 2)->methodPtr;
				reinterpret_cast<CalcSizeFN>(methodOff)(this, content, &ret);

				return ret;
			}
		};

		class GUISkin {
		public:
			CLASS("UnityEngine", "GUISkin");

			METHOD(GetLabel, "get_label", GUIStyle*);
		};

		class GUI {
		public:
			CLASS("UnityEngine", "GUI");

			STATIC_METHOD(SetColor, "set_color", void, Color);
			STATIC_METHOD(Label, "Label", void, Rect, System::String*);
			STATIC_METHOD(DrawTexture, "DrawTexture", void, Rect, Texture*);
			STATIC_METHOD(GetSkin, "get_skin", GUISkin*);
		};

		class Camera : public Behaviour {
		public:
			CLASS("UnityEngine", "Camera");

			STATIC_METHOD(GetMain, "get_main", Camera*);
			METHOD(WorldToScreenPoint, "WorldToScreenPoint", Vector3, Vector3);

			static Vector2 WorldToScreen(Vector3 position) {
				Camera* mainCamera = Cheat::mainCamera;
				if (!mainCamera)
					return Vector2(0.f, 0.f);

				Vector3 worldToScreenPoint = mainCamera->WorldToScreenPoint(position);
				worldToScreenPoint.y = Screen::GetHeight() - worldToScreenPoint.y;
				if (worldToScreenPoint.z < 0.098f)
					return Vector2(0.f, 0.f);

				return Vector2(worldToScreenPoint.x, worldToScreenPoint.y);
			}
		};
	}
}