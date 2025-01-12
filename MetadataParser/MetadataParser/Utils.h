#pragma once

namespace Utils
{
    bool ReadFile(const std::string& path, std::vector<uint8_t>& buffer);
    bool WriteFile(const std::string& path, const std::vector<uint8_t>& buffer);
}