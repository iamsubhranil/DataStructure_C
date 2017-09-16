add_library(queue SHARED libqueue.c)
target_link_libraries(queue node
                                status)

add_library(queuell SHARED libqueuell.c)
target_link_libraries(queuell linkedlist)
