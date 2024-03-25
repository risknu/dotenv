cmake_minimum_required(VERSION 3.27)
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()
project(dotenvcpp VERSION 2024.1.0 DESCRIPTION "A library that helps work with environment variables using .env files (support for all standards)")

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(dotenvcpp main.cpp
    src/dotenv/env.cpp
    src/dotenv/lang/lplang.cpp
    src/dotenv/lang/lpdat.cpp
        include/dotenv/dotenv.hpp
        src/dotenv/dotenv.cpp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET dotenvcpp PROPERTY CXX_STANDARD 20)
endif()
