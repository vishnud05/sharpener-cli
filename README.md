# Sharpener CLI Tool

## Overview

Sharpener is an enhanced file utility tool for Windows that provides a variety of options to streamline file operations.

It allows users to create files, update timestamps, and read file contents directly in the terminal. One of its standout features is the ability to work with templates, enabling users to save or create templates and reuse them in their projects for improved efficiency.

## Installation

1. Download the installer from the [GitHub Releases](https://github.com/vishnud05/sharpener-cli/releases).
2. Run the installer and follow the on-screen instructions.
3. After installation, manually add the installation directory to your system PATH:
   - Open the Start Menu and search for "Environment Variables".
   - Click on "Edit the system environment variables".
   - In the System Properties window, click on "Environment Variables".
   - Under "System variables", find and select the `Path` variable, then click "Edit".
   - Click "New" and add the path (`C:\Program Files\Sharpener\bin`) to the Sharpener `bin` directory.
   - Click "OK" to save your changes.

## Usage

After adding the PATH variable, you can use the `sharp` command in your terminal. For example:

```bash
sharp --help
```

This will display the list of available commands and their usage.

## Contribution Guide

We welcome contributions! To contribute:

1. Fork the repository.
2. Clone your forked repository:
   ```bash
   git clone https://github.com/your-username/sharpener-cli.git
   ```
3. Create a new branch for your feature or bug fix:
   ```bash
   git checkout -b feature-name
   ```
4. Make your changes and commit them:
   ```bash
   git commit -m "Description of changes"
   ```
5. Push your changes to your fork:
   ```bash
   git push origin feature-name
   ```
6. Open a pull request to the main repository.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
