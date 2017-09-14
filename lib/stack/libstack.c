#include <stdlib.h>
#include <stack.h>
#include <linkedlist.h>

Status stack_init(Stack **stack){
	(*stack) = (Stack *)malloc(sizeof(Stack));
	if((*stack)==NULL)
		return NO_MEMORY_AVAILABLE;
	(*stack)->list = NULL;
    list_init(&(*stack)->list);
    if((*stack)->list == NULL){
        free((*stack));
        return NO_MEMORY_AVAILABLE;
    }
	(*stack)->limit = -1;
	(*stack)->list->count = 0;
	return OP_SUCCESS;
}

Status stack_push(Node *aNode, Stack *aStack){
	if(aStack->list->count==aStack->limit)
		return OVERFLOW;
	return list_ins_front(aStack->list, aNode);
}

Status stack_pop(Stack *aStack){
	if(aStack->list->count==0)
		return UNDERFLOW;
    return list_del_front(aStack->list);
}

Status stack_print(Stack *aStack){
	if(aStack->list->count==0)
		return UNDERFLOW;
	Node *temp = aStack->list->head;
	int count = 0;
	while(temp!=NULL){
		node_print(temp, ++count);
		temp = temp->nextNode;
	}
	return OP_SUCCESS;
}
