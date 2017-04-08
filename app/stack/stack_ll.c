#include<stdio.h>
#include<stack.h>
#define CONFIG_NODE_INTEGER
int main(){
	Stack *stack;
	Node *node;
	Data value;
	value.ival = 20;
	printStatus(initStack(&stack), STRUCTURE_CREATION);
	printStatus(initNode(&node, INTEGER, value), NODE_CREATION);
	printStatus(push(node, stack), INSERTION);
	node = NULL;
	printStatus(pop(&node, stack), DELETION);
	printNode(node, 0);
	return 0;
}
