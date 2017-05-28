#include<linkedlist.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
	LinkedList *list;
	Status ret;
	Node *aNode;
	int choice = 1;
	ret = createList(&list);
	if(ret!=OP_SUCCESS)
		printStatus(ret, STRUCTURE_CREATION);
	else{
		while(choice>-1 && choice<12){
			printf("\n0. Display");
			printf("\n1. Insert at front");
			printf("\n2. Insert at end");
			printf("\n3. Insert at position");
			printf("\n4. Insert after value");
			printf("\n5. Delete from front");
			printf("\n6. Delete from end");
			printf("\n7. Delete a value");
			printf("\n8. Delete from position");
			printf("\n9. Delete before value");
			printf("\n10. Reverse list");
			printf("\n11. Sort list");
			printf("\nEnter your choice : ");
			scanf("%d", &choice);
			switch(choice){
				case 0: ret = displayList(list);
					printStatus(ret, TRAVERSAL);
					break;
				case 1:	ret = createNode(&aNode);
					if(ret==OP_SUCCESS){
						ret = insertAtFront(list, aNode);
					}
					printStatus(ret, INSERTION);
					break;
				case 2: ret = createNode(&aNode);
					if(ret==OP_SUCCESS){
						ret = insertAtEnd(list, aNode);
					}
					printStatus(ret, INSERTION);
					break;
				case 3: ret = createNode(&aNode);
					if(ret==OP_SUCCESS){
						printf("\nEnter the position you want to insert : ");
						scanf("%d", &choice);
						ret = insertAtPos(list, aNode, choice);
						choice = 1;
					}
					printStatus(ret, INSERTION);
					break;
				case 4:	printf("\nSelect the node to insert");
					printf("\n==========================");
					Node *node;
					ret = createNode(&node);
					if(ret==OP_SUCCESS){
						printf("\nSelect the value to insert after");
						printf("\n================================");
						ret = createNode(&aNode);
						if(ret==OP_SUCCESS)
							ret = insertAfterValue(list, node, aNode);
						free(aNode);
					}
					printStatus(ret, INSERTION);
					break;
				case 5: ret = deleteFromBeginning(list);
					printStatus(ret, DELETION);
					break;
				case 6: ret = deleteFromEnd(list);
					printStatus(ret, DELETION);
					break;
				case 7: printf("\nSelect the node to delete");
					printf("\n=========================");
					ret = createNode(&aNode);
					if(ret==OP_SUCCESS){
						ret = deleteValue(list, aNode);
					}
					printStatus(ret, DELETION);
					free(aNode);
					break;
				case 8: printf("Enter the position to delete");
					scanf("%d", &choice);
					ret = deleteFromPos(list, choice);
					choice = 1;
					printStatus(ret, DELETION);
					break;
				case 9: printf("\nSelect the node to delete before");
					printf("\n================================");
					ret = createNode(&aNode);
					if(ret==OP_SUCCESS)
						ret = deleteBeforeValue(list, aNode);
					printStatus(ret, DELETION);
					free(aNode);
					break;
				case 10: ret = reverseList(&list);
					 printStatus(ret, REVERSAL);
					 break;
				case 11 : ret = sortList(list);
					  printStatus(ret, SORTING);
					  break;
			}
		}
		freeList(list);
	}
	return 0;
}
