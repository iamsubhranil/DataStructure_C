#ifndef STACK_H
#define STACK_H

#include"status.h"
#include"node.h"

typedef struct Stack {
	Node *top;
	int limit;
	int count;
} Stack;

extern Status pop(Node **aNode, Stack *stack);
extern Status push(Node *aNode, Stack *stack);
extern Status display(Stack *stack);
extern Status initStack(Stack **stack);

#endif
