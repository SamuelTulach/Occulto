#pragma once

#define DLL_EXPORT __declspec(dllexport)

#define DEFINE_PASSTHROUGH_FUNCTION(return_type, func_name, arg_types, arg_names)        \
    EXTERN_C DLL_EXPORT return_type func_name arg_types                                  \
    {                                                                                    \
        static return_type (*target_func) arg_types = nullptr;                           \
        if (!target_func)                                                                \
        {                                                                                \
            target_func = reinterpret_cast<return_type (*) arg_types>(                   \
                GetProcAddress(Global::GameAssembly, #func_name));                       \
            if (!target_func)                                                            \
            {                                                                            \
                Console::Print("Failed to resolve %s()", #func_name);                   \
                return return_type();                                                   \
            }                                                                            \
        }                                                                                \
        /*Console::Print("%s() -> 0x%p", #func_name, &target_func);   */                     \
        return target_func arg_names;                                                    \
    }
