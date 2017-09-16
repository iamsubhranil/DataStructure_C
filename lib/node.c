#include <node.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*
   Initialize a node with given inputs from the user about
   its type and value.

Arguments :	1. createdNode : The node to be initialized
-----------

Return value : This method returns one of the following statuses,
--------------	1. NO_MEMORY_AVAILABLE
2. OP_SUCCESS
*/

Status node_init(Node **aNode, Type type, Data value){
    //Acquire a space for the node from the memory
    (*aNode) = (Node *)malloc(sizeof(Node));
    //Check if the memory is full
    if(*aNode==NULL)
        return NO_MEMORY_AVAILABLE;
    (*aNode)->type = type;
    (*aNode)->value = value;
    (*aNode)->nextNode = NULL;
    (*aNode)->hasPriority = 0;
    return OP_SUCCESS;
}

Status node_init_priority(Node **aNode, Type type, Data value, Priority priority){
    Status stat = node_init(aNode, type, value);
    if(stat==OP_SUCCESS){
        (*aNode)->hasPriority = 1;
        (*aNode)->priority = priority;
    }
    return stat;
}

static void node_print_priority(Priority p){
    printf("\n");
    switch(p){
        case HIGH: printf("Priority : High");
                   break;
        case MED: printf("Priority : Medium");
                  break;
        case LOW: printf("Priority : Low");
    }
}

static Priority node_get_priority(){
    Priority priority;
    char choice;
    printf("Enter the priority of the node\n1. High\n2. Medium\n3. Low : ");
    scanf(" %c", &choice);
    priority = choice=='1'?HIGH:choice=='2'?MED:LOW;
    return priority;
}

static int configured = 0, hasint = 1, hasreal = 0, haschar = 0, typecount = 1;
static char *DEF_NODE_STRING = "integer";
static Type DEF_NODE_TYPE = INTEGER;

void node_configure(){
    char input;
    typecount = hasint = haschar = hasreal = 0;
    printf("\nSelect the type of nodes");
    printf("\n========================");

    int types[] = {0,0,0}, i = 0;
    char *typenames[] = {"Integer", "Real", "Character"};
    while(i < 3){
        printf("\n%s (Y/N) : ", typenames[i]);
        scanf(" %c", &input);
        if(input == 'Y' || input == 'y'){
            typecount++;
            types[i] = 1;
        }
        i++;
    }

    hasint = types[0];
    hasreal = types[1];
    haschar = types[2];

    if(typecount == 0){
        printf("\nDefaulted to type : Integer");
        hasint = 1;
        typecount = 1;
    } 
    else if(typecount == 1){
        if(hasreal){
            DEF_NODE_STRING = "real";
            DEF_NODE_TYPE = REAL;
        }
        else if(haschar){
            DEF_NODE_STRING = "character";
            DEF_NODE_TYPE = CHARACTER;
        }
    }
}

Status node_create(Node **node, int hasPriority){
    Type type;
    Data value;
    char choice;
    if(typecount > 1){
        printf("\nSelect the type of node =>");
        if(hasint)
            printf("\n(I)nteger");
        if(hasreal)
            printf("\n(R)eal");
        if(haschar)
            printf("\n(C)haracter");
        printf(" : ");
        scanf(" %c", &choice);
        switch(choice){
            case 'I' :
            case 'i' : 
                if(!hasint)
                    return WRONG_OPTION_CHOOSEN;
                type = INTEGER;
                printf("Enter the integer value : ");
                scanf("%d",&value.ival);
                break;

            case 'R' : 
            case 'r' : 
                if(!hasreal)
                    return WRONG_OPTION_CHOOSEN;
                type = REAL;
                printf("Enter the real value : ");
                scanf("%f",&value.fval);
                break;

            case 'C' : 
            case 'c' : 
                if(!hasreal)
                    return WRONG_OPTION_CHOOSEN;
                type = CHARACTER;
                printf("Enter the character value : ");
                scanf(" %c",&value.cval);
                break;

            default : return WRONG_OPTION_CHOOSEN;
                      break;
        }
    }
    else{
        int cont = 1;
        char input[100];
        while(cont){
            if(cont == 2){
                printf("\n[Error] Bad %s value : %s", DEF_NODE_STRING, input);
            }
            char *rem = NULL;
            printf("\nEnter the value of the %s node : ", DEF_NODE_STRING);
            scanf("%s", input);
            switch(DEF_NODE_TYPE){
                case INTEGER:
                    value.ival = strtoll(input, &rem, 10);
                    if(strlen(rem) > 0){
                        cont = 2;
                        continue;
                    }
                    cont = 0;
                    break;
                case REAL:
                    value.fval = strtold(input, &rem);
                    if(strlen(rem) > 0){
                        cont = 2;
                        continue;
                    }
                    cont = 0;
                    break;
                case CHARACTER:
                    value.cval = input[0];
                    cont = 0;
                    break;
            }
        }
        type = DEF_NODE_TYPE;
    }

    if(hasPriority){
        Priority p = node_get_priority();
        return node_init_priority(node, type, value, p);
    }
    else
        return node_init(node, type, value);
}

/*
   Prints the value of a node.

Arguments :	1. aNode : the node to be printed
-----------

Return values : Anyone of the following statuses,
---------------	1. INTERNAL_ERROR : When the node type is undefined,
which it should not be
2. OP_SUCCESS
*/

Status node_print(Node *aNode, int count){
    //Check the type of the node
    Type type = aNode->type;
    if(count>0)
        printf("\n\nNode : %d",count);
    if(aNode->hasPriority && aNode->priority>=0)
        node_print_priority(aNode->priority);

    if(typecount > 1)
        printf("\nNode type : ");
    //Print the value associated with the type
    switch(type){
        case INTEGER:
            if(typecount > 1)
                printf("Integer");
            printf("\nValue : %d",aNode->value.ival);
            break;

        case REAL:
            if(typecount > 1)
                printf("Real");
            printf("\nValue : %g",aNode->value.fval);
            break;

        case CHARACTER: 
            if(typecount > 1)
                printf("Character");
            printf("\nValue : %c",aNode->value.cval);
            break;
            //Type is none of the known!

        default: printf("%d\nFATAL ERROR!\n",type);
                 return INTERNAL_ERROR;
    }
    printf("\n");
    return OP_SUCCESS;
}

int node_isequal(Node *node1, Node *node2){
    if(node1->type==node2->type){
        switch(node1->type){
            case INTEGER: return node1->value.ival==node2->value.ival;
                          break;

            case REAL: return node1->value.fval==node2->value.fval;
                       break;

            case CHARACTER: return node1->value.cval==node2->value.cval;
                            break;
        }
    }
    else
        return 0;
}

int node_isgreater(Node *node1, Node *node2){
    if(node1->type==node2->type){
        switch(node1->type){
            case INTEGER: return node1->value.ival>node2->value.ival;
                          break;

            case REAL: return node1->value.fval>node2->value.fval;
                       break;

            case CHARACTER: return node1->value.cval>node2->value.cval;
                            break;
        }
    }
    else
        return 0;

}

int node_islesser(Node *node1, Node *node2){
    return !node_isgreater(node1, node2);
}

Status node_free(Node *toFree){
    while(toFree != NULL){
        Node *backup = toFree;
        toFree = toFree->nextNode;
        free(backup);
    }
    return OP_SUCCESS;
}

int node_typecount(){
    return typecount;
}
