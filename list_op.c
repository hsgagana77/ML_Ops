#include <stdlib.h>
#include "list.h"
#define IS_NULL(PTR) PTR == NULL

List * initialise_list()
{
    List *my_list;

    my_list = (List *)malloc(sizeof(List));
    if(my_list == NULL) return ALLOC_FAIL;

    my_list->head = my_list->tail = NULL;
    my_list->count = 0;

    return my_list;
}
Node *get_node(int data)
{
    Node *new_node;

    new_node = (Node *)malloc(sizeof(Node));
    if(new_node == NULL) return NODE_ALLOC_FAIL;
    new_node->data = data;
    new_node->ptr = NULL;

    return new_node;
}
int insert_data_beg(List *my_list, int data)
{
    Node *new_node = get_node(data);
    if(new_node == NODE_ALLOC_FAIL) return INSERT_FAIL;

    if(my_list->count == 0) // insert first element
        my_list->head = my_list->tail = new_node;
    else
    {
        new_node->ptr = my_list->head;
        my_list->head = new_node;
    }
    my_list->count++;
    return SUCCESS;
}

int insert_data_end(List *my_list, int data)
{
    Node *new_node = get_node(data);
    if(new_node == NODE_ALLOC_FAIL) return INSERT_FAIL;

    if(my_list->count == 0) // insert first element
        my_list->head = my_list->tail = new_node;
    else
    {
        my_list->tail->ptr = new_node; // insert at end
        my_list->tail = new_node; // update tail address
    }
    my_list->count++;
    return SUCCESS;
}


int search(List *my_list, int element)
{
    Node *temp;

    for(temp = my_list->head; temp != NULL; temp = temp->ptr)
        if(temp->data == element) return FOUND;
    return NOT_FOUND;
}
Node *get_node_address(List *my_list,int element)
{
    Node *temp;

    for(temp = my_list->head; temp != NULL; temp = temp->ptr)
        if(temp->data == element) return temp;
    return NULL;
}


int insert_data_after_element(List *my_list, int data, int element)
{
    Node *temp, *new_node;

    temp = get_node_address(my_list, element);
    if(IS_NULL(temp)) return INSERT_FAIL;

    new_node = get_node(data);
    if(IS_NULL(new_node)) return INSERT_FAIL;

    new_node->ptr = temp->ptr;
    temp->ptr = new_node;
    if(temp == my_list->tail) my_list->tail = new_node;
    my_list->count++;

    return SUCCESS;
}

Node * get_node_last_min_addr(List *my_list,int data)
{
    Node *temp;

    for(temp = my_list->head; temp->ptr!=NULL && temp->ptr->data < data;//
    temp = temp->ptr);

    return temp;
}
int insert_and_sort(List *my_list, int data)
{
    if(my_list->count == 0)
        return insert_data_beg(my_list, data);
    if(my_list->head->data > data)
        return insert_data_beg(my_list, data);
    if(my_list->tail->data < data)
        return insert_data_end(my_list, data);

    Node *temp = get_node_last_min_addr(my_list, data);

    Node *new_node = get_node(data);
    new_node->ptr = temp->ptr;
    temp->ptr = new_node;
    my_list->count++;

    return SUCCESS;
}

int insert_and_sort_with_prev(List *my_list, int data)
{
    Node *temp, *prev, *new_node;

     new_node = get_node(data);
    if(my_list->count == 0)
        my_list->head= my_list->tail = new_node;
    if(my_list->head->data > data)
    {
        new_node->ptr = my_list->head;
        my_list->head = new_node;
    }
    //write code to insert data at tail

    for(temp = my_list->head; temp->ptr != NULL && temp->data < data; prev = temp,temp = temp->ptr)
    {
        prev->ptr = new_node;
        new_node->ptr = temp;
    }
    my_list->count++;
    return SUCCESS;
}

int delete_at_beg(List *my_list)
{
    Node *temp;
    int result;

    if(my_list->count == 0) return LIST_EMPTY;
    result = my_list->head->data;
    if(my_list->count == 1)
    {
        free(my_list->head);
        my_list->head = my_list->tail = NULL;
    }
    else{
        temp = my_list->head;
        my_list->head = my_list->head->ptr;
        free(temp);
    }
    my_list->count--;

    return result;
}
Node * get_n_minus_one_node_addr(List *my_list)
{
    Node *temp;

    for(temp=my_list->head; temp->ptr != my_list->tail; temp= temp->ptr);
    return temp;
}

int delete_at_end(List *my_list)
{
     Node *temp;
    int result;

    if(my_list->count == 0) return LIST_EMPTY;
    result = my_list->tail->data;
    if(my_list->count == 1)
    {
        free(my_list->head);
        my_list->head = my_list->tail = NULL;
    }
    else
    {
        temp = get_n_minus_one_node_addr(my_list);
        free(temp->ptr);
        temp->ptr = NULL;
        my_list->tail = temp;
    }
    my_list->count--;
    return result;
}

int delete_element(List *my_list, int ele)
{
    Node *temp, *prev;
    int result;

    if(my_list->count == 0) return LIST_EMPTY;

    if(my_list->head->data == ele)
        return delete_at_beg(my_list);
    if(my_list->tail->data == ele)
        return delete_at_end(my_list);

    for(temp = my_list->head;//
     temp != NULL && temp->data != ele;//
     prev=temp, temp = temp->ptr);

     if(temp == NULL) return NOT_FOUND;
     result = temp->data;
     prev->ptr = temp->ptr;
     free(temp);
     my_list->count--;

     return result;

}
int delete_occurence_element(List *my_list, int ele)
{

    int count=0, i;
    //Node *temp;
    int total_ele = my_list->count;
    for(i=0; i<total_ele;i++)
    {
        if(delete_element(my_list, ele) == ele){
            count++;
            continue;
    }
    else
        break;
    }
    return count;
}

List *deallocate_list(List *my_list)
{
    Node *temp = my_list->head;

    if(my_list == NULL)  return NULL;
    while(my_list->head != NULL)
    {
        my_list->head = my_list->head->ptr;
        free(temp);
        temp = my_list->head;
    }
    free(my_list);
    return NULL;
}
