#include<stdlib.h>
#include<stack.h>

Status initStack(Stack **stack){
	(*stack) = (Stack *)malloc(sizeof(Stack));
	if((*stack)==NULL)
		return NO_MEMORY_AVAILABLE;
	(*stack)->top = NULL;
	(*stack)->limit = -1;
	(*stack)->count = 0;
	return OP_SUCCESS;
}

Status push(Node *aNode, Stack *aStack){
	if(aStack->count==aStack->limit)
		return OVERFLOW;
	aNode->nextNode = aStack->top;
	aNode->nextNode = NULL;
	aStack->top = aNode;
	aStack->count++;
	return OP_SUCCESS;
}

Status pop(Node **aNode, Stack *aStack){
	if(aStack->count==0)
		return UNDERFLOW;
	(*aNode) = aStack->top;
	aStack->top = aStack->top->nextNode;
	aStack->count--;
	return OP_SUCCESS;
}

Status display(Stack *aStack){
	if(aStack->count==0)
		return UNDERFLOW;
	Node *temp = aStack->top;
	int count = 0;
	while(temp!=NULL){
		printNode(temp, ++count);
		temp = temp->nextNode;
	}
	return OP_SUCCESS;
}
