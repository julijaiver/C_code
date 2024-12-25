#include <stdio.h>

int main(void) {
    int matrix[5][3];
    int i,j, count=1;

    for(j=0;j<3;j++) {
        for(i=0;i<5;i++) {
            matrix[i][j]=count;
            ++count;
            printf("%d ",matrix[i][j]);
        }
    }
    return 0;
}