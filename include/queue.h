#ifndef _QUEUE_H
#define _QUEUE_H
//Include custom configuration file
#include"queue_config.h"
#include<status.h>
#include<node.h>
/*
	A basic enum to compensate no boolean identifier
	functionality in C.
	Values : 	1. TRUE : Indicates the truthfulness of an expression
	--------	---------
			2. FALSE : Indicates the falsity of an expression
			----------
*/

typedef enum Boolean {
	FALSE,
	TRUE
} Boolean;

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

typedef enum QueueType {
	LINEAR
#ifdef CONFIG_DEQUE
	,DEQUE
#endif
#ifdef CONFIG_PRIORITY_QUEUE
	,PRIORITY
#endif
} QueueType;

/*
	This is the basic skeleton of a queue.
	Members :	1. isDeque : A Boolean type variable to determine
	---------	----------   the 'Deque'ness of the queue, i.e.
				     it will hold TRUE if the queue is a deque,
				     false otherwise.
			2. front : A pointer to the front node of the queue.
			----------
			3. rear : A pointer to the rear node of the queue.
			---------
			4. count : A variable containing the number of nodes
			---------- in the queue, which must be manually updated
				   after each successful addition or deletion
				   of node in the queue.
			5. limit : Initially set to -1, this variable holds the
			---------- maximum number of allowed elements in the queue,
				   if restricted by the user.
*/

typedef struct Queue {
	QueueType type;
	Node *front;
	Node *rear;
	int count;
	int limit;
} Queue;

//Functions
extern int retry();
extern Position getPos(OP_Type op, Queue *queue);
extern Status traverse(Queue *queue, Position pos, Status (*performOperation)(Node *aNode, int count));
extern Status display(Queue *queue, Position pos);
extern Status addNode(Position pos, Node *aNode, Queue *queue);
extern Status deleteNode(Position pos, Queue *queue);
extern Status initQueue(Queue **queue, QueueType type, int limit);
#ifdef CONFIG_PRIORITY_QUEUE
extern Status addPriorityNode(Node *aNode,  Queue *queue);
extern Status deletePriorityNode(Queue *queue);
#endif
#endif
