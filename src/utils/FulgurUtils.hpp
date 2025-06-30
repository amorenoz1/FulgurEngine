#pragma once
#include <cmath>
#include <string>
#include <unordered_set>
#include <vector>

namespace Utils {
std::string GetFileExtension(const std::string& filepath);
std::string GetFileName(const std::string& filepath);
std::string GetDirectoryPath(const std::string& filepath);
std::string CombinePaths(const std::string& filepath1, const std::string& filepath2);
std::string NormailzePath(const std::string& filepath);
std::string ReadFileToString(const std::string& filepath);
std::string FormatString(const std::string& format, ...);
std::string BytesToHumanReadble(std::size_t bytes);
std::vector<std::string> Split(const std::string& str, char delimeter);
std::vector<char> ReadBinaryFileToByteVector(const std::string& filepath);
std::int32_t ParseInt(const std::string& str);
std::float_t ParseFloat(const std::string& str);
void WriteFileFromString(const std::string& filepath, const std::string& msg);
void ToLower(std::string& str);
void ToUpper(std::string& str);
void Trim(std::string& str);
void ReplaceAll(std::string& src, const std::string& from, const std::string& to);
void Assert(bool condition, const std::string& msg);
void Panic(const std::string msg);
void Breakpoint();
bool FilePathExists(const std::string& filepath);
bool StartsWith(const std::string& str, const std::string& prefix);
bool EndsWith(const std::string& str, const std::string& suffix);

template <typename T> void RemoveDuplicates(std::vector<T>& vec) {
    std::unordered_set<T> seen;
    auto it = vec.begin();

    while (it != vec.end()) {
        if (seen.find(*it) != seen.end()) {
            it = vec.erase(it);
        } else {
            seen.insert(*it);
            ++it;
        }
    }
}

template <typename T> bool Contains(std::vector<T>& vec, const T& value) {
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}

template <typename T> bool Contains(const std::vector<T>& vec, const T& value) {
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}

} // namespace Utils
