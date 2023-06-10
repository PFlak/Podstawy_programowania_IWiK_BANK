cmake_minimum_required (VERSION 3.8)

add_library(CreateTables "CreateTables.cpp" )

find_package(unofficial-sqlite3 CONFIG REQUIRED)
target_link_libraries(CreateTables PRIVATE unofficial::sqlite3::sqlite3)

target_link_libraries(CreateTables PRIVATE DatabaseConnection)

target_include_directories(CreateTables PUBLIC 
"${PROJECT_SOURCE_DIR}/Domain"
"${PROJECT_SOURCE_DIR}/DatabaseConnection")