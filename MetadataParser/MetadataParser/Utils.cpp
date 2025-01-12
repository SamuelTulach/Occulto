#include "Global.h"

bool Utils::ReadFile(const std::string& path, std::vector<uint8_t>& buffer)
{
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file.is_open())
        return false;

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    buffer.resize(size);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), size))
        return false;

    return true;
}

bool Utils::WriteFile(const std::string& path, const std::vector<uint8_t>& buffer)
{
    std::ofstream file(path, std::ios::binary);
    if (!file.is_open())
        return false;

    if (!file.write(reinterpret_cast<const char*>(buffer.data()), buffer.size()))
        return false;

    return true;
}