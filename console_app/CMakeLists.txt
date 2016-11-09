project(console_app)
cmake_minimum_required(VERSION 2.8)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Find the QtWidgets library
find_package(Qt5Core)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_LIST)
file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)
file(GLOB RESSOURCE *.json)


add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${RESSOURCE})

# Use the Widgets module from Qt 5.
target_link_libraries(${PROJECT_NAME} Qt5::Core)
