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
	}
	return initQueue(queue, type, limit);
}

Status createNode(Node **node){
	int choice;
	Type type;
	Data value;
	printf("What type of node do you want to create?\n1. Integer\n2. Real\n3. Character : ");
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
	if(printStatus(createQueue(&queue),QUEUE_CREATION)!=OP_SUCCESS){
		printf("FATAL ERROR!\nTerminating program..");
		return 1;
	}

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
		printf("\nEnter 1 to insert a new node\nEnter 2 to delete an existing node\nEnter 3 to traverse existing nodes\n");
		printf("Press any other key to exit : ");
		scanf("%d",&choice);
		switch(choice){
			case 1: //Acquire a new node, and print the status
				if(printStatus(createNode(&node), NODE_CREATION)==OP_SUCCESS){
					//If creation succeeds, ask user the position of insertion, 
					//insert it in the queue and print the status
					printStatus(addNode(getPos(INSERTION, queue), node, queue), INSERTION);
				} 
				break;
			case 2: //Ask point of deletion, delete the node, and print the status
				printStatus(deleteNode(getPos(DELETION, queue), queue),DELETION); break;
			case 3: //Traverse the queue, and print the status
				printStatus(display(queue, getPos(TRAVERSAL, queue)),TRAVERSAL); break;
		}
	}
}
