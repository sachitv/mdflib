cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_DEBUG_POSTFIX d)
project(mdflibjs)

set(SOURCE_FILES
    src/bindings.cpp  # Replace with the path to your source file
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} mdf)

set_target_properties(${PROJECT_NAME} PROPERTIES
    LINK_FLAGS "-lembind"
)
