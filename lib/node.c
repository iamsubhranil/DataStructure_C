#include<node.h>
#include<stdlib.h>
#include<stdio.h>
/*
   Initialize a node with given inputs from the user about
   its type and value.

Arguments :	1. createdNode : The node to be initialized
-----------

Return value : This method returns one of the following statuses,
--------------	1. NO_MEMORY_AVAILABLE
		2. OP_SUCCESS
 */

Status initNode(Node **aNode, Type type, Data value){
	//Acquire a space for the node from the memory
	(*aNode) = (Node *)malloc(sizeof(Node));
	//Check if the memory is full
	if(*aNode==NULL)
		return NO_MEMORY_AVAILABLE;
	(*aNode)->type = type;
	(*aNode)->value = value;
	return OP_SUCCESS;
}

#ifdef CONFIG_PRIORITY_QUEUE
void printPriority(Priority p){
	printf("\n");
	switch(p){
		case HIGH: printf("Priority : High");
			   break;
		case MED: printf("Priority : Medium");
			  break;
		case LOW: printf("Priority : Low");
	}
}
#endif

/*
   Prints the value of a node.

Arguments :	1. aNode : the node to be printed
-----------

Return values : Anyone of the following statuses,
---------------	1. INTERNAL_ERROR : When the node type is undefined,
		which it should not be
		2. OP_SUCCESS
 */

Status printNode(Node *aNode, int count){
	//Check the type of the node
	Type type = aNode->type;
	if(count>0)
		printf("\n\nNode : %d",count);
#ifdef CONFIG_PRIORITY_QUEUE
	if(aNode->priority>=0)
		printPriority(aNode->priority);
#endif
	printf("\nNode type : ");
	//Print the value associated with the type
	switch(type){
#ifdef CONFIG_NODE_INTEGER
		case INTEGER: printf("Integer\nValue : %d",aNode->value.ival);
			      break;
#endif
#ifdef CONFIG_NODE_REAL
		case REAL: printf("Real\nValue : %g",aNode->value.fval);
			   break;
#endif
#ifdef CONFIG_NODE_CHARACTER
		case CHARACTER: printf("Character\nValue : %c",aNode->value.cval);
				break;
#endif
				//Type is none of the known!
		default: printf("%d\nFATAL ERROR!\n",type);
			 return INTERNAL_ERROR;
	}
	printf("\n");
	return OP_SUCCESS;
}
