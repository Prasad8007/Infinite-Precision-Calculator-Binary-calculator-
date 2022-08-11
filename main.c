#include <stdio.h>
#include <stdlib.h>
#include "BC.h"


int main()
{   printf("Operations which can be performed - [ +  -  *  / %].\n");
    printf("Enter expression as 0 to exit \n");

    while(1){
        printf("\nEnter the expression - ");
        List ANS=Answer();
        if(ANS!=NULL){
            printf("ANSWER - ");
            traverse(ANS);
        }
    }
    return 0;
}
