add_library(linkedlist SHARED liblinkedlist.c)
target_link_libraries(linkedlist node
                                status)
