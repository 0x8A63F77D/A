
cmake_minimum_required(VERSION 3.15)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)
# Version information
set(PROJECT_A_VERSION_MAJOR 1)
set(PROJECT_A_VERSION_MINOR 0)
set(PROJECT_A_VERSION_PATCH 0)
set(PROJECT_A_VERSION "${PROJECT_A_VERSION_MAJOR}.${PROJECT_A_VERSION_MINOR}.${PROJECT_A_VERSION_PATCH}")

project(ProjectA
    VERSION ${PROJECT_A_VERSION}
    DESCRIPTION "Matrix Operations Library"
    LANGUAGES CXX
)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find dependencies
find_package(Eigen3 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

# Generate version header
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/include/project_a/version.hpp.in"
    "${CMAKE_CURRENT_BINARY_DIR}/include/project_a/version.hpp"
    @ONLY
)

# Create library
add_library(project_a SHARED
    src/matrix_ops.cpp
)

add_library(ProjectA::project_a ALIAS project_a)

# Set include directories
target_include_directories(project_a
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link dependencies
target_link_libraries(project_a
    PUBLIC
        Eigen3::Eigen
    PRIVATE
        fmt::fmt
)

# Installation settings
include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/ProjectA)

install(TARGETS project_a
    EXPORT ProjectATargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/project_a
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hpp"
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/include/project_a/version.hpp"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/project_a
)

# Export targets
install(EXPORT ProjectATargets
    FILE ProjectATargets.cmake
    NAMESPACE ProjectA::
    DESTINATION ${INSTALL_CONFIGDIR}
)

# Create config files
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/ProjectAConfigVersion.cmake"
    VERSION ${PROJECT_A_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/ProjectAConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/ProjectAConfig.cmake"
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

# Install config files
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/ProjectAConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/ProjectAConfigVersion.cmake"
    DESTINATION ${INSTALL_CONFIGDIR}
)

# CPack configuration
set(CPACK_PACKAGE_NAME "ProjectA")
set(CPACK_PACKAGE_VENDOR "Your Company")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Matrix Operations Library")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_A_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_A_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_A_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
include(CPack)

