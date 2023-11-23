#pragma once
#include "IL2CPP/IL2CPP.hpp"

#include <Windows.h>

#define GetExport(exportVar, exportName) exportVar = reinterpret_cast<decltype(exportVar)>(GetProcAddress(GetModuleHandleA("GameAssembly.dll"), exportName)); 

#define CLASS(namespaceName, className) \
static Dissector::IL2CPP::IL2CPPClass* TypeClass() { \
	return Dissector::FindClass(namespaceName, className); \
}

#define FIELD(fieldName, fieldPathName, fieldType) \
fieldType& fieldName() { \
	static auto fieldOff = (uintptr_t)Dissector::FindField(TypeClass(), fieldPathName); \
	return *reinterpret_cast<fieldType*>(this + fieldOff); \
}

#define STATIC_FIELD(fieldName, fieldPathName, fieldType) \
static fieldType& fieldName() { \
	static auto fieldOff = (uintptr_t)Dissector::FindField(TypeClass(), fieldPathName, true); \
	return *reinterpret_cast<fieldType*>(fieldOff); \
}

#define METHOD(methodName, methodPathName, returnType, ...) \
    template <typename... Args> \
    returnType methodName(Args... arguments) { \
        using methodName##FN = returnType (*)(void*, Args...); \
		static auto methodOff = (uintptr_t)Dissector::FindMethod(TypeClass(), methodPathName, sizeof...(Args))->methodPtr; \
        static auto methodPtr = reinterpret_cast<methodName##FN>(methodOff); \
        return methodPtr(this, arguments...); \
    }

#define STATIC_METHOD(methodName, methodPathName, returnType, ...) \
    template <typename... Args> \
    static returnType methodName(Args... arguments) { \
        using methodName##FN = returnType (*)(Args...); \
		static auto methodOff = (uintptr_t)Dissector::FindMethod(TypeClass(), methodPathName, sizeof...(Args))->methodPtr; \
        static auto methodPtr = reinterpret_cast<methodName##FN>(methodOff); \
        return methodPtr(arguments...); \
    }

namespace Dissector {
	namespace IL2CPP {
		typedef void* (*il2cpp_domain_get)();
		typedef void** (*il2cpp_domain_get_assemblies)(void* domainInstance, uintptr_t* assemblyAmount);
		typedef void* (*il2cpp_assembly_get_image)(void* imageInstance);
		typedef IL2CPP::IL2CPPClass* (*il2cpp_class_from_name)(void* imageInstance, const char* namespaceName, const char* className);
		typedef IL2CPP::IL2CPPMethod* (*il2cpp_class_get_methods)(IL2CPP::IL2CPPClass* classInstance, uintptr_t* methodIterator);
		typedef const char* (*il2cpp_method_get_name)(IL2CPP::IL2CPPMethod* methodInstance);
		typedef int(*il2cpp_method_get_param_count)(IL2CPP::IL2CPPMethod* methodInstance);
		typedef IL2CPP::IL2CPPField* (*il2cpp_class_get_fields)(IL2CPP::IL2CPPClass* classInstance, uintptr_t* fieldIterator);
		typedef uintptr_t(*il2cpp_field_get_offset)(IL2CPP::IL2CPPField* fieldInstance);
		typedef void* (*il2cpp_string_new)(const char* stringName);
		typedef void* (*il2cpp_object_new)(IL2CPP::IL2CPPClass* classInstance);
		typedef void* (*il2cpp_method_get_return_type)(IL2CPP::IL2CPPMethod* methodInstance);
		typedef void* (*il2cpp_class_get_type)(IL2CPP::IL2CPPClass* classInstance);
		typedef char* (*il2cpp_type_get_name)(void* typeInstance);
		typedef void* (*il2cpp_type_get_object)(void* typeInstance);

		/* Il2Cpp functions */
		inline il2cpp_domain_get GetDomain;
		inline il2cpp_domain_get_assemblies GetAssemblies;
		inline il2cpp_assembly_get_image GetAssemblyImage;
		inline il2cpp_class_from_name GetClassFromName;
		inline il2cpp_class_get_methods GetClassMethods;
		inline il2cpp_method_get_name GetMethodName;
		inline il2cpp_method_get_param_count GetMethodParamCount;
		inline il2cpp_class_get_fields GetClassFields;
		inline il2cpp_field_get_offset GetFieldOffset;
		inline il2cpp_string_new CreateNewString;
		inline il2cpp_object_new CreateNewObject;
		inline il2cpp_method_get_return_type GetMethodReturnType;
		inline il2cpp_class_get_type GetClassType;
		inline il2cpp_type_get_name GetTypeName;
		inline il2cpp_type_get_object GetTypeObject;
	}

	void Attach();

	void* GetClassTypeObject(const char* namespaceName, const char* className);
	IL2CPP::IL2CPPClass* FindClass(const char* namespaceName, const char* className);
	IL2CPP::IL2CPPMethod* FindMethod(IL2CPP::IL2CPPClass* classInstance, const char* methodName, int argCount = -1, const char* returnType = "");
	IL2CPP::IL2CPPField* FindField(IL2CPP::IL2CPPClass* classInstance, const char* fieldName, bool getInstance = false);
}