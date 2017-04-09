#include <stdio.h>
#include <queue.h>
/*
   Main wrapper to the program. User will see only this menu,
   and all of the operations will return back to this method.
 */
Status createQueue(Queue **queue){
	char choice;
	QueueType type = LINEAR;
	int limit = -1;
#ifdef MULQUEUE
	printf("\nWhat type of queue do you want?");
#ifdef CONFIG_LINEAR_QUEUE
	printf("\n(L)inear queue");
#endif
#ifdef CONFIG_DEQUE
	printf("\n(D)eque");
#endif
#ifdef CONFIG_PRIORITY_QUEUE
	printf("\n(P)riority queue");
#endif
	printf(" : ");
	scanf(" %c", &choice);
	switch(choice){
#ifdef CONFIG_LINEAR_QUEUE
		case 'L' : 
		case 'l' : type = LINEAR;
			   break;
#endif
#ifdef CONFIG_DEQUE
		case 'D' : 
		case 'd' : type = DEQUE;
			   break;
#endif
#ifdef CONFIG_PRIORITY_QUEUE
		case 'P' : 
		case 'p' : type = PRIORITY;
			   break;
#endif
		default : return WRONG_OPTION_CHOOSEN;
			  break;
	}
#else
	printf("Queue type : %s\n", DEF_QUEUE_STRING);
	type = DEF_QUEUE_TYPE;
#endif
	
	printf("Do you want the queue to be size restricted?\n1. Yes\n2. No : ");
	scanf(" %c",&choice);
	if(choice!='1' && choice!='2')
		return WRONG_OPTION_CHOOSEN;
	if(choice=='1'){
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

Status createQueueNode(Node **node, Queue *queue){
	Status ret = createNode(node);
#ifdef CONFIG_PRIORITY_QUEUE
	if(queue->type==PRIORITY && ret==OP_SUCCESS){
		ret = getPriority((*node));
	}
#endif
	return ret;
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
	if(printStatus(createQueue(&queue),STRUCTURE_CREATION)!=OP_SUCCESS){
		printf("FATAL ERROR!\nQueue cannot be created!\nTerminating program..");
		return 1;
	}
	printf("\n==================\n");

	//Add atleast one node before performing any operation
	printf("\nBefore we continue, add at least one node.\n");
	//Acquire a new node from the user and check if it succeeds.
	if(createQueueNode(&node, queue)==OP_SUCCESS){
		//If it does, add the node to the queue, and print the status

#ifdef CONFIG_PRIORITY_QUEUE
		if(queue->type==PRIORITY)
			printStatus(addPriorityNode(node, queue), INSERTION);
		else
		{
			node->priority = -1;
#endif
			printStatus(addNode(FRONT, node, queue), INSERTION);
#ifdef CONFIG_PRIORITY_QUEUE
		}
#endif
		choice = 1;
	}
	else{
		//If the first node can't be created, exit from the program immediately
		printf("Fatal error!\nFirst Node can't be added!\nProgram will now terminate!\n");
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
				if(printStatus(createQueueNode(&node, queue), NODE_CREATION)==OP_SUCCESS){
					//If creation succeeds, ask user the position of insertion, 
					//insert it in the queue and print the status
					printf("\n===================\n");
					printf("\nInserting the created node");
					printf("\n==========================\n");
#ifdef CONFIG_PRIORITY_QUEUE
					if(queue->type==PRIORITY)
						printStatus(addPriorityNode(node, queue), INSERTION);
					else
#endif
						printStatus(addNode(getPos(INSERTION, queue), node, queue), INSERTION);

					printf("\n==========================\n");
				}
				else
					printf("\n==================\n");
				break;
			case 2: //Ask point of deletion, delete the node, and print the status
				printf("\nDeleting an existing node");
				printf("\n=========================\n");
#ifdef CONFIG_PRIORITY_QUEUE
				if(queue->type==PRIORITY)
					printStatus(deletePriorityNode(queue), DELETION);
				else
#endif
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
