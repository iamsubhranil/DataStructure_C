#include<stdio.h>
#include<stdlib.h>
#include<linkedlist.h>

Status createList(LinkedList **list){
	(*list) = (LinkedList *)malloc(sizeof(LinkedList));
	if((*list)==NULL)
		return NO_MEMORY_AVAILABLE;
	(*list)->head = NULL;
	(*list)->count = 0;
	return OP_SUCCESS;
}

Status freeList(LinkedList *list){
	Node *temp = list->head, *backup;
	while(temp!=NULL){
		backup = temp;
		temp = temp->nextNode;
		free(backup);
	}
	free(list);
	return OP_SUCCESS;
}

Status insertAtFront(LinkedList *list, Node *node){
	node->nextNode = list->head;
	list->head = node;
	list->count++;
	return OP_SUCCESS;
}

Status insertAtEnd(LinkedList *list, Node *node){
	if(list->head==NULL)
		list->head = node;
	else{
		Node *temp = list->head;
		while(temp->nextNode!=NULL){
			temp = temp->nextNode;
		}
		temp->nextNode = node;
	}
	list->count++;
	return OP_SUCCESS;
}

Status insertAtPos(LinkedList *list, Node *node, int pos){
	if(pos<1 || pos>list->count+1)
		return INVALID_POSITION_SPECIFIED;
	if(pos==1)
		insertAtFront(list, node);
	else{
		Node *temp = list->head;
		int i = 1;
		while(i++<pos-1)
			temp = temp->nextNode;
		node->nextNode = temp->nextNode;
		temp->nextNode = node;
		list->count++;
	}
	return OP_SUCCESS;
}

Status deleteFromBeginning(LinkedList *list){
	if(list->count==0)
		return UNDERFLOW;
	Node *temp = list->head;
	list->head = list->head->nextNode;
	free(temp);
	list->count--;
	return OP_SUCCESS;
}

Status deleteFromEnd(LinkedList *list){
	if(list->count==0)
		return UNDERFLOW;
	Node *backup, *current = list->head;
	while(current->nextNode!=NULL){
		backup = current;
		current = current->nextNode;
	}
	if(current==list->head)
		list->head = list->head->nextNode;
	else
		backup->nextNode = NULL;
	free(current);
	list->count--;
	return OP_SUCCESS;
}

Status deleteValue(LinkedList *list, Node *value){
	if(list->count==0)
		return UNDERFLOW;
	Node *backup, *current = list->head;
	while(current!=NULL){
		if(isValueEqual(current, value))
			break;
		backup = current;
		current = current->nextNode;
	}
	if(current==NULL)
		return VALUE_NOT_FOUND;
	else{
		if(current==list->head)
			return deleteFromBeginning(list);
		else{
			backup->nextNode = current->nextNode;
			free(current);
			list->count--;
		}
	}
	return OP_SUCCESS;
}

Status deleteFromPos(LinkedList *list, int pos){
	if(list->count==0)
		return UNDERFLOW;
	if(pos<1 || pos>list->count)
		return INVALID_POSITION_SPECIFIED;
	Node *backup, *current = list->head;
	int i = 1;
	while(i<pos-1){
		backup = current;
		current = current->nextNode;
		i++;
	}
	if(pos==1)
		return deleteFromBeginning(list);
	else{
		backup->nextNode = current->nextNode;
		list->count--;
		free(current);
	}
	return OP_SUCCESS;
}

Status insertAfterValue(LinkedList *list, Node *node, Node *insertAfter){
	Node *temp = list->head;
	while(temp!=NULL){
		if(isValueEqual(insertAfter, temp))
			break;
		temp = temp->nextNode;
	}
	if(temp==NULL)
		return VALUE_NOT_FOUND;

	node->nextNode = temp->nextNode;
	temp->nextNode = node;
	list->count++;
	return OP_SUCCESS;
}

Status deleteBeforeValue(LinkedList *list, Node *value){
	if(list->head==NULL)
		return UNDERFLOW;
	if(isValueEqual(list->head, value)){
		return INVALID_POSITION_SPECIFIED;
	}
	Node *temp = list->head, *backup;
	while(temp->nextNode!=NULL){
		if(isValueEqual(temp->nextNode, value))
			break;
		backup = temp;
		temp = temp->nextNode;
	}
	if(temp->nextNode==NULL)
		return VALUE_NOT_FOUND;
	if(temp==list->head)
		list->head = list->head->nextNode;
	else
		backup->nextNode = temp->nextNode;
	free(temp);
	return OP_SUCCESS;
}

Status displayList(LinkedList *list){
	if(list->head==NULL)
		return UNDERFLOW;
	else{
		Node *temp = list->head;
		int i = 1;
		while(temp!=NULL){
			printNode(temp, i++);
			temp = temp->nextNode;
		}
	}
	return OP_SUCCESS;
}
