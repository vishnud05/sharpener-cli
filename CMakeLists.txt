cmake_minimum_required(VERSION 3.14)
project(Sharpener VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output binary name will be "sharp.exe"
add_executable(sharp
    src/main.cpp
    src/ops.cpp
    src/command.cpp
)

# Include directories
target_include_directories(sharp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Optional: Add version information to the executable
if(MSVC)
    target_compile_definitions(sharp PRIVATE
        "VERSION_MAJOR=${PROJECT_VERSION_MAJOR}"
        "VERSION_MINOR=${PROJECT_VERSION_MINOR}"
        "VERSION_PATCH=${PROJECT_VERSION_PATCH}"
    )
endif()

# Dependencies - example with CLI parsing library
include(FetchContent)
FetchContent_Declare(
    CLI11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.3.2
)
FetchContent_MakeAvailable(CLI11)
target_link_libraries(sharp PRIVATE CLI11::CLI11)

# Example of another useful library for file operations
FetchContent_Declare(
    filesystem
    GIT_REPOSITORY https://github.com/gulrak/filesystem.git
    GIT_TAG v1.5.14
)
FetchContent_MakeAvailable(filesystem)
target_link_libraries(sharp PRIVATE ghc_filesystem)

# Installation
install(TARGETS sharp
    RUNTIME DESTINATION bin
)

# Package configuration (for creating installers)
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VENDOR "Your Company")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Enhanced file touch utility for Windows")

# Add these before include(CPack)
set(CPACK_GENERATOR "NSIS")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Sharpener")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")


include(CPack)


