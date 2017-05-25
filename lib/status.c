#include<status.h>
/*
   Prints the status message for a particular status code. This is done
   to remove all the interface clutter from the actual operation code.

Arguments : 	1. status : The status to analyze
-----------	2. op : The operation which returned the status

Return value : 	1. The status to analyze for further use
--------------
 */
Status printStatus(Status status, OP_Type op){
	printf("\n");
	if(status!=OP_SUCCESS)
		printf("Error : ");
	switch(op){
		case STRUCTURE_CREATION: printf("Structure creation ");
				     break;
		case NODE_CREATION: printf("Node creation ");
				    break;
		case INSERTION: printf("Insertion ");
				break;
		case DELETION: printf("Deletion ");
			       break;
		case TRAVERSAL: printf("Traversal ");
				break;
	}
	if(status==OP_SUCCESS){
		printf("successful!\n");
		return status;
	}
	printf("failed!\nReason : ");
	switch(status){
		case WRONG_OPTION_CHOOSEN: printf("You've choosen a wrong option!");
					   break;
		case NO_MEMORY_AVAILABLE: printf("No free system memory available!");
					  break;
		case OVERFLOW: printf("Structure overflow!");
				     break;
		case UNDERFLOW: printf("Structure underflow!");
				      break;
		case INTERNAL_ERROR: printf("Internal error!");
				     break;
		case INVALID_POSITION_SPECIFIED: printf("You've specified an invalid position!");
						 break;
		case UNDEFINED_OPERATION: printf("Undefined operation!");
					  break;
		case VALUE_NOT_FOUND: printf("Given value not found in the search scope!");
#ifdef CONFIG_PRIORITY_QUEUE
		case INVALID_PRIORITY: printf("The queue does not contain any element of that priority!");
				       break;
#endif
	}
	printf("\n");
	return status;
}
