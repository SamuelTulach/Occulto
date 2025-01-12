#pragma once

namespace Config
{
    bool Read(const std::string& path);
    bool ShouldProtect(const std::string& name);
}