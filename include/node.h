#ifndef NODE_H
#define NODE_H

#include <status.h>
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
	float fval;
	int ival;
	char cval;
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
	INTEGER,
    REAL,
    CHARACTER
} Type;

// Priority of a node
typedef enum Priority {
	LOW,
	MED,
	HIGH
} Priority;

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
	struct Node *prevNode;
    unsigned short hasPriority;
	Priority priority;
} Node;

void node_configure();
int node_typecount();

Status node_init(Node **node, Type type, Data value);
Status node_init_priority(Node **aNode, Type type, Data value, Priority priority);
Status node_free(Node *aNode);

Status node_print(Node *aNode, int count);
Status node_create(Node **aNode, int hasPriority);

int node_isequal(Node *node1, Node *node2);
int node_isgreater(Node *node1, Node *node2);
int node_islesser(Node *node1, Node *node2);
#endif
