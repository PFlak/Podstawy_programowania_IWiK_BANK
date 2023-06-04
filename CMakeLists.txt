# CMakeList.txt : CMake project for Podstawy_programowania_IWiK_BANK, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Podstawy_programowania_IWiK_BANK")

# Add source to this project's executable.

add_subdirectory(CreateTables)
add_subdirectory(DatabaseConnection)
# add_subdirectory(Operations)

add_executable (Podstawy_programowania_IWiK_BANK 
"main/src/Podstawy_programowania_IWiK_BANK.cpp" 
"main/src/Podstawy_programowania_IWiK_BANK.h" 
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Podstawy_programowania_IWiK_BANK PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

find_package(Crow CONFIG REQUIRED)
target_link_libraries(Podstawy_programowania_IWiK_BANK PRIVATE Crow::Crow)


target_include_directories(Podstawy_programowania_IWiK_BANK PUBLIC
"${PROJECT_SOURCE_DIR}/CreateTables"
"${PROJECT_SOURCE_DIR}/DatabaseConnection"
"${PROJECT_SOURCE_DIR}/Controllers"
#"${PROJECT_SOURCE_DIR}/Operations"
)