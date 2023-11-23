#include "Dissector.hpp"

#include <iostream>

void Dissector::Attach() {
	GetExport(IL2CPP::GetDomain, "il2cpp_domain_get");
	GetExport(IL2CPP::GetAssemblies, "il2cpp_domain_get_assemblies");
	GetExport(IL2CPP::GetAssemblyImage, "il2cpp_assembly_get_image");
	GetExport(IL2CPP::GetClassFromName, "il2cpp_class_from_name");
	GetExport(IL2CPP::GetClassMethods, "il2cpp_class_get_methods");
	GetExport(IL2CPP::GetMethodName, "il2cpp_method_get_name");
	GetExport(IL2CPP::GetMethodParamCount, "il2cpp_method_get_param_count");
	GetExport(IL2CPP::GetClassFields, "il2cpp_class_get_fields");
	GetExport(IL2CPP::GetFieldOffset, "il2cpp_field_get_offset");
	GetExport(IL2CPP::CreateNewString, "il2cpp_string_new");
	GetExport(IL2CPP::CreateNewObject, "il2cpp_object_new");
	GetExport(IL2CPP::GetMethodReturnType, "il2cpp_method_get_return_type");
	GetExport(IL2CPP::GetClassType, "il2cpp_class_get_type");
	GetExport(IL2CPP::GetTypeName, "il2cpp_type_get_name");
	GetExport(IL2CPP::GetTypeObject, "il2cpp_type_get_object");
}

void* Dissector::GetClassTypeObject(const char* namespaceName, const char* className) {
	IL2CPP::IL2CPPClass* classInstance = FindClass(namespaceName, className);
	if (!classInstance)
		return nullptr;

	void* classType = IL2CPP::GetClassType(classInstance);
	if (!classType)
		return nullptr;

	void* classTypeObject = IL2CPP::GetTypeObject(classType);
	if (!classTypeObject)
		return nullptr;

	return classTypeObject;
}

/* you can dump nested classes ex. BaseProjectile.Magazine by doing this BaseProjectile/Magazine as className */
Dissector::IL2CPP::IL2CPPClass* Dissector::FindClass(const char* namespaceName, const char* className) {
	void* domain = IL2CPP::GetDomain();
	if (!domain)
		return nullptr;

	size_t assemblyCount = 0;
	void** gameAssemblies = IL2CPP::GetAssemblies(domain, &assemblyCount);
	if (!gameAssemblies)
		return nullptr;

	IL2CPP::IL2CPPClass* classInstance = nullptr;
	for (int assemblyIndex = 0; assemblyIndex < assemblyCount; ++assemblyIndex) {
		void* currentAssembly = gameAssemblies[assemblyIndex];
		if (!currentAssembly)
			continue;

		void* assemblyImage = IL2CPP::GetAssemblyImage(currentAssembly);
		if (!assemblyImage)
			continue;

		IL2CPP::IL2CPPClass* imageClassInstance = IL2CPP::GetClassFromName(assemblyImage, namespaceName, className);
		if (!imageClassInstance)
			continue;

		classInstance = imageClassInstance;
		break; /* break the loop after we got the instance */
	}

	if (classInstance) {
		printf("found \"%s::%s[0x%p]\"\n", namespaceName, className, classInstance);
	}

	return classInstance; /* will return nullptr if not set */
}

Dissector::IL2CPP::IL2CPPMethod* Dissector::FindMethod(IL2CPP::IL2CPPClass* classInstance, const char* methodName, int argCount, const char* returnType) {
	if (!classInstance)
		return nullptr;

	uintptr_t methodIterator = 0;
	IL2CPP::IL2CPPMethod* methodInstance = nullptr;
	while (IL2CPP::IL2CPPMethod* currentMethod = IL2CPP::GetClassMethods(classInstance, &methodIterator)) { /* this will reset itself to the next iteration on every loop */
		if (!currentMethod)
			continue;

		const char* currentMethodName = IL2CPP::GetMethodName(currentMethod);
		if (strcmp(currentMethodName, methodName))
			continue;

		int currentMethodParamCount = IL2CPP::GetMethodParamCount(currentMethod);
		if (argCount != -1 && currentMethodParamCount != argCount)
			continue;

		void* currentMethodReturnType = IL2CPP::GetMethodReturnType(currentMethod);
		if (!currentMethodReturnType)
			continue;

		const char* returnTypeName = IL2CPP::GetTypeName(currentMethodReturnType);
		if (strlen(returnType) > 0 && strcmp(returnType, returnTypeName))
			continue;

		printf("found \"%s[0x%p]\" with \"%i\" argument/s and return type \"%s\"\n", currentMethodName, currentMethod->methodPtr, currentMethodParamCount, returnTypeName);
		methodInstance = currentMethod;
		break; /* break the loop after we got the instance */
	}

	return methodInstance; /* will return nullptr if not set */
}

Dissector::IL2CPP::IL2CPPField* Dissector::FindField(IL2CPP::IL2CPPClass* classInstance, const char* fieldName, bool getInstance) {
	if (!classInstance)
		return nullptr;

	uintptr_t fieldIterator = 0;
	IL2CPP::IL2CPPField* fieldInstance = nullptr;
	while (IL2CPP::IL2CPPField* currentField = IL2CPP::GetClassFields(classInstance, &fieldIterator)) { /* this will reset itself to the next iteration on every loop */
		const char* currentFieldName = *reinterpret_cast<const char**>(currentField);
		if (strcmp(currentFieldName, fieldName))
			continue;

		fieldInstance = reinterpret_cast<IL2CPP::IL2CPPField*>(*reinterpret_cast<uintptr_t*>((uintptr_t)classInstance + 0xB8) + IL2CPP::GetFieldOffset(currentField));
		if (getInstance)
			break;

		fieldInstance = (IL2CPP::IL2CPPField*)IL2CPP::GetFieldOffset(currentField);
		break;
	}

	if (fieldInstance) {
		printf("found \"%s[0x%p]\"\n", fieldName, fieldInstance);
	}

	return fieldInstance;
}