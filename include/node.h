#ifndef NODE_H
#define NODE_H

#include <status.h>
#include "node_config.h"
/*
	These are the types of data that can be stored inside a structure,
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

// Priority of a node
#ifdef CONFIG_NODE_PRIORITY
typedef enum Priority {
	LOW,
	MED,
	HIGH
} Priority;
#endif

/*
	This is the basic skeleton of each node in the structure.

	Members : 	1. type : The type of data stored inside the structure, as defined
	---------	--------- in enum Type.
			2. value : The actual data of the node.
			----------
			3. nextNode : The pointer to the next node in the structure.
			-------------
			4. prevNode : The pointer to the previous node in the structure,
			------------- if permissible by it.
*/

typedef struct Node {
	Type type;
	Data value;
	struct Node *nextNode;
#ifdef CONFIG_DEQUE
	struct Node *prevNode;
#endif
#ifdef CONFIG_NODE_PRIORITY
	Priority priority;
#endif
} Node;

Status node_init(Node **node, Type type, Data value);
Status node_print(Node *aNode, int count);
Status node_create(Node **aNode);
int node_isequal(Node *node1, Node *node2);
int node_isgreater(Node *node1, Node *node2);
int node_islesser(Node *node1, Node *node2);
#ifdef CONFIG_NODE_PRIORITY
Status node_init_priority(Node **aNode, Type type, Priority priority, Data value);
Status node_get_priority(Node *aNode);
#endif
#endif
