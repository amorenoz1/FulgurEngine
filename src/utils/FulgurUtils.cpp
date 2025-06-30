#include "FulgurUtils.hpp"
#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

std::string Utils::GetFileExtension(const std::string& filepath) {
    std::filesystem::path p(filepath);
    std::filesystem::path extension = p.extension();
    return p.c_str();
}

std::string Utils::GetFileName(const std::string& filepath) {
    std::filesystem::path p(filepath);
    std::filesystem::path extension = p.filename();
    return p.c_str();
}

std::string Utils::GetDirectoryPath(const std::string& filepath) {
    std::filesystem::path p(filepath);
    std::filesystem::path extension = p.parent_path();
    return p.c_str();
}

std::string Utils::CombinePaths(const std::string& filepath1, const std::string& filepath2) {
    std::filesystem::path p(filepath1);
    p.concat(filepath2);
    return p.c_str();
}

std::string Utils::NormailzePath(const std::string& filepath) {
    std::vector<std::string> subdivisions = Utils::Split(filepath, '/');
    std::vector<std::string> normalization;

    for (std::string str : subdivisions) {
        if (std::strncmp(str.c_str(), "..", str.length()) == 0) {
            if (!normalization.empty()) {
                normalization.pop_back();
            }
        } else if (std::strncmp(str.c_str(), ".", str.length()) == 0 || str.empty()) {
            continue;
        } else {
            normalization.push_back(str);
        }
    }

    std::stringstream result;

    if (filepath.starts_with('/')) {
        result << "/";
    }

    for (std::string str : normalization) {
        result << str << "/";
    }

    return result.str();
}

std::string Utils::ReadFileToString(const std::string& filepath) {
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cout << "File " << filepath << "failed to open" << std::endl;
        return "";
    }

    std::stringstream result;
    std::string line;

    while (std::getline(file, line)) {
        result << line;
    }

    file.close();

    return result.str();
}

std::vector<char> Utils::ReadBinaryFileToByteVector(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary | std::ios::ate);
    if (!file.is_open())
        return {};

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);
    if (!file.read(buffer.data(), size)) {
        return {}; // Failed to read entire file
    }

    return buffer;
}

void Utils::WriteFileFromString(const std::string& filepath, const std::string& msg) {
    std::ofstream file(filepath);
    if (file.is_open()) {
        file << msg;
    }
}

bool Utils::FilePathExists(const std::string& filepath) {
    return std::filesystem::exists(filepath);
}

std::string Utils::FormatString(const std::string& format, ...) {
    std::va_list args, args_copy;
    va_start(args, &format);
    va_copy(args_copy, args);

    std::size_t size = std::vsnprintf(nullptr, 0, format.c_str(), args_copy);
    va_end(args_copy);

    if (size < 0) {
        return "";
    }

    std::vector<char> buffer(size + 1);
    std::vsnprintf(buffer.data(), buffer.size(), format.c_str(), args);
    va_end(args);

    return std::string(buffer.data());
}

std::vector<std::string> Utils::Split(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream sub_div;

    for (char ch : str) {
        if (ch == delimiter) {
            result.push_back(sub_div.str());
            sub_div.str(""); // reset content
            sub_div.clear(); // reset flags
        } else {
            sub_div << ch;
        }
    }

    result.push_back(sub_div.str()); // flush last part
    return result;
}

void Utils::ToLower(std::string& str) {
    for (std::size_t i = 0; i < str.length(); i++) {
        if (str.at(i) >= 'A' && str.at(i) <= 'Z') {
            str.at(i) = str.at(i) + 32;
        }
    }
}

void Utils::ToUpper(std::string& str) {
    for (std::size_t i = 0; i < str.length(); i++) {
        if (str.at(i) >= 'a' && str.at(i) <= 'a') {
            str.at(i) = str.at(i) - 32;
        }
    }
}

void Utils::Trim(std::string& str) {
    std::stringstream result;
    bool in_space = false;
    std::size_t start = str.find_first_not_of(" \t\n\r");
    std::size_t end = str.find_last_not_of(" \t\n\r");

    if (start == std::string::npos) {
        str.clear(); // string is all whitespace
        return;
    }

    for (std::size_t i = start; i <= end; ++i) {
        char c = str.at(i);
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            if (!in_space) {
                result << ' ';
                in_space = true;
            }
        } else {
            result << c;
            in_space = false;
        }
    }

    str = result.str();
}

void Utils::ReplaceAll(std::string& src, const std::string& from, const std::string& to) {
    std::stringstream ss;

    for (std::size_t i = 0; i < src.length() - from.length(); i++) {
        std::string str_window = src.substr(i, from.length() - 1 + i);

        if (str_window == from) {
            ss << to;
        } else {
            ss << str_window;
        }
    }
}

bool Utils::StartsWith(const std::string& str, const std::string& prefix) {
    return str.starts_with(prefix);
}

bool Utils::EndsWith(const std::string& str, const std::string& suffix) {
    return str.ends_with(suffix);
}

std::string Utils::BytesToHumanReadble(std::size_t bytes) {
    std::double_t bytes_double = static_cast<std::double_t>(bytes);
    std::size_t iterations = 0;

    while (bytes_double / 1000 > 0) {
        bytes_double /= 1000;
        iterations++;
    }

    std::stringstream ss;

    switch (iterations) {
    case 0:
        ss << bytes_double << " Bytes";
        break;
    case 1:
        ss << bytes_double << " Kb";
        break;
    case 2:
        ss << bytes_double << " Mb";
        break;
    case 3:
        ss << bytes_double << " Gb";
        break;
    case 4:
        ss << bytes_double << " Tb";
        break;
    default:
        ss << bytes_double << " Pb";
        break;
    }

    return ss.str();
}

void Utils::Assert(bool condition, const std::string& msg) {
    if (!condition) {
        std::cout << msg << std::endl;
        std::flush(std::cout);
        std::exit(-1);
    }
}

void Utils::Panic(const std::string msg) {
    std::cout << msg << std::endl;
    std::flush(std::cout);
    std::exit(-1);
}

void Utils::Breakpoint() {
#if defined(_MSC_VER)
    __debugbreak();
#elif defined(__GNUC__) || defined(__clang__)
    __builtin_trap();
#else
    std::abort();
#endif
}

std::int32_t Utils::ParseInt(const std::string& str) {
    try {
        return std::stoi(str);
    } catch (const std::exception& e) {
        return 0;
    }
}

std::float_t Utils::ParseFloat(const std::string& str) {
    try {
        return std::stof(str);
    } catch (const std::exception& e) {
        return 0.0f;
    }
}
