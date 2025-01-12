#pragma once

namespace Metadata
{
    typedef struct _FieldDefinition
    {
        uint32_t NameIndex;
        uint32_t TypeIndex;
        uint32_t Token;
    } FieldDefinition;

    typedef struct _PropertyDefinition
    {
        uint32_t NameIndex;
        uint32_t Get;
        uint32_t Set;
        uint32_t Attrs;
        uint32_t Token;
    } PropertyDefinition;

    typedef struct _ParameterDefinition
    {
        uint32_t NameIndex;
        uint32_t Token;
        uint32_t TypeIndex;
    } ParameterDefinition;

    typedef struct _MethodDefinition
    {
        uint32_t NameIndex;
        uint32_t DeclaringType;
        uint32_t ReturnType;
        uint32_t ReturnParameterToken;
        uint32_t ParameterStart;
        uint32_t GenericContainerIndex;
        uint32_t Token;
        uint16_t Flags;
        uint16_t IFlags;
        uint16_t Slot;
        uint16_t ParameterCount;
    } MethodDefinition;

    typedef struct _TypeDefinition
    {
        uint32_t NameIndex;
        uint32_t NamespaceIndex;
        uint32_t ByvalTypeIndex;

        uint32_t DeclaringTypeIndex;
        uint32_t ParentIndex;
        uint32_t ElementTypeIndex;

        uint32_t GenericContainerIndex;

        uint32_t Flags;

        uint32_t FieldStart;
        uint32_t MethodStart;
        uint32_t EventStart;
        uint32_t PropertyStart;
        uint32_t NestedTypesStart;
        uint32_t InterfacesStart;
        uint32_t VtableStart;
        uint32_t InterfaceOffsetsStart;

        uint16_t MethodCount;
        uint16_t PropertyCount;
        uint16_t FieldCount;
        uint16_t EventCount;
        uint16_t NestedTypeCount;
        uint16_t VtableCount;
        uint16_t InterfacesCount;
        uint16_t InterfaceOffsetsCount;

        uint32_t Bitfield;
        uint32_t Token;
    } TypeDefinition;

#pragma pack(push, p1, 4)
    typedef struct _Header
    {
        uint32_t Sanity;
        uint32_t Version;
        uint32_t StringLiteralOffset;
        uint32_t StringLiteralSize;
        uint32_t StringLiteralDataOffset;
        uint32_t StringLiteralDataSize;
        uint32_t StringOffset;
        uint32_t StringSize;
        uint32_t EventsOffset;
        uint32_t EventsSize;
        uint32_t PropertiesOffset;
        uint32_t PropertiesSize;
        uint32_t MethodsOffset;
        uint32_t MethodsSize;
        uint32_t ParameterDefaultValuesOffset;
        uint32_t ParameterDefaultValuesSize;
        uint32_t FieldDefaultValuesOffset;
        uint32_t FieldDefaultValuesSize;
        uint32_t FieldAndParameterDefaultValueDataOffset;
        uint32_t FieldAndParameterDefaultValueDataSize;
        uint32_t FieldMarshaledSizesOffset;
        uint32_t FieldMarshaledSizesSize;
        uint32_t ParametersOffset;
        uint32_t ParametersSize;
        uint32_t FieldsOffset;
        uint32_t FieldsSize;
        uint32_t GenericParametersOffset;
        uint32_t GenericParametersSize;
        uint32_t GenericParameterConstraintsOffset;
        uint32_t GenericParameterConstraintsSize;
        uint32_t GenericContainersOffset;
        uint32_t GenericContainersSize;
        uint32_t NestedTypesOffset;
        uint32_t NestedTypesSize;
        uint32_t InterfacesOffset;
        uint32_t InterfacesSize;
        uint32_t VtableMethodsOffset;
        uint32_t VtableMethodsSize;
        uint32_t InterfaceOffsetsOffset;
        uint32_t InterfaceOffsetsSize;
        uint32_t TypeDefinitionsOffset;
        uint32_t TypeDefinitionsSize;
        uint32_t ImagesOffset;
        uint32_t ImagesSize;
        uint32_t AssembliesOffset;
        uint32_t AssembliesSize;
        uint32_t FieldRefsOffset;
        uint32_t FieldRefsSize;
        uint32_t ReferencedAssembliesOffset;
        uint32_t ReferencedAssembliesSize;
        uint32_t AttributeDataOffset;
        uint32_t AttributeDataSize;
        uint32_t AttributeDataRangeOffset;
        uint32_t AttributeDataRangeSize;
        uint32_t UnresolvedIndirectCallParameterTypesOffset;
        uint32_t UnresolvedIndirectCallParameterTypesSize;
        uint32_t UnresolvedIndirectCallParameterRangesOffset;
        uint32_t UnresolvedIndirectCallParameterRangesSize;
        uint32_t WindowsRuntimeTypeNamesOffset;
        uint32_t WindowsRuntimeTypeNamesSize;
        uint32_t WindowsRuntimeStringsOffset;
        uint32_t WindowsRuntimeStringsSize;
        uint32_t ExportedTypeDefinitionsOffset;
        uint32_t ExportedTypeDefinitionsSize;
    } Header;
#pragma pack(pop, p1)

    inline Header* header = nullptr;
    inline uint32_t typeCount = 0;

    template<typename T>
    inline T Offset(size_t sectionOffset, size_t itemIndex)
    {
        return reinterpret_cast<T>(reinterpret_cast<uint8_t*>(header) + sectionOffset) + itemIndex;
    }

    inline char* GetStringFromIndex(uint32_t index)
    {
        return Offset<char*>(header->StringOffset, index);
    }

    inline TypeDefinition* GetTypeDefinitionFromIndex(uint32_t index)
    {
        return Offset<TypeDefinition*>(header->TypeDefinitionsOffset, index);
    }

    inline ParameterDefinition* GetParameterDefinitionFromIndex(uint32_t index)
    {
        return Offset<ParameterDefinition*>(header->ParametersOffset, index);
    }

    inline MethodDefinition* GetMethodDefinitionFromIndex(uint32_t index)
    {
        return Offset<MethodDefinition*>(header->MethodsOffset, index);
    }

    inline PropertyDefinition* GetPropertyDefinitionFromIndex(uint32_t index)
    {
        return Offset<PropertyDefinition*>(header->PropertiesOffset, index);
    }

    inline FieldDefinition* GetFieldDefinitionFromIndex(uint32_t index)
    {
        return Offset<FieldDefinition*>(header->FieldsOffset, index);
    }

    bool IsInternalType(const std::string& name);

    void ModifyField(FieldDefinition* field);
    void ModifyParameter(ParameterDefinition* parameter);
    void ModifyMethod(MethodDefinition* method);
    void ModifyProperty(PropertyDefinition* property);
    void ModifyType(TypeDefinition* type);
    bool Process(std::vector<uint8_t>& buffer);
}