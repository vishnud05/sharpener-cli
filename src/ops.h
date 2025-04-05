#pragma once

#include <string>
#include <chrono>
#include <ghc/filesystem.hpp>
namespace fs = ghc::filesystem;

class FileOps
{
public:
    // Touch a file - create it if it doesn't exist and/or update its timestamp
    static void create_file_timestamp(const std::string &filename,
                                      bool create_missing = true,
                                      bool recursive = false);

    // Get file metadata
    static fs::file_time_type get_last_modified(const std::string &filename);
    static uintmax_t get_file_size(const std::string &filename);
    static bool file_exists(const std::string &filename);

    // Create directory structure
    static void create_directories(const std::string &path);

    // File content operations
    static void read_file_content(const std::string &filename);
    static void write_file_content(const std::string &filename, const std::string &content);
    static void append_file_content(const std::string &filename, const std::string &content);
};
