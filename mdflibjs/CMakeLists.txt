cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_DEBUG_POSTFIX d)
project(mdflibjs)

set(SOURCE_FILES
    src/attachment_wrapped.h
    src/can_message_wrapped.h
    src/channel_conversion_wrapped.h
    src/channel_group_wrapped.h
    src/channel_observer_wrapped.h
    src/channel_wrapped.h
    src/data_group_wrapped.h
    src/etag_helpers.h
    src/event_wrapped.h
    src/file_history_wrapped.h
    src/file_wrapped.h
    src/header_wrapped.h
    src/metadata_wrapped.h
    src/reader_wrapped.h
    src/source_information_wrapped.h
    src/writer_wrapped.h
    src/bindings.cpp  # Replace with the path to your source file
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} mdf)

set_target_properties(${PROJECT_NAME} PROPERTIES
    COMPILE_FLAGS "-sWASM_BIGINT -pthread -sPTHREAD_POOL_SIZE=2"
    LINK_FLAGS "-lembind -sWASM_BIGINT -pthread -sPTHREAD_POOL_SIZE=2"
)
