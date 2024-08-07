#include <stdio.h>

int main(void){
//int i = 10;
//int *j = &i;
//int **k = &j;
//printf("%x\t%d\n", &i, i);
//printf("%x\t%x\t%d\n", &j, j, *j);
//printf("%x\t%x\t%x\t%d\n",
//&k, k, *k, **k);
    int moves[3] = {0, 3, 4};
    int *first = &moves[2];
    int board[9] = {0,1,2,3,4,5,6,7,8};
    printf("%d\n", board[*first]);
    return 0;
}