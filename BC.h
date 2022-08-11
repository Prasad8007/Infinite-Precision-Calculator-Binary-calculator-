typedef struct node{
    struct node *prev;
    int data;
    struct node *next;
}node;

typedef node * List;

typedef struct snode{
    char op;
    struct node*next;
}snode;

typedef snode* stack;

typedef struct Lnode{
    List L;
    struct Lnode *next;
}Lnode;

typedef Lnode* Lstack;

void init_list(List *L);
void traverse(List L);
void destroy_list(List *L);
void insert_at_first(List *L,int d);
int size(List L);
void rmv_int_zero(List *L);
int compare(List *L1,List *L2);
void append(List *L,int d);
void Reverse(List *L);
List copy_list(List L);

void init_stack(stack *s);
void push(stack *s,char c);
char pop(stack *s);
void Display(stack s);
int isEmpty_stack(stack s);
int priority(char x);

void init_liststack(Lstack *Ls);
void list_push(Lstack *Ls,List l);
int isEmpty_Lstack(Lstack Ls);
List Lpop(Lstack *Ls);
void LDisplay(Lstack Ls);

List add(List*L1,List*L2);
List sub(List*L1,List*L2);
List multi(List*L1,List*L2);
List division(List*L1,List*L2);
List modulo(List*L1,List*L2);

List Simplify(List *Lc);
List Answer();


