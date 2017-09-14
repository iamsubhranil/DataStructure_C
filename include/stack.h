#ifndef STACK_H
#define STACK_H

#include "status.h"
#include "node.h"
#include "linkedlist.h"

typedef struct Stack {
	LinkedList *list;
	int limit;
} Stack;

Status stack_pop(Stack *stack);
Status stack_push(Node *aNode, Stack *stack);
Status stack_print(Stack *stack);
Status stack_init(Stack **stack);

#endif
