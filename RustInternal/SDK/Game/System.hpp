#pragma once

namespace SDK {
	namespace System {
		class BufferList;
		class ListDictionary {
		public:
			BufferList* GetValues() {
				return *reinterpret_cast<BufferList**>(this + 0x28);
			}
		};

		class BufferList {
		public:
			int GetSize() {
				return *reinterpret_cast<int*>(this + 0x10);
			}

			void* GetBuffer() {
				return *reinterpret_cast<void**>(this + 0x18);
			}

			void* GetArray(int index) {
				return *reinterpret_cast<void**>((uintptr_t)this->GetBuffer() + (0x20 + ((uintptr_t)index * 0x8)));
			}
		};

		template<typename T = void*>
		class List {
		public:
			T GetBuffer() {
				return *reinterpret_cast<T*>(this + 0x10);
			}

			T GetArray(int index) {
				return *reinterpret_cast<T*>(this->GetBuffer() + (0x20 + ((uintptr_t)index * 0x8)));
			}

			int GetSize() {
				return *reinterpret_cast<int*>(this + 0x18);
			}
		};

		template<typename T = void*>
		class Array {
		public:
			int ArraySize() {
				return *reinterpret_cast<int*>(this + 0x18);
			}

			T GetArray(int index) {
				return *reinterpret_cast<T*>(this + (0x20 + ((uintptr_t)index * 0x8)));
			}
		};

		class String {
		public:
			char pad_000[0x10];
			int stringSize;
			wchar_t stringBuffer[128 + 1];

			static String* New(const char* string) {
				return (String*)Dissector::IL2CPP::CreateNewString(string);
			}
		};

		class Type {
		public:
			CLASS("System", "Type");

			STATIC_METHOD(GetType, "GetType", Type*, String*);
		};
	}
}