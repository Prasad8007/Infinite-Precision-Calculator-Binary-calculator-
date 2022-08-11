#include <stdio.h>
#include <stdlib.h>
#include "BC.h"

void init_list(List *L){
    *L=NULL;
    return;
}

void traverse(List L){
    node *p;
    p=L;
    if(!p) printf(" \n");
    while(p!=NULL){
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
    return;
}

void destroy_list(List *L){
    node *p = *L;
    node *q=NULL;
    while(p){
        q = p;
        p = p->next;
        free(q);
    }
    *L=NULL;
    return ;
}

void insert_at_first(List *L,int d){
    node *p = *L;
    node *nn= (node*)malloc(sizeof(node));
    if(!nn) return;
    nn->data=d;
    nn->prev=NULL;
    nn->next=NULL;

    p->prev=nn;
    nn->next=p;
    *L=nn;

    return ;
}

int size(List L){
    node *p=L;
    int count=0;
    while(p!=NULL){
        count++;
        p=p->next;
    }
    return count;
}

void rmv_int_zero(List *L){
    node*p=*L;
    node*q=NULL;

    while(p->next && p->data==0){
        q=p;
        p=p->next;
        *L=p;
        p->prev=NULL;
        free(q);
    }
    return;
}

int compare(List *L1,List *L2){
    rmv_int_zero(L1);
    rmv_int_zero(L2);

    if(size(*L1)>size(*L2)) return 1;
    else if(size(*L1)<size(*L2)) return 2;
    else {
        node *p=*L1;
        node *q=*L2;
        while(p){
            if(p->data > q->data) return 1;
            else if(p->data < q->data) return 2;
            else {
                p=p->next;
                q=q->next;
            }
        }
        return 0;
    }
}

void append(List *L,int d){
    node *nn = (node *)malloc(sizeof(node));
    if(!nn) return;
    node *p;
    p=*L;
    nn->data=d;
    nn->prev=NULL;
    nn->next=NULL;

    if(*L==NULL){
        *L=nn;
        return;
    }
    else{
        while(p->next!=NULL){
            p=p->next;
        }
        p->next=nn;
        nn->prev=p;
    }
}

List copy_list(List L){
    List Lcopy;
    init_list(&Lcopy);

    node*p=L;
    while(p){
        int x=p->data;
        append(&Lcopy,x);
        p=p->next;
    }
    return Lcopy;
}

void Reverse(List *L){
    node *p,*q;
    p=*L;
    if(!p) return;

    q=p->next;

    p->next=NULL;
    p->prev=q;

    while(q){
        q->prev=q->next;
        q->next=p;
        p=q;
        q=q->prev;
    }
    *L=p;
    return;
}
void Remove(List *L,char d){

    if(!*L) return;
    node *p=*L;
    node *q=NULL;
    while(p && p->data!=d){
        q=p;
        p=p->next;
    }

    if(!p) return;
    else if(!q){
        q=p;
        p=p->next;
        *L=p;
        p->prev=NULL;
        free(q);
        return;
    }

    else{
        q->next=p->next;
        free(p);
        p=p->next;
        if(!p) return;
        p->prev=q;
        return;
        }

}

int isOperator(char c) {
        switch(c) {
            case '+':
                return 1;
            case '-':
                return 1;
            case '*':
                return 1;
            case '/':
                return 1;
            case '%':
                return 1;
            case '^':
                return 1;
            default:
                return 0;
        }
}


List add(List*L1,List*L2){

    if(!*L1) return *L2;
    if(!*L2) return *L1;

    List L3;
    init_list(&L3);

    rmv_int_zero(L1);
    rmv_int_zero(L2);

    Reverse(L1);
    Reverse(L2);

    int sum,s,c=0;

    node*p=*L1;
    node*q=*L2;



    while(p || q){

        if(!p){
            sum=q->data+c;
            q=q->next;
        }

        else if(!q){
            sum=p->data+c;
            p=p->next;
        }

        else{
            sum=p->data+q->data+c;
            p=p->next;
            q=q->next;
        }

        s=sum%10;
        c=sum/10;
        //printf("%d %d\n",s,c);
        append(&L3,s);

    }

    if(c) append(&L3,c);
    Reverse(L1);
    Reverse(L2);
    Reverse(&L3);
    return L3;
}

List sub(List*L1,List*L2){

    List L3;
    init_list(&L3);
    rmv_int_zero(L1);
    rmv_int_zero(L2);

    if(!*L1) return *L2;
    if(!*L2) return *L1;

    if(compare(L1,L2)==0){
        append(&L3,0);
        return L3;
    }
    Reverse(L1);
    Reverse(L2);

    node*p=*L1;
    node*q=*L2;

    int d,b;

    while(p || q){

        if(!p){
            d=q->data;
            q=q->next;
        }

        else if(!q){
            if(p->data<0){
                p->data=9;
                p->next->data--;
            }
            d=p->data;
            p=p->next;
        }

        else{
            if(p->data < q->data){
                p->next->data --;
                b = 10+ p->data;
                d= b - q->data;
            }
            else{
                d=p->data - q->data ;
            }
            p=p->next;
            q=q->next;
        }
        //printf("%d %d\n",d,b);
        append(&L3,d);
    }
    Reverse(L1);
    Reverse(L2);
    Reverse(&L3);
    return L3;
}

List multi(List*L1,List*L2){
    List L3;
    init_list(&L3);
    List tmp;
    init_list(&tmp);
    rmv_int_zero(L1);
    rmv_int_zero(L2);
    Reverse(L1);
    Reverse(L2);

    node*p=*L1;
    node*q=*L2;

    if(size(p)==1 && p->data==0) {
        append(&L3,0);
        Reverse(L1);
        Reverse(L2);
        return L3;
    }
    if(size(q)==1 && q->data==0){
        append(&L3,0);
        Reverse(L1);
        Reverse(L2);
        return L3;
    }

    int m,s=0,c=0,k=0;

    while(q){
        while(p){
            m=p->data * q->data +c;
            s=m%10;
            c=m/10;
            append(&tmp,s);
            p=p->next;
        }
        if(c) append(&tmp,c);

        for(int i=0;i<k;i++){
            insert_at_first(&tmp,0);
        }

        Reverse(&tmp);
        L3=add(&L3,&tmp);
        q=q->next;
        p=*L1;
        k++;
        s=0;
        c=0;
        tmp=NULL;
    }
    Reverse(L1);
    Reverse(L2);
    return L3;
}

List division(List*L1,List*L2){

    List L3,d1,d2,mp,pr,tmpfree;
    init_list(&L3);
    init_list(&d1);
    init_list(&d2);
    init_list(&mp);
    init_list(&pr);
    init_list(&tmpfree);

    rmv_int_zero(L1);
    rmv_int_zero(L2);
    node *p=*L1;
    node *q=*L2;
    d1=*L2;

    if(q->data==0){
        printf("Error - Not Defined .\n");
        return L3;
    }

    else if(size(q)==1 && q->data==1) return *L1;

    if(compare(L1,L2)==0){
        append(&L3,1);
        return L3;
    }

    else if(compare(L1,L2)==2){
        append(&L3,0);
        return L3;
    }

    int i;
    for(i=0;i<size(*L2);i++){
        append(&d2,p->data);
        p=p->next;
    }

    for(i=1;i<10;i++){
        append(&mp,i);
        pr=multi(&mp,&d1);
        if (compare(&d2, &pr) == 2)
            break;
        destroy_list(&mp);
        destroy_list(&pr);
    }
    int multiplier = i-1;
    destroy_list(&mp);
    destroy_list(&pr);

    append(&mp, multiplier);
    pr = multi(&mp, &d1);
    tmpfree = d2;
    d2 = sub(&d2, &pr);
    destroy_list(&tmpfree);

    append(&L3, multiplier);
    destroy_list(&mp);
    destroy_list(&pr);

    while(p){
        append(&d2,p->data);

        for(i=1;i<10;i++){
            append(&mp,i);
            pr=multi(&mp,&d1);
            if (compare(&d2, &pr) == 2)
                break;
            destroy_list(&mp);
            destroy_list(&pr);
        }

        int multiplier = i-1;
        destroy_list(&mp);
        destroy_list(&pr);

        append(&mp, multiplier);
        pr = multi(&d1, &mp);

        tmpfree = d2;
        d2 = sub(&d2, &pr);
        destroy_list(&tmpfree);

        append(&L3, multiplier);
        destroy_list(&mp);
        destroy_list(&pr);
        p=p->next;
    }
    rmv_int_zero(&L3);
    return L3;
}

List modulo(List *L1,List *L2){
    List D,M,L3;
    D=division(L1,L2);
    M=multi(L2,&D);
    L3= sub(L1,&M);
    rmv_int_zero(&L3);
    return L3;
}

List fact(List *L){
    List L1,L2;
    rmv_int_zero(&L);
    node *p=L1;

    if(p->data==0){
        append(&L1,1);
        return L1;
    }

    return L2;
}

void init_stack(stack *s){
    *s=NULL;
    return;
}

void push(stack *s,char c){
    snode *nn=(snode*)malloc(sizeof(snode));
    if(!nn) return;
    nn->op=c;
    nn->next=NULL;

    if(*s==NULL){
        *s=nn;
        return;
    }

    nn->next= *s;
    *s=nn;
    return;
}

int isEmpty_stack(stack s){
    if(!s) return 1;
    return 0;
}


char pop(stack *s){
    if(isEmpty_stack(*s)) return 0;
    snode*p=*s;
    *s=p->next;
    char x=p->op;
    free(p);
    return x;
}

void Display(stack s){
    snode*p =s;
    if(!p) {
        printf("The stack Empty.\n");
        return;
    }
    printf("The stack is -\n");
    while(p){
        printf("%c\n",p->op);
        p=p->next;
    }
}

int priority(char x)
{
    if(x == '(')
        return 1;
    else if(x == '+' || x == '-')
        return 10;
    else if(x == '*' || x == '/' || x == '%' )
        return 20;
    else if(x == '^')
        return 30;
    return 0;
}

void init_liststack(Lstack *Ls){
    *Ls=NULL;
    return;
}

void list_push(Lstack *Ls,List l){
    Lnode* nn=(Lnode*)malloc(sizeof(Lnode));
    nn->L=l;
    nn->next=NULL;

    if(*Ls==NULL){
        *Ls=nn;
        return;
    }

    nn->next=*Ls;
    *Ls=nn;
    return;
}

int isEmpty_Lstack(Lstack Ls){
    if(!Ls) return 1;
    return 0;
}


List Lpop(Lstack *Ls){
    if(isEmpty_Lstack(*Ls)) return 0;
    Lnode*p=*Ls;
    *Ls=p->next;
    List x=p->L;
    free(p);
    return x;
}

void LDisplay(Lstack Ls){
    Lnode*p =Ls;
    if(!p) {
        printf("The stack Empty.\n");
        return;
    }
    printf("The stack is -\n");
    int i=1;
    while(p){
        printf("%d - ",i);
        traverse(p->L);
        p=p->next;
        i++;
    }
}

List perform(List *L1,List *L2,int op){
    List Lresult;
    init_list(&Lresult);
    if(op=='+') Lresult = add(L1,L2);
    else if(op=='-'){
            if(compare(L1,L2)==1) Lresult = sub(L1,L2);
            else Lresult = sub(L2,L1);
        }
    else if(op=='*') Lresult = multi(L1,L2);
    else if(op=='/') Lresult = division(L1,L2);
    else if(op=='%') Lresult = modulo(L1,L2);
    return Lresult;
}

List Simplify(List *L){
    //Converting Infix to Postfix

    stack s1;
    init_stack(&s1);
    List Lc;
    init_list(&Lc);
    node*p=*L;
    List L1,L2,L3;
    Lstack Lresult;
    init_list(&L1);
    init_list(&L2);
    init_list(&L3);
    init_liststack(&Lresult);
    int c=0;
    while(p){

        if(isdigit(p->data)) {
                append(&Lc,p->data);
        }

        else if(p->data=='('){
                c++;
                push(&s1,p->data);
            }

        else if(p->data==')'){
                c--;
                if(isEmpty_stack(s1)){
                    printf("Unbalanced Brackets.\n");
                    return L1;
                }
                while(s1->op!='('){
                    int x=pop(&s1);
                    append(&Lc,x);
                }
                pop(&s1);
            }

        else if(isOperator(p->data)) {
            if(isOperator(p->next->data)){
                printf("Consecutive operators.\n");
                return L1;
            }
            if(!s1) goto l1;
            else if(priority(p->data) <= priority(s1->op)) {
                append(&Lc,pop(&s1));
            }
            l1:
            append(&Lc,' ');
            push(&s1,p->data);
        }
        else{
            printf("Invalid Input . \n");
            return L1;
        }
        p=p->next;
    }

    if(c){
        printf("Unbalanced Brackets .\n");
        return L1;
    }
    while(s1){
        int x=pop(&s1);
        append(&Lc,x);
    }

    //Simply Postfix

    node *y=Lc;
    int op;

        while(y){
            if(isdigit(y->data)){
                int tmp=(y->data)-'0';
                append(&L1,tmp);
                y=y->next;
            }
            else if(y->data==' '){
                    if(L1){
                        list_push(&Lresult,L1);
                    }
                    L1=NULL;
                    y=y->next;
            }
            else if(isOperator(y->data)){
                    op=y->data;
                    if(L1){
                        list_push(&Lresult,L1);
                    }
                    L1=NULL;
                    L2=Lpop(&Lresult);
                    L3=Lpop(&Lresult);
                    list_push(&Lresult,perform(&L3,&L2,op));
                    y=y->next;
            }
        }
        L1=Lpop(&Lresult);
        return L1;
}

List Answer(){
    List L1,L2,Lc;
    init_list(&L1);
    init_list(&L2);

    int ch;
    while ((ch = getchar()) != '\n') {
        append(&L1, ch);
    }
    if(L1->data=='0') exit(1);

    node*p=L1;
    while(p){
        Remove(&L1,' ');
        p=p->next;
    }

    L2=Simplify(&L1);
    if(!L2) return L2;

    rmv_int_zero(&L2);
    return L2;
}
