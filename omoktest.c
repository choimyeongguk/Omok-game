#include <stdio.h>
#define n 5

int main()
{
    int i, j ;
    //const int n = 5 ;
    int board[n][n] = {0,};

    /*for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            board[i][j] = 0 ;
        }
    }*/

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d", board[j][i]) ;
        }
        printf("\n") ;
    }
}
