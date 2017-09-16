#include<linkedlist.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
    LinkedList *list;
    Status ret;
    Node *aNode;
    int choice = 1;
    ret = list_init(&list);
    if(ret!=OP_SUCCESS)
        status_print(ret, STRUCTURE_CREATION);
    else{
        node_configure();
        while(choice>-1 && choice<14){
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
            printf("\n12. Alt. reverse list");
            printf("\n13. Delete second largest item");
            printf("\nEnter your choice : ");
            scanf("%d", &choice);
            switch(choice){
                case 0: ret = list_print(list);
                        status_print(ret, TRAVERSAL);
                        break;
                case 1:	ret = node_create(&aNode, 0);
                        if(ret==OP_SUCCESS){
                            ret = list_ins_front(list, aNode);
                        }
                        status_print(ret, INSERTION);
                        break;
                case 2: ret = node_create(&aNode, 0);
                        if(ret==OP_SUCCESS){
                            ret = list_ins_end(list, aNode);
                        }
                        status_print(ret, INSERTION);
                        break;
                case 3: ret = node_create(&aNode, 0);
                        if(ret==OP_SUCCESS){
                            printf("\nEnter the position you want to insert : ");
                            scanf("%d", &choice);
                            ret = list_ins_pos(list, aNode, choice);
                            choice = 1;
                        }
                        status_print(ret, INSERTION);
                        break;
                case 4:	printf("\nSelect the node to insert");
                        printf("\n==========================");
                        Node *node;
                        ret = node_create(&node, 0);
                        if(ret==OP_SUCCESS){
                            printf("\nSelect the value to insert after");
                            printf("\n================================");
                            ret = node_create(&aNode, 0);
                            if(ret==OP_SUCCESS)
                                ret = list_ins_after(list, node, aNode);
                            free(aNode);
                        }
                        status_print(ret, INSERTION);
                        break;
                case 5: ret = list_del_front(list);
                        status_print(ret, DELETION);
                        break;
                case 6: ret = list_del_end(list);
                        status_print(ret, DELETION);
                        break;
                case 7: printf("\nSelect the node to delete");
                        printf("\n=========================");
                        ret = node_create(&aNode, 0);
                        if(ret==OP_SUCCESS){
                            ret = list_del_val(list, aNode);
                        }
                        status_print(ret, DELETION);
                        free(aNode);
                        break;
                case 8: printf("Enter the position to delete : ");
                        scanf("%d", &choice);
                        ret = list_del_pos(list, choice);
                        choice = 1;
                        status_print(ret, DELETION);
                        break;
                case 9: printf("\nSelect the node to delete before");
                        printf("\n================================");
                        ret = node_create(&aNode, 0);
                        if(ret==OP_SUCCESS)
                            ret = list_del_before(list, aNode);
                        status_print(ret, DELETION);
                        free(aNode);
                        break;
                case 10: ret = list_reverse(&list);
                         status_print(ret, REVERSAL);
                         break;
                case 11 : ret = list_sort(list);
                          status_print(ret, SORTING);
                          break;
                case 12: ret = list_reverse_alt(list);
                         status_print(ret, REVERSAL);
                         break;
                case 13: ret = list_del_second_largest(list);
                         status_print(ret, DELETION);
                         break;
            }
        }
        list_free(list);
    }
    return 0;
}
