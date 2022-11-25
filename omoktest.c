#include <stdio.h>
#include <stdlib.h>

int print(int* list)
{
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<2;j++)
        {
            printf("%d ", *(list+i*2+j)) ;
        }
        printf("\n") ;
    }
}

int main()
{
    int n ;
    scanf("%d", &n) ;

    int **arr ;
    arr = (int) malloc (sizeof(int)*n) ;
    for(int i=0;i<n;i++)
    {
        arr[i] = (int) malloc (sizeof(int)*n) ;
    }

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            arr[i][j] = i*n+j ;
        }
    }

    print(*arr) ;
}
