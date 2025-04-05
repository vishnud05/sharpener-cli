#include "ops.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <ctime>

void FileOps::create_file_timestamp(const std::string &filename, bool create_only, bool recursive)
{

    if (create_only && file_exists(filename))
    {
        throw std::runtime_error("File already exists: " + filename);
        return;
    }

    if (file_exists(filename))
    {
        // File exists, update timestamp
        fs::file_time_type now = fs::file_time_type::clock::now();
        fs::last_write_time(filename, now);
    }
    else
    {

        if (recursive)
        {
            fs::path path(filename);
            if (path.has_parent_path())
            {
                create_directories(path.parent_path().string());
            }
        }

        // Create the file
        std::ofstream file(filename);

        if (!file.is_open())
        {
            throw std::ios_base::failure("Failed to create file: " + filename);
        }
        file.close();
    }
}

fs::file_time_type FileOps::get_last_modified(const std::string &filename)
{
    if (!file_exists(filename))
    {
        throw std::runtime_error("File does not exist: " + filename);
    }
    return fs::last_write_time(filename);
}

uintmax_t FileOps::get_file_size(const std::string &filename)
{
    if (!file_exists(filename))
    {
        throw std::runtime_error("File does not exist: " + filename);
        return 0;
    }
    return fs::file_size(filename);
}

bool FileOps::file_exists(const std::string &filename)
{
    return fs::exists(filename);
}

void FileOps::create_directories(const std::string &path)
{
    fs::create_directories(path);
}

void FileOps::read_file_content(const std::string &filename)
{
    if (!file_exists(filename))
    {
        throw std::runtime_error("File does not exist: " + filename);
        return;
    }

    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::ios_base::failure("Failed to open file for writing: " + filename);
        return;
    }

    std::string line;
    int line_number = 1;
    while (std::getline(file, line))
    {
        std::cout << line_number++ << " " << line << std::endl;
    }
}

void FileOps::write_file_content(const std::string &filename, const std::string &content)
{
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        throw std::ios_base::failure("Failed to open file for writing: " + filename);
    }

    file.write(content.c_str(), content.size());
}

void FileOps::append_file_content(const std::string &filename, const std::string &content)
{
    std::ofstream file(filename, std::ios::binary | std::ios::app);
    if (!file.is_open())
    {
        throw std::ios_base::failure("Failed to open file for appending: " + filename);
    }

    file.write(content.c_str(), content.size());
}
