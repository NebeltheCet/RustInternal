#pragma once
#include "../SDK/Utils/Renderer/Renderer.hpp"
#include <map>

namespace Hooks {
	namespace Methods {
		namespace MainMenuSystem {
			void hkUpdate(SDK::MainMenuSystem* _this);
		}

		namespace VisualizeTexelDensity {
			void hkOnGUI(SDK::VisualizeTexelDensity* _this);
		}
	}

	namespace Utils {
		class HookLibrary {
		public:
			void Initialize(const char* ns, const char* cn) {
				this->classPtr = Dissector::FindClass(ns, cn);
			}

			void Attach(const char* methodName, void* detourFunction) {
				Dissector::IL2CPP::IL2CPPMethod* method = Dissector::FindMethod(this->classPtr, methodName);
				if (!method)
					return;

				Dissector::IL2CPP::IL2CPPMethod* methodPtr = method->methodPtr;
				if (!methodPtr)
					return;

				/* Pointer Swap our wanted function */
				this->oMethod[methodName] = reinterpret_cast<uintptr_t>(methodPtr);
				*reinterpret_cast<PVOID*>(method) = detourFunction;
				printf("successfully hooked %s[0x%X]\n", methodName, (int)this->oMethod[methodName]);
			}

			void Detach() {
				if (this->oMethod.empty())
					return;

				for (const auto& methodPair : this->oMethod) {
					Dissector::IL2CPP::IL2CPPMethod* method = Dissector::FindMethod(this->classPtr, methodPair.first);
					if (!method)
						continue;

					*reinterpret_cast<PVOID*>(method) = reinterpret_cast<PVOID>(methodPair.second);
					printf("successfully unhooked %s\n", methodPair.first);
				}

				this->oMethod.clear();
			}

			template< typename functionType>
			functionType GetOriginal(const char* methodName) {
				if (this->oMethod.empty() || this->oMethod.find(methodName) == this->oMethod.end())
					return functionType();

				return reinterpret_cast<functionType>(this->oMethod[methodName]);
			}
		private:
			Dissector::IL2CPP::IL2CPPClass* classPtr = nullptr;

			std::map<const char*, uintptr_t> oMethod;
		};
	}

	inline Utils::HookLibrary mainMenuSystem;
	inline Utils::HookLibrary visualizeTexelDensity;

	void Attach();
	void Detach();
}