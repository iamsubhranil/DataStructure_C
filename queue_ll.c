#include<stdio.h>
#include<stdlib.h>

/*
	These are the basic status codes used throughout the program,
	to indicate the status of a particular operation.
	
	Values : 	1. WRONG_OPTION_CHOOSEN : This code is returned by a method when the user
	--------	------------------------- does not comply to the valid choices with the 
				  		  associated menu
			2. NO_MEMORY_AVAILABLE : This code is returned by acquireNode(), when the
			------------------------ node creation process fails because of insufficient
				 		 system memory, i.e. malloc() returns NULL.
			3. QUEUE_OVERFLOW : This code is returned when the user tries to extend the
			------------------- queue beyond its predefined limit, if any.
			4. QUEUE_UNDERFLOW : This code is returned when traversal or deletion is
			-------------------- performed over an empty queue.
			5. INTERNAL_ERROR : This code is returned to depict an undefined system
			------------------- behaviour, which the program should not face in general
			    		    condition.
			6. INVALID_POSITION_SPECIFIED : This code is returned when the user does not
			------------------------------- select any of the front and rear positions to
							perform an opeartion. This is typically binded
							with Position:UNDEFINED, and the choice of the
							position is just converted into a suitable status.
			7. OP_SUCCESS : This code declares the successful execution of a particular
			---------------	operation.
*/
typedef enum Status {
	WRONG_OPTION_CHOOSEN,
	NO_MEMORY_AVAILABLE,
	QUEUE_OVERFLOW,
	QUEUE_UNDERFLOW,
	INTERNAL_ERROR,
	INVALID_POSITION_SPECIFIED,
	OP_SUCCESS
} Status;

/*
	These are the basic operations performed over the queue, declared here
	to make more generalized methods, just by 'switch'ing the appropiate type
	to print the appropiate messages.
	
	Values :	1. CREATION : This indicates the operation of the creation of node,
	--------	------------- typically by acquireNode().
			2. INSERTION : This indicates the operation of inserting a node into
			-------------- the queue, by addNode().
			3. DELETION : This indicates the operation of deletion of a node from
			------------- the queue, if any, by deleteNode().
			4. TRAVERSAL : This indicates the operation of traversal of the queue,
			-------------- by traverse().
*/

typedef enum OP_Type {
	CREATION,
	INSERTION,
	DELETION,
	TRAVERSAL
} OP_Type;

/*
	These are the positions to perform operations over the queue.
	
	Values : 	1. FRONT : The front position of the queue.
	--------	----------
			2. REAR : The rear position of the queue.
			---------
			3. UNDEFINED : If user chooses an invalid option in selection,
			--------------	typically causing return of INVALID_POSITION_SPECIFIED.
*/

typedef enum Position {
	FRONT,
	REAR,
	UNDEFINED
} Position;

/*
	These are the possible types of data values in a node.
	
	Values : 	1. INTEGER : Signifies the node contains integer data
	--------	------------
			2. REAL : Signifies the node contains real data
			---------
			3. CHARACTER : Signifies the node contains character data
			--------------
*/

typedef enum Type {
	INTEGER,
	REAL,
	CHARACTER
} Type;

/*
	These are the types of data that can be stored inside the queue,
	and each node can contain any one of them.
	
	Members :	1. fval : A floating point value
	---------	---------
			2. ival : An integer value
			---------
			3. cval : A character value
			---------
*/

typedef union Data {
	float fval;
	int ival;
	char cval;
} Data;

/*
	This is the basic structure of each node in the queue.
	
	Members : 	1. type : The type of data stored inside the queue.
	---------	--------- 1 indicates an integer value, 2 indicates
				  a real value, a 3 indicates a character value.
			2. value : The actual data of the node
			----------
			3. nextNode : The pointer to the next node in the queue.
			-------------
*/

typedef struct Node {
	Type type;
	Data value;
	struct Node *nextNode;
} Node;

/*
	The fundamental pointers to the front and rear position of the queue.
	Both can be NULL if the queue is empty, can point to the same node
	if the queue contains only one node, or point to the different
	nodes if the size of the queue is >1.
*/

Node *front=NULL, *rear=NULL;

/*
	If the user decides it to be a size restricted queue, limit will contain
	the number of maximum allowed nodes in the queue, and count will contain
	the number of presently inserted nodes.
*/

int limit = -1, count = 0;

/*
	Prints the status message for a particular status code. This is done
	to remove all the interface clutter from the actual operation code.
	
	Arguments : 	1. status : The status to analyze
	-----------	2. op : The operation which returned the status
	Return value : 	1. The status to analyze for further use
	--------------
*/
Status printstatus(Status status, OP_Type op){
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
		return status;
	}
	printf("failed!\nReason : ");
	switch(status){
		case WRONG_OPTION_CHOOSEN: printf("You've choosen a wrong option!");
			break;
		case NO_MEMORY_AVAILABLE: printf("No free system memory available!");
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
	return status;
}

/*
	Gets the user specified position for performing insertion or deletion.
	
	Arguments : 	op : The type of operation for which the position is required
	-----------
	Return value :	Any one of possible position values, based on
	--------------	the selection of the user
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
	Traverses and displays the queue.
	
	Return value : Any one of the following statuses,
	--------------	1. QUEUE_UNDERFLOW
			2. INTERNAL_ERROR : If the type of a node is <1 or >3,
					    which shouldn't be the case whatsoever.
			3. OP_SUCCESS
*/
Status traverse(){
	int count = 1;
	Type type;
	//Point to the front of the queue
	Node *aNode = front;
	//Check if any item is at all present in the queue
	if(aNode==NULL)
		return QUEUE_UNDERFLOW;
	printf("\b\b");
	//Start traversal
	while(aNode!=NULL){
		printf("\n\n");
		printf("Node : %d\nType : ",count++);
		//Check the type of the node
		type = aNode->type;
		//Print the value associated with the type
		switch(type){
			case INTEGER: printf("Integer\nValue : %d",aNode->value.ival);
				break;
			case REAL: printf("Real\nValue : %g",aNode->value.fval);
				break;
			case CHARACTER: printf("Character\nValue : %c",aNode->value.cval);
				break;
			//Type is none of the known!
			default: return INTERNAL_ERROR;
		}
		//Switch to next node
		aNode = aNode->nextNode;
	}
	printf("\n");
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
	Acquires a node from the user. This method saves the acquired node in the global
	variable createdNode, for later use - typically by addNode().
	
	Return value : This method returns one of the following statuses,
	--------------	1. WRONG_OPTION_CHOOSEN
			2. NO_MEMORY_AVAILABLE
			3. OP_SUCCESS
*/
Node *createdNode = NULL;
Status acquireNode(){
	int type;
	//Reset the pointer
	createdNode = NULL;
	//Ask user for the type of the node
	printf("\nEnter the type of Node you want to add : \n");
	printf("1. Integer\n2. Real\n3. Character : ");
	scanf("%d",&type);
	//check if it is at all a valid type
	if(type<1 || type>3)
	{
		//If not, ask the user to retry
		if(retry())
			return acquireNode();
		//If the user denies, return the status
		return WRONG_OPTION_CHOOSEN;
	}
	//If it is a valid type
	else{
		//Acquire a space for the node from the memory
		createdNode = (Node *)malloc(sizeof(Node *));
		//Check if the memory is full
		if(createdNode==NULL)
			return NO_MEMORY_AVAILABLE;
		//Set the type of the node based on previous user selection
		createdNode->type = type==1?INTEGER:type==2?REAL:CHARACTER;
		//Take input of the value for that particular type by the user
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
	Inserts a node in the queue.
	
	Arguments :	1. pos : The position in which the new node is to be inserted
	-----------	2. aNode : The node to be inserted
	Return value : One of the following statuses,
	--------------	1. INTERNAL_ERROR : When the value of aNode is NULL, which it shouldn't be
			2. INVALID_POSITION_SPECIFIED
			3. OP_SUCCESS
*/
Status addNode(Position pos, Node *aNode){
	//Check if the node given to insert is NULL
	if(aNode==NULL)
		return INTERNAL_ERROR;
	//Check if the position is valid
	if(pos==UNDEFINED){
		free(aNode);
		return INVALID_POSITION_SPECIFIED;
	}
	//Check if the queue is full
	if(count==limit){
		free(aNode);
		return QUEUE_OVERFLOW;
	}
	//If front is NULL, then it is the first node to be inserted
	if(front==NULL){
		front = rear = aNode;
	}
	//Check if the insertion is to be performed at the front
	else if(pos==FRONT){
		//Insert front at the end of this node
		aNode->nextNode = front;
		//Set front to the this node
		front = aNode;
	}
	//Check if the insertion is to be performed at the rear
	else if(pos==REAR){
		//Insert the node at the end to the queue
		rear->nextNode = aNode;
		aNode->nextNode = NULL;
		//Set rear to this node
		rear = aNode;
	}
	//Increase the counter
	count++;
	return OP_SUCCESS;
}

/*
	Deletes a node from the queue.
	
	Arguments :	1. pos : The position from which the node is to be deleted
	-----------
	Return value :	One of the following statuses,
	--------------	1. INVALID_POSITION_SPECIFIED
			2. QUEUE_UNDERFLOW
			3. OP_SUCCESS
*/

Status deleteNode(Position pos){
	Node *del;
	//Check if the position is at all valid
	if(pos==UNDEFINED)
		return INVALID_POSITION_SPECIFIED;
	//Check if there is any node present in the queue
	if(front==NULL)
		return QUEUE_UNDERFLOW;
	//Point to the first node
	del = front;
	//Check if there is only one node in the queue
	if(front==rear){
		//Free the only node
		free(front);
		//Reset front and rear to NULL
		front = NULL;
		rear = NULL;
	}
	//Check if the deletion is to be performed on the front
	else if(pos==FRONT){
		//Set front to the second node
		front = front->nextNode;
		//Free front
		free(del);
	}
	//Deletion is to performed at the rear end
	else{
		/* Get the penultimate node of the queue.
		   We need this because queue can only propagate
		   linearly, from front to rear. To delete the rearmost
		   node, we need to set the nextNode pointer of
		   (rear-1)th node to NULL, so that the link is actually
		   broken.
		   This is done by checking the 2nd next node of the present
		   node. If the 2nd next node is NULL, next node is rear,
		   and hence present node is the one containing the link to it.
		*/
		while(del->nextNode->nextNode!=NULL){
			//Propagate to the next node
			del = del->nextNode;
		}
		//Free the next node from memory
		free(del->nextNode);
		//Break the link
		del->nextNode = NULL;
	}
	//Decrease the counter
	count--;
	return OP_SUCCESS;
}

/*
	Main wrapper to the program. User will see only this menu,
	and all of the operations will return back to this method.
*/


int main(){
	int choice = -1;
	//Print welcome message
	printf("Welcome to QueueSimulator\n");
	printf("=========================\n");
	//Ask the user if the queue is size restricted
	printf("Do you want the queue to be size restricted?\nPress 1 to specify a size of the queue\nPress any other key to skip : ");
	scanf("%d",&choice);
	if(choice==1){
		//If it is, get the size and store it to limit
		printf("Specify the size of the queue : ");
		scanf("%d",&limit);
	}
	//Add atleast one node before performing any operation
	printf("\nBefore we continue, add at least one Node.\n");
	//Acquire a new node from the user and check if it succeeds.
	if(acquireNode()==OP_SUCCESS){
		//If it does, add the node to the queue, and print the status
		printstatus(addNode(FRONT, createdNode), INSERTION);
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
				if(printstatus(acquireNode(), CREATION)==OP_SUCCESS){
					//If creation succeeds, ask user the position of insertion, 
					//insert it in the queue and print the status
					printstatus(addNode(getpos(INSERTION), createdNode), INSERTION);
				} 
				break;
			case 2: //Ask point of deletion, delete the node, and print the status
				printstatus(deleteNode(getpos(DELETION)), DELETION); break;
			case 3: //Traverse the queue, and print the status
				printstatus(traverse(), TRAVERSAL); break;
		}
	}
}
