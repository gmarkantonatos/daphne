cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(tdms VERSION 1.0.0 LANGUAGES C)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Add the library source file
add_library(tdms_writer STATIC
    src/TDMS.c
)

# Specify the include directories for your TDMS library
target_include_directories(tdms_writer PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_options(tdms_writer PUBLIC -fPIC)

# Specify the installation rules for the library and headers
install(TARGETS tdms_writer EXPORT tdms_writerTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# Install the headers (TDMS.h and TDMS_config.h)
install(FILES include/TDMS.h include/TDMS_config.h DESTINATION include)

# Create export targets for the TDMS writer library
install(EXPORT tdms_writerTargets
    FILE tdms_writerTargets.cmake
    NAMESPACE tdms_writer::
    DESTINATION lib/cmake/tdms_writer
)

# Include the package config helpers
include(CMakePackageConfigHelpers)

# Generate a version file for compatibility checks
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/tdms_writerConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# Configure the package config file
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/tdms_writerConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/tdms_writerConfig.cmake"
    INSTALL_DESTINATION lib/cmake/tdms_writer
)

# Install the config and version files
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/tdms_writerConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/tdms_writerConfigVersion.cmake"
    DESTINATION lib/cmake/tdms_writer
)
