#include "command.h"
#include "ops.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <filesystem>
#include <fstream>

void CommandHandler::insert_template(const std::string &template_name, const std::vector<std::string> &files)
{

    auto template_dir = fs::path(std::getenv("USERPROFILE")) / "Documents" / "Sharpener" / "Templates" / template_name;

    if (fs::is_directory(template_dir))
    {
        std::cout << "Overwriting Template : " << template_name << std::endl;
    }
    else
    {
        std::cout << "Creating Template : " << template_name << std::endl;
        fs::create_directories(template_dir);
    }

    for (const auto &file : files)
    {
        fs::path source_file_path = fs::current_path() / file;
        fs::path new_file_path = template_dir / file;

        if (fs::exists(source_file_path))
        {
            // Normalize paths to prevent traversal outside the current directory
            fs::path normalized_source = fs::weakly_canonical(source_file_path);
            fs::path normalized_current = fs::weakly_canonical(fs::current_path());

            if (normalized_source.string().find(normalized_current.string()) != 0)
            {
                // If the file is outside the current directory, copy it to the parent folder
                new_file_path = template_dir / source_file_path.filename();
            }

            fs::create_directories(new_file_path.parent_path());
            fs::copy_file(source_file_path, new_file_path, fs::copy_options::overwrite_existing);
            std::cout << "Copied file: " << source_file_path << " to " << new_file_path << std::endl;
        }
        else
        {
            throw std::runtime_error("Source file does not exist: " + source_file_path.string());
        }
    }
}

void CommandHandler::use_template(const std::string &template_name)
{
    auto template_dir = fs::path(std::getenv("USERPROFILE")) / "Documents" / "Sharpener" / "Templates" / template_name;

    if (!fs::is_directory(template_dir))
    {
        throw std::runtime_error("Template directory does not exist: " + template_dir.string());
        return;
    }

    for (const auto &entry : fs::recursive_directory_iterator(template_dir))
    {
        if (fs::is_regular_file(entry))
        {
            fs::path relative_path = fs::relative(entry.path(), template_dir);
            fs::path destination_path = fs::current_path() / relative_path;

            fs::create_directories(destination_path.parent_path());
            fs::copy_file(entry.path(), destination_path, fs::copy_options::overwrite_existing);
            std::cout << "Created file: " << destination_path << std::endl;
        }
    }
}

void CommandHandler::show_file_info(const std::string &filename)
{
    if (!FileOps::file_exists(filename))
    {
        throw std::runtime_error("File does not exist: " + filename);
        return;
    }

    auto last_modified = FileOps::get_last_modified(filename);
    auto file_size = FileOps::get_file_size(filename);

    // Convert file time to system time
    std::time_t tt = std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now() - (fs::file_time_type::clock::now() - last_modified));

    // Display file information
    std::cout << "File: " << filename << std::endl;
    std::cout << "Size: " << file_size << " bytes" << std::endl;
    std::cout << "Last modified: " << std::put_time(std::localtime(&tt), "%Y-%m-%d %H:%M:%S") << std::endl;

    // Get file extension
    fs::path path(filename);
    if (path.has_extension())
    {
        std::cout << "Extension: " << path.extension().string().substr(1) << std::endl;
    }
    else
    {
        std::cout << "Extension: none" << std::endl;
    }

    // Show if the file is a directory, symlink, etc.
    if (fs::is_directory(filename))
    {
        std::cout << "Type: Directory" << std::endl;
    }
    else if (fs::is_symlink(filename))
    {
        std::cout << "Type: Symbolic Link" << std::endl;
    }
    else
    {
        std::cout << "Type: Regular File" << std::endl;
    }
}
