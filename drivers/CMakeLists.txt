message(STATUS "Configuring drivers")

target_sources(${TARGET_NAME} PRIVATE
    acpi/Acpi.cpp
    acpi/Ics.cpp
)

target_include_directories(${TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

message(STATUS "Drivers configured: ACPI")
