#ifndef LIST_HEADER
#define LIST_HEADER
#define ALLOC_FAIL NULL
#define NODE_ALLOC_FAIL NULL
#define SUCCESS 1
#define INSERT_FAIL 0
#define NOT_FOUND 0
#define FOUND 1
#define LIST_EMPTY -1
struct _node_
{
    int data;
    struct _node_ *ptr;
};
typedef struct _node_ Node;

struct _linked_list_
{
    Node *head, *tail;
    int count;
};
typedef struct _linked_list_ List;

List * initialise_list();
int insert_data_beg(List *, int);
int insert_data_end(List *, int);
int insert_data_after_element(List *, int data, int element);
int insert_and_sort(List *, int);
int search(List *, int);

int delete_at_beg(List *);
int delete_at_end(List *);
int delete_element(List *, int element);


int merge_list(List *, List *); // practice lab
List * intersection(List *, List *); // practice lab
List * split_at_index(List *, int index); // practice lab
List *sort(List *);
List *deallocate_list(List *);
List * delete_duplicate_element(List *); // practice lab
int delete_occurence_element(List *, int);

#endif // LIST_HEADER
