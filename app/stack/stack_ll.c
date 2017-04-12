#include<stdio.h>
#include<stack.h>

int main(){
	Stack *stack;
	Node *node;
	int ch;
	printf("Creating stack..");
	printStatus(initStack(&stack), STRUCTURE_CREATION);
	printf("Do you want to specify stack limit?\n1. Yes\n2. No : ");
	scanf("%d",&ch);
	switch(ch){
		case 1: printf("\nEnter the limit of the stack : ");
			scanf("%d",&ch);
			stack->limit = ch;
	}
	ch = 1;
	while(ch>0 && ch<4){
		printf("\n1. Push\n2. Pop\n3. Traverse\n4. Exit : ");
		scanf("%d", &ch);
		switch(ch){
			case 1: printf("\nPushing a node");
				printf("\n==============");
				if(printStatus(createNode(&node), NODE_CREATION)==OP_SUCCESS){
					if(printStatus(push(node, stack), INSERTION)!=OP_SUCCESS)
						free(node);
				}
				printf("\n===============");
				break;
			case 2: printf("\nPopping a node");
				printf("\n==============");
				if(printStatus(pop(&node, stack), DELETION)==OP_SUCCESS){
					printf("\nPopped item =>");
					printNode(node, 0);
				}
				printf("\n==============");
				break;
			case 3: printf("\nTraversing the stack");
				printf("\n====================");
				printStatus(display(stack), TRAVERSAL);
				printf("\n====================");
				break;
			default: printf("\nExiting program..");
				 break;
		}
	}
	return 0;
}
