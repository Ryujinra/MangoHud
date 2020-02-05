#pragma once
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include <dirent.h>
#include <algorithm> 
#include <cctype>
#include <locale>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

// https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring#217605
// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

static bool starts_with(const std::string& s,  const char *t) {
    return s.rfind(t, 0) == 0;
}

template<typename T>
static std::string itox(T i) {
    std::stringstream ss;
    ss << "0x" 
        << std::setfill ('0') << std::setw(sizeof(T) * 2) 
        << std::hex << i;
    return ss.str();
}

static std::string read_line(const std::string& filename)
{
    std::string line;
    std::ifstream file(filename);
    std::getline(file, line);
    return line;
}

static bool find_folder(const char* root, const char* prefix, std::string& dest)
{
    struct dirent* dp;
    DIR* dirp = opendir(root);
    if (!dirp) {
        std::cerr << "Error opening directory '" << root << "': ";
        perror("");
        return false;
    }

    while ((dp = readdir(dirp))) {
        if (dp->d_type == DT_DIR && starts_with(dp->d_name, prefix)) {
            dest = dp->d_name;
            closedir(dirp);
            return true;
        }
    }

    closedir(dirp);
    return false;
}

static std::vector<std::string> ls(const char* root, int d_type = DT_DIR)
{
    std::vector<std::string> list;
    struct dirent* dp;

    DIR* dirp = opendir(root);
    if (!dirp) {
        std::cerr << "Error opening directory '" << root << "': ";
        perror("");
        return list;
    }

    while ((dp = readdir(dirp))) {
        if (dp->d_type == d_type)
            list.push_back(dp->d_name);
    }

    closedir(dirp);
    return list;
}

#pragma GCC diagnostic pop
