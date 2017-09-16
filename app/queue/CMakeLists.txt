add_executable(queue_ll queue_ll.c)
target_link_libraries(queue_ll queue)

add_executable(queue2 queue2.c)
target_link_libraries(queue2 queuell)
