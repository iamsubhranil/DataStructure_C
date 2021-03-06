#include <queue.h>
#include <stdio.h>
#include <stdlib.h>

/*
   Gets appropiate position for performing insertion or deletion.
   This method only asks for user interference is the queue is a
   deque, otherwise it returns the deafult position of operations
   on a standard linear queue.

Arguments : 	1. op : The type of operation for which the position is required
-----------	2. queue : The queue for which the position is to be determined

Return value :	Any one of possible position values, based on
--------------	the selection of the user
 */
Position queue_get_pos(OP_Type op, Queue *queue){
	int choice;
	//If the queue is a linear one, don't bother
	if(queue->type==LINEAR
#ifdef CONFIG_PRIORITY_QUEUE
			|| queue->type==PRIORITY
#endif
	  ){
		if(op==INSERTION)
			return REAR;
		else if(op==DELETION)
			return FRONT;
		else if(op==TRAVERSAL)
			return FRONT;
	}
#ifdef CONFIG_DEQUE
	//This queue is deque, and can have both
	//ends of operation
	switch(op){
		case INSERTION: printf("\nInsert at\n");
				break;
		case DELETION: printf("\nDelete from\n");
			       break;
		case TRAVERSAL: printf("\nTraverse from\n");
				break;
	}
	printf("1. Front\n2. Rear : ");
	scanf("%d",&choice);
	return choice==1?FRONT:choice==2?REAR:UNDEFINED;
#endif
}

/*
   Traverses and displays the queue. This method acts as according to
   the position specified, i.e. if the position is FRONT, it'll traverse
   from the front to the rear end of the queue, and vice versa. This
   method however does not deny to perform reverse traversal on a
   linear queue, which will obviously produce erronous results. Thus
   it is recommended to pass the position from getpos(), which
   determines all implementation specific position values.

   Arguments :		1. queue : The queue which is to be traversed
   -----------		2. pos : The position from which the traversal is to be started
			3. performOperation : The operation to be performed over each traversed node   

   Return value : Any one of the following statuses,
   --------------	1. QUEUE_UNDERFLOW
   			2. OP_SUCCESS
   			3. Statuses of printNode()
 */
Status queue_traverse(Queue *queue, Position pos, Status (*performOperation)(Node *aNode, int count)){
	int loccount = 1;
	Status printStatus;
	Node *aNode = queue->front;
	//Check if there is at all any element in the queue
	if(queue->count==0)
		return UNDERFLOW;
	//Check the position of traversal
#ifdef CONFIG_DEQUE
	if(pos==REAR){
		aNode = queue->rear;
		loccount = queue->count;
	}
#endif
	while(aNode!=NULL){
		if(performOperation!=NULL){
			printStatus = performOperation(aNode, loccount);
			if(printStatus!=OP_SUCCESS)
				return printStatus;
		}
		if(pos==FRONT){
			loccount++;
			aNode = aNode->nextNode;
		}
#ifdef CONFIG_DEQUE
		else if(pos==REAR){
			loccount--;
			aNode=aNode->prevNode;
		}
#endif
	}
	return OP_SUCCESS;
}

Status queue_print(Queue *queue, Position pos){
	return queue_traverse(queue,pos,&node_print);
}
/*
   Simple retry method which prompts the user to retry an operation.
   Returns 1 (true) if user complies to retry, or 0 (false) if user denies.
 */
int retry(){
	int choice;
	printf("Wrong option choosen!\n1. Retry\n2. Exit : ");
	scanf("%d",&choice);
	return choice==1?1:0;
}

#ifdef CONFIG_PRIORITY_QUEUE
Status queue_ins_priority(Node *aNode, Queue *queue){
	Node *temp = queue->front;
	if(aNode==NULL)
		return INTERNAL_ERROR;
	if(queue->count==queue->limit){
		free(aNode);
		return OVERFLOW;
	}
	if(temp==NULL){
		queue->front = queue->rear = aNode;
	}
	else if(temp->priority<aNode->priority){
		aNode->nextNode = temp;
		queue->front = aNode;
	}
	else{
		while(temp->nextNode!=NULL && temp->nextNode->priority>=aNode->priority){
			temp = temp->nextNode;
		}
		if(temp->nextNode==NULL)
			queue->rear = aNode;

		aNode->nextNode = temp->nextNode;
		temp->nextNode = aNode;
	}
	queue->count++;

	return OP_SUCCESS;
}

Status queue_del_priority(Queue *queue){
	Node *temp = queue->front;

	if(queue->count==0)
		return UNDERFLOW;
	
	if(queue->front==queue->rear)
		queue->front = queue->rear = NULL;
	else
		queue->front = queue->front->nextNode;

	free(temp);
	queue->count--;
	return OP_SUCCESS;
}

#endif

/*
   Inserts a node in the queue. This method does not denies to perform the
   insertion on the wrong end of a queue, which defies the queue integrity.
   Thus it is recommended to resolve the position using getpos(), which
   holds all the implementation specific position specifications.

Arguments :	1. pos : The position in which the new node is to be inserted
-----------	2. aNode : The node to be inserted
		3. queue : The queue in which the node is to be inserted

Return value : One of the following statuses,
--------------	1. INTERNAL_ERROR : When the value of aNode is NULL, which it shouldn't be
		2. INVALID_POSITION_SPECIFIED
		3. OP_SUCCESS
 */

Status queue_ins(Position pos, Node *aNode, Queue *queue){
#if defined(CONFIG_LINEAR_QUEUE) || defined(CONFIG_DEQUE)
	//Check if the node given to insert is NULL
	if(aNode==NULL)
		return INTERNAL_ERROR;
	//Check if the position is valid
	if(pos==UNDEFINED){
		free(aNode);
		return INVALID_POSITION_SPECIFIED;
	}
	//Check if the queue is full
	if(queue->count==queue->limit){
		free(aNode);
		return OVERFLOW;
	}
	//If front is NULL, then it is the first node to be inserted
	if(queue->count==0){
		queue->front = queue->rear = aNode;
	}
#ifdef CONFIG_DEQUE
	//Check if the insertion is to be performed at the front.
	//Only advisable is the queue is a deque, otherwise
	//prevNode links will still be there.
	else if(pos==FRONT){
		//Insert front at the end of this node
		aNode->nextNode = queue->front;
		//Link the node as the previous node of front
		queue->front->prevNode = aNode;
		//Set this node's previous node to NULL
		aNode->prevNode = NULL;
		//Set front to the this node
		queue->front = aNode;
	}
#endif
	//Check if the insertion is to be performed at the rear
	else{
		//Insert the node at the end to the queue
		queue->rear->nextNode = aNode;
#ifdef CONFIG_DEQUE
		//If the queue is a deque, link the prevNode
		if(queue->type==DEQUE){
			aNode->prevNode = queue->rear;
		}
#endif
		//Set the nextNode to NULL
		aNode->nextNode = NULL;
		//Set rear to this node
		queue->rear = aNode;
	}
	//Increase the counter
	queue->count++;
	return OP_SUCCESS;
#else
	return UNDEFINED_OPERATION;
#endif
}
/*
   Deletes a node from the queue.  However, this method does not denies
   to perform the operation on the wrong end of a particular queue,
   which in turn does not guarantee the queue integrity whatsoever. Thus
   it is recommended to retrieve the position only using getpos(), which
   holds all implementation speific queue position declarations.

Arguments :	1. pos : The position from which the node is to be deleted
----------- 	2. queue : The queue on which deletion will be performed

Return value :	One of the following statuses,
--------------	1. INVALID_POSITION_SPECIFIED
		2. QUEUE_UNDERFLOW
		3. OP_SUCCESS
 */

Status queue_del(Position pos, Queue *queue){
#if defined(CONFIG_LINEAR_QUEUE) || defined(CONFIG_DEQUE)
	Node *del;
	//Check if the position is at all valid
	if(pos==UNDEFINED)
		return INVALID_POSITION_SPECIFIED;
	//Check if there is any node present in the queue
	if(queue->count==0)
		return UNDERFLOW;
	//Point to the first node
	del = queue->front;
	//Check if there is only one node in the queue
	if(queue->front==queue->rear){
		//Free the only node
		free(queue->front);
		//Reset front and rear to NULL
		queue->front = NULL;
		queue->rear = NULL;
	}
	//Check if the deletion is to be performed on the front
	else if(pos==FRONT){
		//Set front to the second node
		queue->front = queue->front->nextNode;
#ifdef CONFIG_DEQUE
		if(queue->type==DEQUE)
			queue->front->prevNode = NULL;
#endif
		//Free front
		free(del);
	}
#ifdef CONFIG_DEQUE
	//Deletion is to performed at the rear end
	//Only happenning if the queue is deque
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
		del->nextNode->prevNode = NULL;
		free(del->nextNode);
		//Break the link
		del->nextNode = NULL;
	}
#endif
	//Decrease the counter
	queue->count--;
	return OP_SUCCESS;
#else
	return UNDEFINED_OPERATION;
#endif
}

/*
   Initializes a queue based on the user specification
   of size restriction.
Arguments :	1. queue : The queue to be initialized
-----------

Return value : Any one of the following statuses,
--------------	1. NO_MEMORY_AVAILABLE
		2. OP_SUCCESS
 */

Status queue_init(Queue **queue, QueueType type, int limit){
	//Allocate memory for the queue
	*queue = (Queue *)malloc(sizeof(Queue));
	//Check if the allocation succeeds
	if(*queue==NULL)
		return NO_MEMORY_AVAILABLE;
	//Initialize the queue members
	(*queue)->count = 0;
	(*queue)->limit = limit;
	(*queue)->front = NULL;
	(*queue)->rear = NULL;
	(*queue)->type = type;

	return OP_SUCCESS;
}
