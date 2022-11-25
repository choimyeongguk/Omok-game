#include <stdio.h>
#include <stdlib.h>

void prt_board(int* board, int n) ;

int main()
{
    int n, line, i, j, k, x, y, turn=0 ;
    printf("board size : ") ;  // �� ũ�� �Է�
    scanf("%d", &n) ;
    printf("line size : ") ; // �¸� ���� �Է�
    scanf("%d", &line) ;

    /* 2���� �迭 ���� �Ҵ� */
    int* board ;
    board = (int*)malloc(sizeof(int)*(n*n)) ;

    /* 0���� �ʱ�ȭ */
    for(i=0;i<n*n;i++)
    {
        board[i] = 0 ;
    }

    prt_board(board, n) ;

    /* play game */
    while(1)
    {
        if(turn==0)  // ������ ������
        {
            reput_b: printf("black >> ") ;
            scanf("%d %d", &x, &y) ;  // ��ǥ �Է�
            if(board[(y-1)*n+x-1]==1 || board[(y-1)*n+x-1]==2)  // �̹� ���� �� �ִ��� Ȯ��
            {
                printf("already laid\n") ;
                goto reput_b ;  // �ٽ� �ݺ�
            }
            else
            {
                board[(y-1)*n+x-1] = 1 ;  // �� ����
                prt_board(board, n) ;  // ��� ���
                turn = 1 ;  // ���� ��ȯ
            }
        }
        else
        {
            reput_w: printf("white >> ") ;
            scanf("%d %d", &x, &y) ;
            if(board[(y-1)*n+x-1]==1 || board[(y-1)*n+x-1]==2)
            {
                printf("already laid\n") ;
                goto reput_w ;
            }
            else
            {
                board[(y-1)*n+x-1] = 2 ;
                prt_board(board, n) ;
                turn = 0 ;
            }
        }

    }

    /* ������� ���� */
    free(board) ;
    return 0 ;
}

/* �ٵ��� ��� �Լ� */
void prt_board(int* board, int n)
{
    int i, j, k ;
    printf("\n     ") ;
    if(n>9) printf(" ") ;
    for(i=0;i<n;i++)
    {
        if(n>9) printf("%d   ", i+1) ;
        else printf("%d    ", i+1) ;
    }
    printf("\n") ;
    for(i=0;i<n;i++)  // y��ǥ
    {
        if(n>9) printf("    ") ;
        else printf("     ") ;
        for(k=0;k<n*4-1;k++) printf("-") ;
        printf("\n %d |", i+1) ;
        for(j=0;j<n;j++)  // x��ǥ
        {
            printf(" %d |", *(board+i*n+j)) ;  // ������
        }
        printf("\n") ;
    }
    printf("    ") ;
    for(i=0;i<n*4-1;i++) printf("-") ;
    printf("\n\n") ;
}
