#include "FileUtils.h"
#include "Log/Log.h"

#include <fstream>
#include <sstream>

using namespace DarrJorge;

DEFINE_LOG_CATEGORY_STATIC(LogFileUtils);

std::string FileUtils::readTextFile(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        LOG(LogFileUtils, Error, "Failed to open file: {}", path);
        return {};
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
