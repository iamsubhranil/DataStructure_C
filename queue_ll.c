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

typedef union data {
	float fval;
	int ival;
	char cval;
} data;

typedef struct node {
	int type;
	data value;
	struct node *nextnode;
} node;

node *front=NULL, *rear=NULL;

/*
	Prints the error message for a particular error code.
*/
void printerror(Status error){
	switch(error){
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
}

/*
	Traverse the queue till 'upto'. 
	Returns the node at 'upto' if found, or NULL.
*/
node* traverse(int upto){
	int count = 0;
	node *anode = front;
	if(anode==NULL)
		return NULL;
	while(count<upto && anode!=NULL){
		anode = anode->nextnode;
		count++;
	}
	return anode;
}

/*
	Insert a node in the queue. Here pos==0 signifes insert at the front, pos==1 signifies insert at the end,
	and any other non-negative value signifes to insert at that particular position, if present.
	The possible 'Status'es of this operation are :
	1. WRONG_OPTION_CHOOSEN : When the user does not comply to any of the three types of node to insert
	2. NO_MEMORY_AVAILABLE : When the node creation failed because of insufficient memory
	3. INVALID_POSITION_SPECIFIED : When user tries to enter the node in a position which doesn't exist
	4. OP_SUCCESS : When the insertion succeeds
*/
Status addnode(int pos){
	node *anode, *temp;
	int type;
	if(pos<0)
		return INVALID_POSITION_SPECIFIED;
	printf("Enter the type of node you want to add : \n");
	printf("1. Integer\n2. Real\n3. Character : ");
	scanf("%d",&type);
	if(type<1 || type>3)
	{
		printf("Wrong type inserted!\nPress 1 to retry\nPress 2 to exit : ");
		scanf("%d",&type);
		if(type==1)
			return addnode(pos);
		else
			return WRONG_OPTION_CHOOSEN;
	}
	else{
		anode = (node *)malloc(sizeof(struct node));
		if(anode==NULL)
			return NO_MEMORY_AVAILABLE;
		anode->type = type;
		if(type==1)
		{
			printf("Enter the integer value you want to store : ");
			scanf("%d",&anode->value.ival);
		}
		else if(type==2){
			printf("Enter the real value you want to store : ");
			scanf("%f",&anode->value.fval);
		}
		else{
			printf("Enter the character value you want to store : ");
			scanf("%c",&anode->value.cval);
		}
		if(pos==0){
			if(front==NULL){
				front=anode;
				rear=anode;
			}
			else{
				anode->nextnode = front;
				front = anode;
			}
		}
		else if(pos==1){
			if(rear==NULL){
				front = anode;
				rear=anode;
			}
			else{
				rear->nextnode = anode;
				anode->nextnode = NULL;
			}
		}
		else{
			temp = traverse(pos);
			if(temp==NULL)
				return INVALID_POSITION_SPECIFIED;
			anode->nextnode = temp->nextnode;
			temp->nextnode = anode;
		}
		return OP_SUCCESS;
	}
}


int main(){
	Status status;
	printf("Welcome to QueueSimulator\n");
	printf("=========================\n");
	printf("Before we continue, add at least one node.\n");
	status = addnode(0);
	if(status!=OP_SUCCESS){
		printf("Insertion failed!\nReason : ");
		printerror(status);
	}
}
