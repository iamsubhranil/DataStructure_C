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
#ifdef CONFIG_NODE_PRIORITY
	(*aNode)->priority = -1;
#endif
	return OP_SUCCESS;
}

#ifdef CONFIG_NODE_PRIORITY
Status initPriorityNode(Node **aNode, Type type, Priority priority, Data value){
	Status stat = initNode(aNode, type, value);
	if(stat==OP_SUCCESS)
		(*aNode)->priority = priority;
	return stat;
}

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

Status getPriority(Node *aNode){
	Priority priority;
	char choice;
	printf("Enter the priority of the node\n1. High\n2. Medium\n3. Low : ");
	scanf(" %c", &choice);
	if(choice<'1' || choice>'3')
		return WRONG_OPTION_CHOOSEN;
	priority = choice=='1'?HIGH:choice=='2'?MED:LOW;
	aNode->priority = priority;
	return OP_SUCCESS;
}
#endif

Status createNode(Node **node){
	Type type;
	Data value;
	char choice;
#ifdef MULVALUE
	printf("\nSelect the type of node =>");
#ifdef CONFIG_NODE_INTEGER
	printf("\n(I)nteger");
#endif
#ifdef CONFIG_NODE_REAL
	printf("\n(R)eal");
#endif
#ifdef CONFIG_NODE_CHARACTER
	printf("\n(C)haracter");
#endif
	printf(" : ");
	scanf(" %c", &choice);
	switch(choice){
#ifdef CONFIG_NODE_INTEGER
		case 'I' :
		case 'i' : type = INTEGER;
			printf("Enter the integer value : ");
			scanf("%d",&value.ival);
			break;
#endif
#ifdef CONFIG_NODE_REAL
		case 'R' : 
		case 'r' : type = REAL;
			printf("Enter the real value : ");
			scanf("%f",&value.fval);
			break;
#endif
#ifdef CONFIG_NODE_CHARACTER
		case 'C' : 
		case 'c' : type = CHARACTER;
			printf("Enter the character value : ");
			scanf(" %c",&value.cval);
			break;
#endif
		default : return WRONG_OPTION_CHOOSEN;
			  break;
	}
#else
	printf("\nEnter the value of the %s node : ", DEF_NODE_STRING);
	scanf(DEF_NODE_FS,&value.DEF_NODE_BIT);
	type = DEF_NODE_TYPE;
#endif
	return initNode(node, type, value);
}

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
#ifdef CONFIG_NODE_PRIORITY
	if(aNode->priority>=0)
		printPriority(aNode->priority);
#endif
#ifdef MULVALUE
	printf("\nNode type : ");
#endif
	//Print the value associated with the type
	switch(type){
		case INTEGER: 
#ifdef MULVALUE
			printf("Integer");
#endif
			printf("\nValue : %d",aNode->value.ival);
			break;
#ifdef CONFIG_NODE_REAL
		case REAL:
#ifdef MULVALUE	
			printf("Real");
#endif
			printf("\nValue : %g",aNode->value.fval);
			break;
#endif
#ifdef CONFIG_NODE_CHARACTER
		case CHARACTER: 
#ifdef MULVALUE
			printf("Character");
#endif
			printf("\nValue : %c",aNode->value.cval);
			break;
#endif
				//Type is none of the known!
		default: printf("%d\nFATAL ERROR!\n",type);
			 return INTERNAL_ERROR;
	}
	printf("\n");
	return OP_SUCCESS;
}

int isValueEqual(Node *node1, Node *node2){
	if(node1->type==node2->type){
		switch(node1->type){
			case INTEGER: return node1->value.ival==node2->value.ival;
#ifdef CONFIG_NODE_REAL
			case REAL: return node1->value.fval==node2->value.fval;
#endif
#ifdef CONFIG_NODE_CHARACTER
			case CHARACTER: return node1->value.cval==node2->value.cval;
#endif
		}
	}
	else
		return 0;
}
