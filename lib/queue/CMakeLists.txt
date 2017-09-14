add_library(queue SHARED libqueue.c)
target_link_libraries(queue node
                                status)
