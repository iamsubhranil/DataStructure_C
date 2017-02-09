#include<stdio.h>
#include<stdlib.h>

typedef enum Status {
	WRONG_OPTION_CHOOSEN,
	NO_MEMORY_AVAILABLE,
	QUEUE_OVERFLOW,
	QUEUE_UNDERFLOW,
	INTERNAL_ERROR,
	INVALID_POSITION_SPECIFIED,
	OP_SUCCESS
} Status;

typedef enum OP_Type{
	CREATION,
	INSERTION,
	DELETION,
	TRAVERSAL
} OP_Type;

typedef enum Position{
	FRONT,
	REAR,
	UNDEFINED
} Position;

typedef union Data {
	float fval;
	int ival;
	char cval;
} Data;

typedef struct Node {
	int type;
	Data value;
	struct Node *nextNode;
} Node;

Node *front=NULL, *rear=NULL;

/*
	Prints the error message for a particular error code.
*/
void printstatus(Status status, OP_Type op){
	printf("\n");
	switch(op){
		case CREATION: printf("Node creation ");
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
		return;
	}
	printf("failed!\nReason : ");
	switch(status){
		case WRONG_OPTION_CHOOSEN: printf("You've choosen a wrong option!\n");
			break;
		case NO_MEMORY_AVAILABLE: printf("No free system memory available!\n");
			break;
		case QUEUE_OVERFLOW: printf("Queue overflow!");
			break;
		case QUEUE_UNDERFLOW: printf("Queue underflow!");
			break;
		case INTERNAL_ERROR: printf("Internal error!");
			break;
		case INVALID_POSITION_SPECIFIED: printf("You've specified an invalid position!");
			break;
	}
	printf("\n");
}

/*
	Gets the user specified position for performing insertion or deletion.
*/
Position getpos(OP_Type op){
	int choice;
	printf("\nChoose the point of ");
	switch(op){
		case INSERTION: printf("insertion\n");
			break;
		case DELETION: printf("deletion\n");
			break;
	}
	printf("Press 1 for front\nPress 2 for rear : ");
	scanf("%d",&choice);
	return choice==1?FRONT:choice==2?REAR:UNDEFINED;
}

/*
	Traverse the queue till 'upto'. 
	Returns the Node at 'upto' if found, or NULL.
*/
Status traverse(){
	int count = 1, type;
	Node *aNode = front;
	if(aNode==NULL)
		return QUEUE_UNDERFLOW;
	while(aNode!=NULL){
		printf("Node : %d\nValue : ",count++);
		type = aNode->type;
		switch(type){
			case 1: printf("%d",aNode->value.ival);
				break;
			case 2: printf("%g",aNode->value.fval);
				break;
			case 3: printf("%c",aNode->value.cval);
				break;
			default: return INTERNAL_ERROR;
		}
		printf("\n");
		aNode = aNode->nextNode;
	}
	return OP_SUCCESS;
}
/*
	Simple retry method which prompts the user to retry an operation.
	Returns 1 (true) if user complies to retry, or 0 (false) if user denies.
*/
int retry(){
	int choice;
	printf("Wrong option choosen!\nPress 1 to retry\nPress any other key to exit : ");
	scanf("%d",&choice);
	return choice==1?1:0;
}
/*
	Method for acquiring a node from the user. This method saves the acquired node in the global
	createdNode, for later use - typically by addNode().
*/
Node *createdNode = NULL;
Status acquireNode(){
	int type;
	createdNode = NULL;
	printf("Enter the type of Node you want to add : \n");
	printf("1. Integer\n2. Real\n3. Character : ");
	scanf("%d",&type);
	if(type<1 || type>3)
	{
		if(retry())
			return acquireNode(); 
		return WRONG_OPTION_CHOOSEN;
	}
	else{
		createdNode = (Node *)malloc(sizeof(struct Node));
		if(createdNode==NULL)
			return NO_MEMORY_AVAILABLE;
		createdNode->type = type;
		if(type==1)
		{
			printf("Enter the integer value you want to store : ");
			scanf("%d",&createdNode->value.ival);
		}
		else if(type==2){
			printf("Enter the real value you want to store : ");
			scanf("%f",&createdNode->value.fval);
		}
		else{
			printf("Enter the character value you want to store : ");
			scanf(" %c",&createdNode->value.cval);
		}
	}
	return OP_SUCCESS;

}

/*
	Insert a Node in the queue. Here pos signifies the position to insert, typically front or rear, if present.
	The possible 'Status'es of this operation are :
	1. INTERNAL_ERROR : When the value of aNode is NULL, which it shouldn't be
	2. INVALID_POSITION_SPECIFIED
	3. OP_SUCCESS
*/
Status addNode(Position pos, Node *aNode){
	Node *temp;
	int type;
	if(aNode==NULL)
		return INTERNAL_ERROR;
	if(pos==UNDEFINED)
		return INVALID_POSITION_SPECIFIED;
	if(pos==FRONT){
		if(front==NULL){
			front=aNode;
			rear=aNode;
		}
		else{
			aNode->nextNode = front;
			front = aNode;
		}
	}
	else if(pos==REAR){
		if(rear==NULL){
			front = aNode;
			rear=aNode;
		}
		else{
			rear->nextNode = aNode;
			aNode->nextNode = NULL;
			rear = aNode;
		}
	}
	return OP_SUCCESS;
}

Status deleteNode(Position pos){
	Node *del, *temp;
	if(pos==UNDEFINED)
		return INVALID_POSITION_SPECIFIED;
	if(front==NULL)
		return QUEUE_UNDERFLOW;
	del = front;
	if(front==rear){
		free(front);
		front = NULL;
		rear = NULL;
	}
	else if(pos==FRONT){
		front = front->nextNode;
		free(del);
	}
	else{
		while(del->nextNode->nextNode!=NULL){
			del = del->nextNode;
		}
		free(del->nextNode);
		del->nextNode = NULL;
	}
	return OP_SUCCESS;
}

int main(){
	int choice = 1;
	printf("Welcome to QueueSimulator\n");
	printf("=========================\n");
	printf("Before we continue, add at least one Node.\n");
	if(acquireNode()==OP_SUCCESS)
		printstatus(addNode(FRONT, createdNode), INSERTION);
	else{
		printf("Fatal error! Program will now terminate!");
		choice = 5;
	}
	while(choice>0 && choice<4){
		printf("\nEnter 1 to insert a new Node\nEnter 2 to delete an existing Node\nEnter 3 to traverse existing Nodes\n");
		printf("Press any other key to exit : ");
		scanf("%d",&choice);
		printf("\n");
		switch(choice){
			case 1: printstatus(acquireNode(), CREATION);
				printstatus(addNode(getpos(INSERTION), createdNode), INSERTION); break;
			case 2: printstatus(deleteNode(getpos(DELETION)), DELETION); break;
			case 3: printstatus(traverse(), TRAVERSAL); break;
		}
	}
}
