#include<stdio.h>
#include"queue_interface.h"


/*
	Main wrapper to the program. User will see only this menu,
	and all of the operations will return back to this method.
*/
Status createQueue(Queue **queue){
	int choice;
	QueueType type;
	int limit = -1;
	printf("What type of queue do you want?\n1. Linear queue\n2. Deque : ");
	scanf("%d",&choice);
	if(choice<1 || choice>2)
		return WRONG_OPTION_CHOOSEN;
	type = choice==1?LINEAR:DEQUE;
	printf("Do you want the queue to be size restricted?\n1. Yes\n2. No : ");
	scanf("%d",&choice);
	if(choice<1 || choice>2)
		return WRONG_OPTION_CHOOSEN;
	if(choice==1){
		printf("Enter the size of the queue : ");
		scanf("%d",&limit);
		if(limit<1)
		{
			printf("The queue must contain atleast 1 node!\n");
			return WRONG_OPTION_CHOOSEN;
		}
	}
	return initQueue(queue, type, limit);
}

Status createNode(Node **node){
	int choice;
	Type type;
	Data value;
	printf("\nWhat type of node do you want to create?\n1. Integer\n2. Real\n3. Character : ");
	scanf("%d",&choice);
	if(choice<1 || choice>3)
		return WRONG_OPTION_CHOOSEN;
	type = choice==1?INTEGER:choice==2?REAL:CHARACTER;
	switch(choice){
		case 1: printf("Enter the integer value : ");
			scanf("%d",&value.ival);
			break;
		case 2: printf("Enter the real value : ");
			scanf("%f",&value.fval);
			break;
		case 3: printf("Enter the character value : ");
			scanf(" %c",&value.cval);
			break;
	}
	return initNode(node, type, value);
}

int main(){
	int choice = -1;
	Queue *queue;
	Node *node;
	//Print welcome message
	printf("Welcome to QueueSimulator\n");
	printf("=========================\n");
	//
	printf("\nCreating the queue");
	printf("\n==================\n");
	if(printStatus(createQueue(&queue),QUEUE_CREATION)!=OP_SUCCESS){
		printf("FATAL ERROR!\nTerminating program..");
		return 1;
	}
	printf("\n==================\n");

	//Add atleast one node before performing any operation
	printf("\nBefore we continue, add at least one Node.\n");
	//Acquire a new node from the user and check if it succeeds.
	if(createNode(&node)==OP_SUCCESS){
		//If it does, add the node to the queue, and print the status
		printStatus(addNode(FRONT, node, queue), INSERTION);
		choice = 1;
	}
	else{
		//If the first node can't be created, exit from the program immediately
		printf("Fatal error! Program will now terminate!\n");
	}
	//The infinite choice-loop
	while(choice>0 && choice<4){
		//Get user choice
		printf("\nWhat do you want to do? ");
		printf("\n1. Insert\n2. Delete\n3. Traverse\n4. Exit : ");
		scanf("%d",&choice);
		switch(choice){
			case 1: //Acquire a new node, and print the status
				printf("\nCreating a new node");
				printf("\n===================\n");
				if(printStatus(createNode(&node), NODE_CREATION)==OP_SUCCESS){
					//If creation succeeds, ask user the position of insertion, 
					//insert it in the queue and print the status
					printf("\n===================\n");
					printf("\nInserting the created node");
					printf("\n==========================\n");
					printStatus(addNode(getPos(INSERTION, queue), node, queue), INSERTION);
					printf("\n==========================\n");
				}
				else
					printf("\n==================\n");
				break;
			case 2: //Ask point of deletion, delete the node, and print the status
				printf("\nDeleting an existing node");
				printf("\n=========================\n");
				printStatus(deleteNode(getPos(DELETION, queue), queue),DELETION);
				printf("\n=========================\n");
				break;
			case 3: //Traverse the queue, and print the status
				printf("\nTraversing the queue");
				printf("\n====================\n");
				printStatus(display(queue, getPos(TRAVERSAL, queue)),TRAVERSAL);
				printf("\n====================\n");
				break;
		}
	}
}
