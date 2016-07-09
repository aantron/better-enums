cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

set(project_name better-enums)

project(${project_name})

include(CTest)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

# Set this to the current published version of Better Enums
set(upstream_version 0.11.2)

set(public_header_files
    enum.h
)

# Directories for installed targets
set(INSTALL_DIR ${CMAKE_INSTALL_PREFIX})
set(INCLUDE_DIR include/${project_name}-${upstream_version})
set(CONFIG_DIR lib/cmake/${project_name}-${upstream_version})

# Convert source files to absolute path, since `target_sources()` does not
# function well on relative paths and actually requires them to be absolute.
#
# If better enums ever gets actual translation units, we can build a STATIC
# or SHARED library, at which time this manual relative->absolute conversion
# will no longer be necessary since it won't be an INTERFACE target.
foreach(source_file ${public_header_files})
    get_filename_component(abs_source_file ${source_file} ABSOLUTE)
    
    # Use BUILD_INTERFACE because we don't actually want the interface
    # source files to be exported with targets for installation purposes.
    # The interface sources are only useful for our own targets, so that
    # we see the files in the actual exe/lib projects for devleopment
    # purposes.
    #
    # External projects that import better-enums do so only for the
    # public include directories and the header files we use should not
    # be put into their own projects.
    list(APPEND absolute_source_files
        $<BUILD_INTERFACE:${abs_source_file}>
    )
endforeach()

###################################################################
## DEFINE BUILD TARGETS
###################################################################

# Main Library Target
add_library(${project_name} INTERFACE)
target_sources(${project_name} INTERFACE ${absolute_source_files})

# Test Targets
if(BUILD_TESTING)
    add_subdirectory(test)
endif()

###################################################################
## INSTALL TARGETS & FILES
###################################################################

# Install all of our public header files
install(FILES
    ${public_header_files}
    DESTINATION ${INCLUDE_DIR}
)

# Generate export rules for better-enums target
install(TARGETS ${project_name} EXPORT ${project_name}-targets
    INCLUDES DESTINATION ${INCLUDE_DIR}
)

install(EXPORT ${project_name}-targets
    DESTINATION ${CONFIG_DIR}
)

include(CMakePackageConfigHelpers)

# Generate the Config Package file. Used by find_package() in
# downstream projects to find the better enums library
configure_package_config_file(
    ${project_name}-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${project_name}-config.cmake
    INSTALL_DESTINATION ${CONFIG_DIR}
    PATH_VARS INSTALL_DIR INCLUDE_DIR CONFIG_DIR
)

# Version file for the config package also used by find_package() to
# allow a specific version of better enums to be found and used
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${project_name}-config-version.cmake
    VERSION ${upstream_version}
    COMPATIBILITY AnyNewerVersion
)

# Install the config package & version config files
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${project_name}-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${project_name}-config-version.cmake
    DESTINATION ${CONFIG_DIR}
)
