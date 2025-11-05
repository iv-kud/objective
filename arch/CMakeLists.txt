if(ARCH_LOWER STREQUAL "x86")
    target_sources(${TARGET_NAME} PRIVATE
        SecondaryInit.cpp
        x86/PrimaryInit.cpp
        x86/cpuinfo/Cpuinfo.cpp
        x86/gdt/Gdt.cpp
        x86/ic/Pic.cpp
        x86/idt/Idt.cpp
        x86/io/VGADisplay.cpp
        x86/msr/Msr.cpp
        x86/port/PortOps.cpp
    )
    target_sources(${TARGET_NAME} PRIVATE
        x86/boot/boot.asm
        x86/cpuinfo/CpuidCheck.asm
        x86/gdt/SwitchToGdt.asm
    )
    target_include_directories(${TARGET_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/x86
    )

    message(STATUS "x86 architecture configured successfully")
    
elseif(ARCH_LOWER STREQUAL "arm")
    message(WARNING "ARM architecture not yet implemented")    
else()
    message(FATAL_ERROR "Unsupported architecture: ${ARCH}. Supported: x86, arm")
endif()
