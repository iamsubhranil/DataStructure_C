set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/bin)

include_directories(include)

add_subdirectory(${CMAKE_SOURCE_DIR}/lib)
add_subdirectory(${CMAKE_SOURCE_DIR}/app)
#add_library(node SHARED lib/node.c)
#add_library(status SHARED lib/node.c)
#add_library(linkedlist SHARED lib/linkedlist/liblinkedlist.c)
#target_link_libraries(linkedlist node
#                                status)
#add_library(queue SHARED lib/queue/libqueue.c)
#add_library(stack SHARED lib/linkedlist/libstack.c)
#target_link_libraries(stack linkedlist)
#
#add_executable(linkedlist_app app/linkedlist/ll_frontend.c)
#target_link_libraries(linkedlist_app linkedlist)

