#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(){
    char c1 = getchar();
    char c2 = getchar();
    if(c1 > c2){
        char t = c1;
        c1 = c2;
        c2 = t;
    }
    int d = c2 - c1;
    printf("The distance between %c and %c is %d\n", c1, c2, d);
    int i;
    for ( i = c1; i <= c2; i++)
    {
        printf("%c: %d, %o, %X\n",i,i,i, i);
    }
    return 0;
}
