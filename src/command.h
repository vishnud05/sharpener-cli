#pragma once

#include <string>
#include <map>
#include <vector>

class CommandHandler
{
public:
    // Create a file from template
    static void insert_template(const std::string &template_name, const std::vector<std::string> &files);

    // Show detailed file information
    static void show_file_info(const std::string &filename);

    // Use a template to create files
    static void use_template(const std::string &template_name);
};
