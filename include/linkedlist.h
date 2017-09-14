#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <node.h>
#include <status.h>
typedef struct LinkedList{
	Node *head;
	int count;
} LinkedList;

Status list_init(LinkedList **list);
Status list_free(LinkedList *list);
Status list_print(LinkedList *list);

Status list_ins_front(LinkedList *list, Node *node);
Status list_ins_end(LinkedList *list, Node *node);
Status list_ins_pos(LinkedList *list, Node *node, int pos);
Status list_ins_after(LinkedList *list, Node *value, Node *insertAfter);

Status list_del_front(LinkedList *list);
Status list_del_end(LinkedList *list);
Status list_del_val(LinkedList *list, Node * value);
Status list_del_pos(LinkedList *list, int position);
Status list_del_before(LinkedList *list, Node *value);
Status list_del_second_largest(LinkedList *list);

Status list_reverse(LinkedList **list);
Status list_sort(LinkedList *list);
Status list_reverse_alt(LinkedList *list);
#endif
