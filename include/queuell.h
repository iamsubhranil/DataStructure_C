#ifndef _QUEUELL_H
#define _QUEUELL_H
//Include custom configuration file
#include <status.h>
#include <node.h>
#include <linkedlist.h>

typedef enum QueueType {
	LINEAR,
    DEQUE,
    PRIORITY
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
	LinkedList *list;
	Node *front;
	Node *rear;
	int limit;
    QueueType type;
} Queue;

//Functions

Status queuell_init(Queue **queue, QueueType type, int limit);
Status queuell_free(Queue *queue);
Status queuell_ins(Queue *queue, Node *aNode);
Status queuell_del(Queue *queue);
Status queuell_print(Queue *queue);

#endif
