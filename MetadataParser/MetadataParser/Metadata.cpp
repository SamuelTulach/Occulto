#include "Global.h"

bool Metadata::IsInternalType(const std::string& name)
{
    static std::unordered_set<std::string> list =
    {
        "Object", "Void", "Boolean", "Byte", "SByte", "Int16", "UInt16", "Int32", "UInt32", "UIntPtr",
        "IntPtr", "Int64", "UInt64", "Single", "Double", "Char", "String", "Enum", "Array", "ValueType",
        "Delegate", "MulticastDelegate", "AsyncResult", "MonoAsyncCall", "ManualResetEvent", "Type",
        "MonoType", "Thread", "InternalThread", "RuntimeType", "AppDomain", "AppDomainSetup", "MemberInfo",
        "FieldInfo", "MethodInfo", "PropertyInfo", "EventInfo", "StringBuilder", "StackFrame", "StackTrace",
        "TypedReference", "IList`1", "ICollection`1", "IEnumerable`1", "IReadOnlyList`1", "IReadOnlyCollection`1",
        "Nullable`1", "Version", "CultureInfo", "RuntimeAssembly", "AssemblyName", "RuntimeParameterInfo",
        "RuntimeModule", "Exception", "SystemException", "ArgumentException", "MarshalByRefObject", "__Il2CppComObject",
        "SafeHandle", "SortKey", "DBNull", "ErrorWrapper", "Missing", "Attribute", "CustomAttributeData",
        "CustomAttributeTypedArgument", "CustomAttributeNamedArgument", "KeyValuePair`2", "Guid", "_ThreadPoolWaitCallback",
        "MonoMethodMessage", "SByteEnum", "Int16Enum", "Int32Enum", "Int64Enum", "ByteEnum", "UInt16Enum",
        "UInt32Enum", "UInt64Enum", "__Il2CppFullySharedGenericType", "__Il2CppFullySharedGenericStructType", "GetHashCode",
        "Finalize", "Empty", "AudioSource", "Awake", "Start", "OnEnable", "OnDisable", "Update", "FixedUpdate",
        "LateUpdate", "OnDestroy", "OnApplicationQuit", "OnApplicationPause", "OnApplicationFocus", "OnGUI",
        "OnRenderObject", "OnWillRenderObject", "OnPreCull", "OnPreRender", "OnPostRender", "OnBecameVisible",
        "OnBecameInvisible", "OnCollisionEnter", "OnCollisionStay", "OnCollisionExit", "OnTriggerEnter", "OnTriggerStay",
        "OnTriggerExit", "OnMouseDown", "OnMouseUp", "OnMouseDrag", "OnMouseEnter", "OnMouseOver", "OnMouseExit",
        "OnLevelWasLoaded", "OnSceneLoaded", "OnSceneUnloaded", "OnAudioFilterRead", "OnAnimatorMove", "OnAnimatorIK",
        "OnControllerColliderHit", "Reset", "OnValidate", "OnServerInitialized", "OnConnectedToServer", "OnDisconnectedFromServer"
    };

    return list.find(name) != list.end();
}

void Metadata::ModifyField(FieldDefinition* field)
{
    char* namePtr = GetStringFromIndex(field->NameIndex);
    std::string name(namePtr);

    if (IsInternalType(name))
        return;

    Hash::Run(namePtr, strlen(namePtr));

    printf(" - [field] %s => %s\n", name.c_str(), namePtr);
}

void Metadata::ModifyParameter(ParameterDefinition* parameter)
{
    char* namePtr = GetStringFromIndex(parameter->NameIndex);
    std::string name(namePtr);

    if (IsInternalType(name))
        return;

    Hash::Run(namePtr, strlen(namePtr));

    printf(" - [param] %s => %s\n", name.c_str(), namePtr);
}

void Metadata::ModifyProperty(PropertyDefinition* property)
{
    char* namePtr = GetStringFromIndex(property->NameIndex);
    std::string name(namePtr);

    if (IsInternalType(name))
        return;

    Hash::Run(namePtr, strlen(namePtr));

    printf(" - [prop] %s => %s\n", name.c_str(), namePtr);
}

void Metadata::ModifyMethod(MethodDefinition* method)
{
    char* namePtr = GetStringFromIndex(method->NameIndex);
    std::string name(namePtr);

    if (IsInternalType(name))
        return;

    if (name.find('.') != std::string::npos)
        return;

    Hash::Run(namePtr, strlen(namePtr));

    printf(" - [method] %s() => %s()\n", name.c_str(), namePtr);

    for (uint32_t i = 0; i < method->ParameterCount; i++)
    {
        ParameterDefinition* parameter = GetParameterDefinitionFromIndex(method->ParameterStart + i);
        ModifyParameter(parameter);
    }
}

void Metadata::ModifyType(TypeDefinition* type)
{
    char* namePtr = GetStringFromIndex(type->NameIndex);
    std::string name(namePtr);

    if (IsInternalType(name))
        return;

    if (!Config::ShouldProtect(namePtr))
        return;

    Hash::Run(namePtr, strlen(namePtr));
    printf("%s => %s\n", name.c_str(), namePtr);

    for (uint32_t i = 0; i < type->FieldCount; i++)
    {
        FieldDefinition* field = GetFieldDefinitionFromIndex(type->FieldStart + i);
        ModifyField(field);
    }

    for (uint32_t i = 0; i < type->MethodCount; i++)
    {
        MethodDefinition* method = GetMethodDefinitionFromIndex(type->MethodStart + i);
        ModifyMethod(method);
    }

    for (uint32_t i = 0; i < type->PropertyCount; i++)
    {
        PropertyDefinition* property = GetPropertyDefinitionFromIndex(type->PropertyStart + i);
        ModifyProperty(property);
    }
}

bool Metadata::Process(std::vector<uint8_t>& buffer)
{
    header = reinterpret_cast<Header*>(buffer.data());
    if (header->Sanity != 0xFAB11BAF)
        return false;

    printf("Version: %u\n", header->Version);

    typeCount = header->TypeDefinitionsSize / sizeof(TypeDefinition);
    printf("Types: %u\n", typeCount);

    for (uint32_t i = 0; i < typeCount; i++)
    {
        TypeDefinition* type = GetTypeDefinitionFromIndex(i);
        ModifyType(type);
    }

    return true;
}
