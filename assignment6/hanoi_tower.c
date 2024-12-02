#include <stdio.h>

void showMoves(int n,char start, char dest, char temp){
    if(n==1)
        printf("Move dist 1 from peg %c to peg %c\n",start,dest);
    else
    {
        showMoves(n-1,start,temp,dest);
        printf("Move disk %d from peg %c to peg %c\n",n,start,dest);
        showMoves(n-1,temp,dest,start);
    }
}

int main(){
    showMoves(3,'L','M','N');
}