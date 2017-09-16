#include <stdio.h>
#include <stdlib.h>
#include <linkedlist.h>

Status list_init(LinkedList **list){
	(*list) = (LinkedList *)malloc(sizeof(LinkedList));
	if((*list)==NULL)
		return NO_MEMORY_AVAILABLE;
	(*list)->head = NULL;
	(*list)->count = 0;
	return OP_SUCCESS;
}

Status list_free(LinkedList *list){
	node_free(list->head);
	free(list);
	return OP_SUCCESS;
}

Status list_ins_front(LinkedList *list, Node *node){
	node->nextNode = list->head;
	list->head = node;
	list->count++;
	return OP_SUCCESS;
}

Status list_ins_end(LinkedList *list, Node *node){
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

Status list_ins_pos(LinkedList *list, Node *node, int pos){
	if(pos<1 || pos>list->count+1)
		return INVALID_POSITION_SPECIFIED;
	if(pos==1)
		list_ins_front(list, node);
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

Status list_del_front(LinkedList *list){
	if(list->count==0)
		return UNDERFLOW;
	Node *temp = list->head;
	list->head = list->head->nextNode;
	free(temp);
	list->count--;
	return OP_SUCCESS;
}

Status list_del_end(LinkedList *list){
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

Status list_del_val(LinkedList *list, Node *value){
	if(list->count==0)
		return UNDERFLOW;
	Node *backup, *current = list->head;
	while(current!=NULL){
		if(node_isequal(current, value))
			break;
		backup = current;
		current = current->nextNode;
	}
	if(current==NULL)
		return VALUE_NOT_FOUND;
	else{
		if(current==list->head)
			return list_del_front(list);
		else{
			backup->nextNode = current->nextNode;
			free(current);
			list->count--;
		}
	}
	return OP_SUCCESS;
}

Status list_del_pos(LinkedList *list, int pos){
	if(list->count==0)
		return UNDERFLOW;
	if(pos<1 || pos>list->count)
		return INVALID_POSITION_SPECIFIED;
	Node *backup = list->head, *current = list->head;
	int i = 0;
	while(i<pos-1){
		backup = current;
		current = current->nextNode;
		i++;
	}
	if(pos==1)
		return list_del_front(list);
	else{
		backup->nextNode = current->nextNode;
		list->count--;
		free(current);
	}
	return OP_SUCCESS;
}

Status list_ins_after(LinkedList *list, Node *node, Node *insertAfter){
	Node *temp = list->head;
	while(temp!=NULL){
		if(node_isequal(insertAfter, temp))
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

Status list_del_before(LinkedList *list, Node *value){
	if(list->head==NULL)
		return UNDERFLOW;
	if(node_isequal(list->head, value)){
		return INVALID_POSITION_SPECIFIED;
	}
	Node *temp = list->head, *backup;
	while(temp->nextNode!=NULL){
		if(node_isequal(temp->nextNode, value))
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

Status list_print(LinkedList *list){
	if(list->head==NULL)
		return UNDERFLOW;
	else{
		Node *temp = list->head;
		int i = 1;
		while(temp!=NULL){
			node_print(temp, i++);
			temp = temp->nextNode;
		}
	}
	return OP_SUCCESS;
}

Status list_reverse(LinkedList **list){
	if((*list)->head==NULL)
		return UNDERFLOW;
	Node *temp = (*list)->head;
	LinkedList *newList;
	Status ret;
	ret = list_init(&newList);
	if(ret!=OP_SUCCESS)
		return ret;
	while(temp!=NULL){
		Node *temp2;
		ret = node_init(&temp2, temp->type, temp->value);
		if(ret!=OP_SUCCESS)
			return ret;
		ret = list_ins_front(newList, temp2);
		temp = temp->nextNode;
	}
	list_free(*list);
	(*list) = newList;
	return OP_SUCCESS;
}

static void list_sort_type(LinkedList *list){
	Node *temp = list->head;
	while(temp->nextNode!=NULL){
		Node *t2 = temp->nextNode;
		while(t2!=NULL){
			if(t2->type>temp->type){
				Data d = temp->value;
				Type t = temp->type;
				temp->type = t2->type;
				temp->value = t2->value;
				t2->value = d;
				t2->type = t;
			}
			t2 = t2->nextNode;
		}
		temp = temp->nextNode;
	}
}

Status list_sort(LinkedList *list){
	if(list->head==NULL)
		return UNDERFLOW;
    list_sort_type(list);
	Node *temp = list->head;
	while(temp->nextNode!=NULL){
		Node *t2 = temp->nextNode;
		while(t2!=NULL){
			if(node_isgreater(temp, t2)){
				Data t = temp->value;
				temp->value = t2->value;
				t2->value = t;
			}
			t2 = t2->nextNode;
		}
		temp = temp->nextNode;
	}
	return OP_SUCCESS;
}

Status list_reverse_alt(LinkedList *list){
	if(list->count==0)
		return UNDERFLOW;
	if(list->count==1)
		return OP_SUCCESS;
	Node *prev = NULL;
	Node *temp = list->head;
	while(temp!=NULL){
		Node *copy = temp;
		temp = temp->nextNode;
		copy->nextNode = prev;
		prev = copy;
	}
	list->head = prev;
	return OP_SUCCESS;
}

Status list_del_second_largest(LinkedList *list){
    if(node_typecount() > 1)
        return UNDEFINED_OPERATION;
    if(list->count==0)
		return UNDERFLOW;
	if(list->count==1)
		return VALUE_NOT_FOUND;
	/* By : alexykuzmin0 (https://stackoverflow.com/users/1989995/alexeykuzmin0)
	 * From :
	 * https://stackoverflow.com/questions/44562724/deletion-of-second-largest-element-from-a-singly-linked-list/44563708#44563708
	 *
	 */
	Node *temp = list->head;
	Node *prev = NULL;

	Node *largest = NULL;
	Node *prev0 = NULL;

	Node *prev1 = NULL;
	Node *ptr = temp;
	while(temp!=NULL){
		if(largest==NULL || node_isgreater(temp, largest)){
			ptr = largest;
			prev1 = prev0;

			largest = temp;
			prev0 = prev;
		}
		else if(!node_isequal(largest, temp) && (ptr==NULL || node_isgreater(temp, ptr))){
			prev1 = prev;
			ptr = temp;
		}
		prev = temp;
		temp = temp->nextNode;
	}
	if(ptr==NULL)
		return VALUE_NOT_FOUND;
	if(ptr==list->head)
		list->head = list->head->nextNode;
	else
		prev1->nextNode = ptr->nextNode;
	free(ptr);
	list->count--;
	return OP_SUCCESS;
}
