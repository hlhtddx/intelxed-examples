cmake_minimum_required(VERSION 3.23)
project(intelxed-examples)

set(CMAKE_CXX_STANDARD 17)

include_directories(PUBLIC "${XED_KIT_PATH}/include")
link_directories(PUBLIC "${XED_KIT_PATH}/lib")
link_libraries(xed)

add_library(xed_cmd_line
        xed-examples-util.c
        xed-enc-lang.c
        xed-dot.c
        xed-dot-prep.c
        xed-disas-raw.c
        avltree.c
        xed-disas-hex.c
        xed-symbol-table.c
        )

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_library(xed_cmdline_linux STATIC
            xed-disas-elf.c
            )
    link_libraries(xed_cmdline_linux)
endif ()

add_library(xed_decoder
        xed-disas-filter.c
        xed-nm-symtab.c
        )

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_library(xed_decoder_windows
            xed-disas-pecoff.cpp
            )
    link_libraries(xed_decoder_windows)
endif ()

if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    add_library(xed_decoder_darwin
            xed-disas-macho.c
            )
    link_libraries(xed_decoder_darwin)
endif ()

add_executable(test01 main.cpp)
add_executable(xed-bin xed.c)
target_link_libraries(xed-bin xed_cmd_line xed_decoder)
add_executable(xed-dec-print xed-dec-print.c)
add_executable(xed-table xed-tables.c)
