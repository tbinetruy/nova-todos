# Build definition for the TODO counter demo:
cmake_minimum_required(VERSION 2.8.11)

find_package(Qt5Core 5.3.0 REQUIRED NO_MODULE)
link_directories(/usr/local/lib/)

add_executable(todos todos.cpp)

target_include_directories(todos PUBLIC /usr/local/include/OrgModeParser)

target_link_libraries(todos Qt5::Core)
target_link_libraries(todos OrgModeParser)

set_target_properties(todos PROPERTIES MACOSX_BUNDLE FALSE)
set_property(TARGET todos PROPERTY CXX_STANDARD 11)

install(TARGETS todos DESTINATION bin)
