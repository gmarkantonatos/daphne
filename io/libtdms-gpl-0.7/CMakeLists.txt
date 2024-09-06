cmake_minimum_required(VERSION 3.10)

# Define the project name and version
project(tdms VERSION 1.0.0)

# Add the tdms library
add_library(tdms STATIC src/TdmsChannel.cpp src/TdmsGroup.cpp src/TdmsLeadIn.cpp src/TdmsMetaData.cpp src/TdmsObject.cpp src/TdmsParser.cpp src/TdmsSegment.cpp)

# Specify the include directories for tdms
target_include_directories(tdms PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Install the tdms library and headers
install(TARGETS tdms EXPORT tdmsTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# Install the headers
install(DIRECTORY include/ DESTINATION include)

# Create the export targets for the tdms library
install(EXPORT tdmsTargets
    FILE tdmsTargets.cmake
    NAMESPACE tdms::
    DESTINATION lib/cmake/tdms
)

# Include the package config helpers
include(CMakePackageConfigHelpers)

# Generate a version file for compatibility checks
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/tdmsConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# Configure the package config file
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/tdmsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/tdmsConfig.cmake"
    INSTALL_DESTINATION lib/cmake/tdms
)

# Install the config and version files
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/tdmsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/tdmsConfigVersion.cmake"
    DESTINATION lib/cmake/tdms
)
