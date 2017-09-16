#include <queuell.h>
#include <stdlib.h>
#include <stdio.h>

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

Status queuell_init(Queue **queue, QueueType type, int limit){
    (*queue) = (Queue *)malloc(sizeof(Queue));
    list_init(&(*queue)->list);
    if((*queue)->list == NULL)
        return NO_MEMORY_AVAILABLE;
    (*queue)->rear = NULL;
    (*queue)->front = NULL;
    (*queue)->limit = limit;
    (*queue)->type = type;
    return OP_SUCCESS;
}

static Position queue_get_pos(OP_Type op, Queue *queue){
	int choice;
	//If the queue is a linear one, don't bother
	if(queue->type==LINEAR || queue->type==PRIORITY){
		if(op==INSERTION)
			return REAR;
		else if(op==DELETION)
			return FRONT;
		else if(op==TRAVERSAL)
			return FRONT;
	}

	//This queue is deque, and can have both
	//ends of operation
	switch(op){
		case INSERTION: printf("\nInsert at\n");
				break;
		case DELETION: printf("\nDelete from\n");
			       break;
		case TRAVERSAL: printf("\nTraverse from\n");
				break;
        default:
                break;
	}
	printf("1. Front\n2. Rear : ");
	scanf("%d",&choice);
	return choice==1?FRONT:choice==2?REAR:UNDEFINED;
}

static void queuell_ins_priority(Queue *queue, Node *aNode){
    Node *temp = queue->front;
    if(temp->priority<aNode->priority){
		list_ins_front(queue->list, aNode);
	}
	else{
		while(temp->nextNode!=NULL && temp->nextNode->priority>=aNode->priority){
			temp = temp->nextNode;
		}
		if(temp->nextNode==NULL)
			queue->rear = aNode;

		aNode->nextNode = temp->nextNode;
		temp->nextNode = aNode;
	}
}

Status queuell_ins(Queue *queue, Node *toIns){
    if(queue->limit == queue->list->count)
        return OVERFLOW;

    if(queue->front == NULL){
        queue->front = queue->rear = toIns;
        list_ins_end(queue->list, toIns);
    }
    else if(queue->type == PRIORITY){
        queuell_ins_priority(queue, toIns);
    }
    else{
        Position insert = queue_get_pos(INSERTION, queue);
        if(insert == UNDEFINED)
            return INVALID_POSITION_SPECIFIED;

        toIns->nextNode = NULL;

        if(insert == REAR){
            if(queue->type == DEQUE)
                toIns->prevNode = queue->rear;

            queue->rear->nextNode = toIns;
            queue->rear = toIns;
            queue->list->count++;
        }
        else if(insert == FRONT){
            if(queue->type == DEQUE){
                toIns->prevNode = NULL;
                queue->list->head->prevNode = toIns;
            }
            list_ins_front(queue->list, toIns);
        }
    }
    return OP_SUCCESS;
}

Status queuell_del(Queue *queue){
    if(queue->list->count == 0)
        return UNDERFLOW;

    Position del = queue_get_pos(DELETION, queue);
    
    if(del == UNDEFINED)
        return INVALID_POSITION_SPECIFIED;

    if(del == FRONT)
        return list_del_front(queue->list);
    else
        return list_del_end(queue->list);
}

Status queuell_print(Queue *queue){
    if(queue->list->count == 0)
        return UNDERFLOW;

    Position pos = queue_get_pos(TRAVERSAL, queue);
    
    if(pos == FRONT)
        return list_print(queue->list);
    else{
        Node *toStart = queue->rear;
        int i = queue->list->count;
        while(toStart != NULL){
            node_print(toStart, i--);
            toStart = toStart->prevNode;
        }
        return OP_SUCCESS;
    }
}

Status queuell_free(Queue *queue){
    list_free(queue->list);
    free(queue);
    return OP_SUCCESS;
}
