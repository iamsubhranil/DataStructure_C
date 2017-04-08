#ifndef NODE_H
#define NODE_H

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
#ifdef CONFIG_PRIORITY_QUEUE
	Priority priority;
#endif
} Node;

#endif
