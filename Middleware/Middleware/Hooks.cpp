#include "Global.h"

EXTERN_C DLL_EXPORT PVOID il2cpp_class_from_name(const PVOID image, const char* namespaze, const char* name)
{
    static PVOID(*target_func)(const PVOID, const char*, const char*) = nullptr;
    if (!target_func)
        target_func = reinterpret_cast<PVOID(*)(const PVOID, const char*, const char*)>(GetProcAddress(Global::GameAssembly, "il2cpp_class_from_name"));

    Console::Print("il2cpp_class_from_name(): %s.%s", namespaze, name);

    PVOID result = target_func(image, namespaze, name);
    if (result)
        return result;

    const size_t s1 = strlen(namespaze);
    const size_t s2 = strlen(name);

    char t1[256];
    char t2[256];

    if (s1 >= sizeof(t1) || s2 >= sizeof(t2))
    {
        Console::Print("Buffer too small");
        return result;
    }

    memcpy(t1, namespaze, s1 + 1);
    memcpy(t2, name, s2 + 1);

    //Hash::Run(t1, s1);
    Hash::Run(t2, s2);

    Console::Print("-> %s.%s", t1, t2);

    result = target_func(image, t1, t2);

    Console::Print("-> 0x%p", result);

    return result;
}

EXTERN_C DLL_EXPORT PVOID il2cpp_class_get_property_from_name(PVOID klass, const char* name)
{
    static PVOID(*target_func)(PVOID klass, const char* name) = nullptr;
    if (!target_func)
        target_func = reinterpret_cast<PVOID(*)(PVOID klass, const char* name)>(GetProcAddress(Global::GameAssembly, "il2cpp_class_get_property_from_name"));

    Console::Print("il2cpp_class_get_property_from_name(): %s", name);

    return target_func(klass, name);
}

EXTERN_C DLL_EXPORT PVOID il2cpp_class_get_field_from_name(PVOID klass, const char* name)
{
    static PVOID(*target_func)(PVOID klass, const char* name) = nullptr;
    if (!target_func)
        target_func = reinterpret_cast<PVOID(*)(PVOID klass, const char* name)>(GetProcAddress(Global::GameAssembly, "il2cpp_class_get_field_from_name"));

    Console::Print("il2cpp_class_get_field_from_name(): %s", name);

    return target_func(klass, name);
}

EXTERN_C DLL_EXPORT PVOID il2cpp_class_get_method_from_name(PVOID klass, const char* name, int argsCount)
{
    static PVOID(*target_func)(PVOID klass, const char* name, int argsCount) = nullptr;
    if (!target_func)
        target_func = reinterpret_cast<PVOID(*)(PVOID klass, const char* name, int argsCount)>(GetProcAddress(Global::GameAssembly, "il2cpp_class_get_method_from_name"));

    Console::Print("il2cpp_class_get_method_from_name(): %s", name);

    return target_func(klass, name, argsCount);
}