#ifndef _QUEUE_H
#define _QUEUE_H
//Include custom configuration file
#include"queue_config.h"
#include<status.h>
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

#ifdef CONFIG_PRIORITY_QUEUE
typedef enum Priority {
	LOW,
	MED,
	HIGH
} Priority;
#endif

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
	INTEGER
#ifdef CONFIG_NODE_REAL
	,REAL
#endif
#ifdef CONFIG_NODE_CHARACTER
	,CHARACTER
#endif
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
#ifdef CONFIG_NODE_REAL
	float fval;
#endif
	int ival;
#ifdef CONFIG_NODE_CHARACTER
	char cval;
#endif
} Data;

/*
	This is the basic structure of each node in the queue.

	Members : 	1. type : The type of data stored inside the queue, as defined
	---------	--------- in enum Type.
			2. value : The actual data of the node.
			----------
			3. nextNode : The pointer to the next node in the queue.
			-------------
			4. prevNode : The pointer to the previous node in the queue,
			------------- only useful if the queue is a deque.
*/

typedef struct Node {
	Type type;
	Data value;
	struct Node *nextNode;
#ifdef CONFIG_DEQUE
	struct Node *prevNode;
#endif
#ifdef CONFIG_PRIORITY_QUEUE
	Priority priority;
#endif
} Node;

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
extern Status printNode(Queue *queue, Node *aNode, int count);
extern Status traverse(Queue *queue, Position pos, Status (*performOperation)(Queue *queue, Node *aNode, int count));
extern Status display(Queue *queue, Position pos);
extern Status initNode(Node **aNode, Type type, Data value);
extern Status addNode(Position pos, Node *aNode, Queue *queue);
extern Status deleteNode(Position pos, Queue *queue);
extern Status initQueue(Queue **queue, QueueType type, int limit);
#ifdef CONFIG_PRIORITY_QUEUE
extern Status addPriorityNode(Node *aNode,  Queue *queue);
extern Status initPriorityNode(Node **aNode, Type type, Priority priority, Data value);
extern Status deletePriorityNode(Queue *queue);
#endif
#endif
