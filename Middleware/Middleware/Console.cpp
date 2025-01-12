#include "Global.h"

void Console::Init()
{
    AllocConsole();
    FILE* file;
    freopen_s(&file, "CONOUT$", "w", stdout);
    freopen_s(&file, "CONOUT$", "w", stderr);
    freopen_s(&file, "CONIN$", "r", stdin);
}

void Console::Print(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    const int length = vsnprintf(nullptr, 0, format, args) + 1;
    va_end(args);

    char* message = new char[length];

    va_start(args, format);
    vsnprintf(message, length, format, args);
    va_end(args);

    printf("[MW] %s\n", message);

    delete[] message;
}