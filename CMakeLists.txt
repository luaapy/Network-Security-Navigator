cmake_minimum_required(VERSION 3.10)
project(NSN VERSION 1.0.0 LANGUAGES C CXX)

# Options
option(NSN_BUILD_TESTS "Build tests" ON)
option(NSN_ENABLE_STATIC "Enable static build" OFF)

# Configuration
configure_file(nsnconfig.h.in nsnconfig.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(Include)

# Find Dependencies
find_package(OpenSSL)
# (Add others as needed)

# Sources
file(GLOB_RECURSE NSN_CORE_SRCS
    "Nsn/*.c"
    "Objects/*.c"
    "Parser/*.c"
    "Modules/*.c"
)

# Executable
add_executable(nsn Programs/nsn.c ${NSN_CORE_SRCS})
if(OPENSSL_FOUND)
    target_link_libraries(nsn OpenSSL::SSL OpenSSL::Crypto)
endif()
target_link_libraries(nsn m)

# Installation
install(TARGETS nsn DESTINATION bin)
install(DIRECTORY Include/ DESTINATION include/nsn)
install(DIRECTORY Lib/ DESTINATION lib/nsn)

# Tests
if(NSN_BUILD_TESTS)
    enable_testing()
    add_executable(test_lexer tests/unit/test_lexer.c ${NSN_CORE_SRCS})
    target_link_libraries(test_lexer m)
    add_test(NAME test_lexer COMMAND test_lexer)
endif()
