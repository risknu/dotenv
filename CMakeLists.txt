cmake_minimum_required(VERSION 3.27)
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()
project(dotenvcpp VERSION 2024.1.0 DESCRIPTION "A library that helps work with environment variables using .env files (support for all standards)")

set(CMAKE_CXX_STANDARD 20)

include(GNUInstallDirs)

include_directories(include)

set(SOURCES
        src/dotenv/env.cpp
        src/dotenv/lang/lpdat.cpp
        src/dotenv/lang/lplang.cpp)
set(HEADERS
        include/dotenv/env.hpp
        include/dotenv/lang/lpdat.hpp
        include/dotenv/lang/lplang.hpp)

add_library(dotenvcpp STATIC ${SOURCES} ${HEADERS})

set_target_properties(dotenvcpp PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(dotenvcpp PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
set_target_properties(dotenvcpp PROPERTIES PUBLIC_HEADER "${HEADERS}")

target_include_directories(dotenvcpp PRIVATE include)
target_include_directories(dotenvcpp PRIVATE src)

configure_file(dotenvcpp.pc.in dotenvcpp.pc @ONLY)
install(TARGETS dotenvcpp
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/dotenvcpp.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

add_executable(dotenvcpp_executable main.cpp)
target_link_libraries(dotenvcpp_executable dotenvcpp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET dotenvcpp PROPERTY CXX_STANDARD 20)
endif()
