#include "Global.h"

void OnDllAttach()
{
    Console::Init();
    Console::Print("Loading module...");
    Global::GameAssembly = LoadLibraryA("GameAssembly.Real.dll");
    if (!Global::GameAssembly || Global::GameAssembly == INVALID_HANDLE_VALUE)
    {
        Console::Print("Failed to load module");
        return;
    }

    Console::Print("Module loaded at 0x%p", Global::GameAssembly);
}

void OnDllDetach()
{
    Console::Print("Unloading module...");
    if (Global::GameAssembly)
        FreeLibrary(Global::GameAssembly);
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
    UNREFERENCED_PARAMETER(reserved);

    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(module);
        OnDllAttach();
    }
    else if (reason == DLL_PROCESS_DETACH)
        OnDllDetach();

    return TRUE;
}

