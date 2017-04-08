#include<node.h>
#include<stdlib.h>
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
