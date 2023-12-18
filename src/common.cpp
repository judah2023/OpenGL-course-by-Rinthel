#include "common.h"
#include "fstream"
#include "sstream"

std::optional<std::string> LoadTestFile(const std::string &filename)
{
    std::ifstream fin(filename);
    if(!fin.is_open())
    {
        SPDLOG_ERROR("Failed to open file : {}", filename);
        return {};
    }
    
    std::stringstream text;
    text << fin.rdbuf();
    return text.str();
}