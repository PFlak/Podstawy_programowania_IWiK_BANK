cmake_minimum_required (VERSION 3.8)

add_library(Operations "Operations.cpp")

find_package(unofficial-sqlite3 CONFIG REQUIRED)
target_link_libraries(Operations unofficial::sqlite3::sqlite3)