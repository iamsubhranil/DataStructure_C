#ifndef STATUS_H
#define STATUS_H
/*
	These are the basic status codes used throughout the programs,
	to indicate the status of a particular operation.

	Values : 	1. WRONG_OPTION_CHOOSEN : This code is returned by a method when the user
	--------	------------------------- does not comply to the valid choices with the
				  		  associated menu
			2. NO_MEMORY_AVAILABLE : This code is returned by initNode(), when the
			------------------------ node creation process fails because of insufficient
				 		 system memory, i.e. malloc() returns NULL.
			3. OVERFLOW : This code is returned when the user tries to extend the
			------------------- structure beyond its predefined limit, if any.
			4. UNDERFLOW : This code is returned when traversal or deletion is
			-------------------- performed over an empty structure.
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
	OVERFLOW,
	UNDERFLOW,
	INTERNAL_ERROR,
	INVALID_POSITION_SPECIFIED,
	OP_SUCCESS,
	UNDEFINED_OPERATION
#ifdef CONFIG_PRIORITY_QUEUE
	,INVALID_PRIORITY
#endif
} Status;

/*
	These are the basic operations performed over a data structure, declared here
	to make more generalized methods, just by 'switch'ing the appropiate type
	to print the appropiate messages.

	Values :	1. CREATION : This indicates the operation of the creation of node,
	--------	------------- typically by initNode().
			2. INSERTION : This indicates the operation of inserting a node into
			-------------- the structure, by addNode() or similar functions.
			3. DELETION : This indicates the operation of deletion of a node from
			------------- the structure, if any, by deleteNode() or similar functions.
			4. TRAVERSAL : This indicates the operation of traversal over the structure,
			-------------- by traverse().
*/

typedef enum OP_Type {
	STRUCTURE_CREATION,
	NODE_CREATION,
	INSERTION,
	DELETION,
	TRAVERSAL
} OP_Type;

extern Status printStatus(Status status, OP_Type op);
#endif
