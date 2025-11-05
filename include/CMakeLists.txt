# include/CMakeLists.txt

message(STATUS "Configuring common utilities library")

add_library(common_utils STATIC)

target_sources(common_utils PRIVATE
    MemoryOperations.cpp
    StringOperations.cpp
    TypeConverter.cpp
)

target_sources(common_utils PUBLIC
    FILE_SET headers TYPE HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
        types.h
        ISingleton.h
        Templates.h
        MemoryOperations.h
        StringOperations.h
        TypeConverter.h
        containers/Tuple.h
)

target_include_directories(common_utils PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

message(STATUS "Common utils library configured")
