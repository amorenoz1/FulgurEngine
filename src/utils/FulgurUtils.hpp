#pragma once
#include "core/FulgurCore.hpp"
#include <cmath>
#include <string>
#include <unordered_set>
#include <vector>

namespace Utils
{
    auto GetFileExtension(const std::string &filepath) -> std::string FGAPI;
    auto GetFileName(const std::string &filepath) -> std::string FGAPI;
    auto GetDirectoryPath(const std::string &filepath) -> std::string FGAPI;
    auto CombinePaths(const std::string &filepath1, const std::string &filepath2)
        -> std::string FGAPI;
    auto       NormailzePath(const std::string &filepath) -> std::string FGAPI;
    auto       ReadFileToString(const std::string &filepath) -> std::string FGAPI;
    auto       FormatString(const std::string &format, ...) -> std::string FGAPI;
    auto       BytesToHumanReadble(std::size_t bytes) -> std::string FGAPI;
    auto       Split(const std::string &str, char delimeter) -> std::vector<std::string> FGAPI;
    auto       ReadBinaryFileToByteVector(const std::string &filepath) -> std::vector<char> FGAPI;
    auto       ParseInt(const std::string &str) -> std::int32_t FGAPI;
    auto       ParseFloat(const std::string &str) -> std::float_t FGAPI;
    void       WriteFileFromString(const std::string &filepath, const std::string &msg) FGAPI;
    void FGAPI ToLower(std::string &str);
    void FGAPI ToUpper(std::string &str);
    void FGAPI Trim(std::string &str);
    void FGAPI ReplaceAll(std::string &src, const std::string &from, const std::string &to);
    void FGAPI Assert(bool condition, const std::string &msg);
    void FGAPI Panic(const std::string &msg);
    void FGAPI Breakpoint();
    auto       FilePathExists(const std::string &filepath) -> bool FGAPI;
    auto       StartsWith(const std::string &str, const std::string &prefix) -> bool FGAPI;
    auto       EndsWith(const std::string &str, const std::string &suffix) -> bool FGAPI;

    template <typename T>
    void FGAPI RemoveDuplicates(std::vector<T> &vec)
    {
        std::unordered_set<T> seen;
        auto                  iter = vec.begin();

        while (iter != vec.end())
        {
            if (seen.find(*iter) != seen.end())
            {
                iter = vec.erase(iter);
            }
            else
            {
                seen.insert(*iter);
                ++iter;
            }
        }
    }

    template <typename T>
    auto Contains(std::vector<T> &vec, const T &value) -> bool FGAPI
    {
        return std::find(vec.begin(), vec.end(), value) != vec.end();
    }

    template <typename T>
    auto Contains(const std::vector<T> &vec, const T &value) -> bool FGAPI
    {
        return std::find(vec.begin(), vec.end(), value) != vec.end();
    }

} // namespace Utils
