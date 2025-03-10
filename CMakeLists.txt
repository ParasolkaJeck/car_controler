cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME car_controler)

set(CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/Core/Src)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    "${CMAKE_CURRENT_SOURCE_DIR}/joystick.c"
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)


make_directory(${CMAKE_CURRENT_LIST_DIR}/bins)

set(OUTPUT_FILES_DIR ${CMAKE_CURRENT_LIST_DIR}/bins)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME}
        COMMAND cp ${CMAKE_PROJECT_NAME}.elf ${CMAKE_CURRENT_LIST_DIR}/bins/car_controler.elf
        COMMAND objcopy -O ihex ${CMAKE_CURRENT_LIST_DIR}/bins/car_controler.elf ${CMAKE_CURRENT_LIST_DIR}/bins/car_controler.hex
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        USES_TERMINAL
        )

add_custom_target(flash_mcu
    COMMAND STM32_Programmer_CLI -c port=SWD -d car_controler.hex -v -rst
    WORKING_DIRECTORY ${OUTPUT_FILES_DIR}
    VERBATIM
    USES_TERMINAL)