#include <iostream>
#include <string>
#include <command.h>
#include <CLI/CLI.hpp>
#include "ops.h"
#include <filesystem>

int main(int argc, char **argv)
{
    CLI::App app{"Sharpener - Enhanced File Utility for Windows"};
    app.set_version_flag("--version", std::string("Sharpener CLI v") +
                                          std::to_string(VERSION_MAJOR) + "." +
                                          std::to_string(VERSION_MINOR) + "." +
                                          std::to_string(VERSION_PATCH));

    // Template Subcommand
    CLI::App *template_subcommand = app.add_subcommand("temp", "Create a template file with a specific name");
    std::string template_name;
    template_subcommand->add_option("name", template_name, "Template name")->required();
    CLI::App *template_mode_group = template_subcommand->add_option_group("Template Mode", "Template options");
    bool use_template = false;
    bool insert_template = false;
    template_mode_group->add_flag("-i,--insert", insert_template, "Create or overwrite the template");
    template_mode_group->add_flag("-u,--use", use_template, "Use the template");
    template_mode_group->require_option(1);

    // Info Subcommand
    CLI::App *info_subcommand = app.add_subcommand("info", "Show file information");
    std::string info_filename;
    info_subcommand->add_option("filename", info_filename, "File name")->required();

    std::vector<std::string> files;
    template_subcommand->add_option("files", files);
    app.add_option("files", files, "Files to create or update");

    CLI::App *mode_group = app.add_option_group("Modes", "File creation and modification modes");
    bool create_only = false;
    bool read_only = false;
    bool recursive = false;
    mode_group->add_flag("-c,--create-only", create_only, "Create files if they don't exist");
    mode_group->add_flag("-r,--read-only", read_only, "Print file contents (no file creation or modification)");

    try
    {
        app.parse(argc, argv);

        if (template_subcommand->parsed())
        {

            if (insert_template)
            {
                CommandHandler::insert_template(template_name, files);
                        }
            else if (use_template)
            {
                CommandHandler::use_template(template_name);
            }
            else
            {
                std::cerr << "Invalid template command. Use --insert or --use." << std::endl;
                return 1;
            }

            return 0;
        }

        if (info_subcommand->parsed())
        {
            CommandHandler::show_file_info(info_filename);
            return 0;
        }

        if (read_only)
        {
            for (const auto &file : files)
            {
                std::cout << "-------" << "Reading file: " << file << "-------\n"
                          << std::endl;
                FileOps::read_file_content(file);
                std::cout << "------- " << "File Size : " << FileOps::get_file_size(file) << "Bytes -------\n"
                          << std::endl;
            }
            return 0;
        }

        for (const auto &file : files)
        {

            bool has_folders = file.find('\\') != std::string::npos || file.find('/') != std::string::npos;
            if (has_folders)
            {
                recursive = true;
            }

            FileOps::create_file_timestamp(file, create_only, recursive);
            std::cout << "Processed: " << file << std::endl;
        }
    }
    catch (const CLI::ParseError &e)
    {
        std::cerr << "CLI parsing error: " << e.what() << std::endl;
        return app.exit(e);
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Runtime error: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown error occurred." << std::endl;
        return 1;
    }

    return 0;
}
