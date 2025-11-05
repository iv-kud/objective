cmake_minimum_required(VERSION 3.16)

set(ARCH "x86" CACHE STRING "Target architecture (x86, arm, etc)")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

string(TOLOWER "${ARCH}" ARCH_LOWER)

if(ARCH_LOWER STREQUAL "x86")
    set(TARGET_NAME "ObjectiveOS-X86")
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/arch/x86/toolchain-x86.cmake)
    enable_language(ASM_NASM)
    message(STATUS "Building for x86 architecture")
elseif(ARCH_LOWER STREQUAL "arm")
    #TODO: Add build for ARM arch
else()
    message(FATAL_ERROR "Unknown architecture: ${ARCH_LOWER}. Supported: x86, arm")
endif()

project(ObjectiveOS VERSION 0.1 LANGUAGES C CXX)

add_executable(${TARGET_NAME})
execute_process(
    COMMAND i686-elf-gcc -print-libgcc-file-name
    OUTPUT_VARIABLE LIBGCC_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

get_filename_component(LIBGCC_DIR ${LIBGCC_PATH} DIRECTORY)
message(STATUS "LibGCC directory: ${LIBGCC_DIR}")

add_subdirectory(include)
target_link_libraries(${TARGET_NAME} PRIVATE common_utils)

target_sources(${TARGET_NAME} PUBLIC
    kernel/kernel.cpp
)
add_subdirectory(arch)
add_subdirectory(drivers)

if(ARCH_LOWER STREQUAL "x86")
    target_link_options(${TARGET_NAME} PRIVATE ${OS_LINKER_FLAGS})
    target_link_libraries(${TARGET_NAME} PRIVATE
        -L${LIBGCC_DIR}
        -lgcc
    )
endif()
