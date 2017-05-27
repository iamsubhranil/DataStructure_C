#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include<node.h>
#include<status.h>
typedef struct LinkedList{
	Node *head;
	int count;
} LinkedList;

extern Status createList(LinkedList **list);
extern Status freeList(LinkedList *list);
extern Status displayList(LinkedList *list);

extern Status insertAtFront(LinkedList *list, Node *node);
extern Status insertAtEnd(LinkedList *list, Node *node);
extern Status insertAtPos(LinkedList *list, Node *node, int pos);
extern Status insertAfterValue(LinkedList *list, Node *value, Node *insertAfter);

extern Status deleteFromBeginning(LinkedList *list);
extern Status deleteFromEnd(LinkedList *list);
extern Status deleteValue(LinkedList *list, Node * value);
extern Status deleteFromPos(LinkedList *list, int position);
extern Status deleteBeforeValue(LinkedList *list, Node *value);

extern Status reverseList(LinkedList **list);
extern Status sort(LinkedList *list);

#endif
