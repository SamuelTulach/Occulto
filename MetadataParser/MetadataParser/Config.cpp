#include "Global.h"

static std::unordered_set<std::string> targetNames;

bool Config::Read(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
        return false;

    std::string line;
    while (std::getline(file, line))
        targetNames.insert(line);

    file.close();
    return true;
}

bool Config::ShouldProtect(const std::string& name)
{
    return targetNames.find(name) != targetNames.end();
}
