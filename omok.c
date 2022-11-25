#include <stdio.h>
#include <stdlib.h>

int check(int *board, int line) ;
void prt_board(int* board, int n, int x, int y) ;

int main()
{
    int n, line, i, j, k, x, y, turn=0 ;
    printf("board size : ") ;  // 판 크기 입력
    scanf("%d", &n) ;
    printf("line size : ") ; // 승리 조건 입력
    scanf("%d", &line) ;

    /* 배열 동적 할당 */
    int* board ;
    board = (int*)malloc(sizeof(int)*(n*n)) ;

    /* 0으로 초기화 */
    for(i=0;i<n*n;i++)
    {
        board[i] = 0 ;
    }

    prt_board(board, n) ;

    /* play game */
    while(1)
    {
        if(turn==0)  // 검은돌 순서면
        {
            reput_b: printf("black >> ") ;
            scanf("%d %d", &x, &y) ;  // 좌표 입력
            if(board[(y-1)*n+x-1]==1 || board[(y-1)*n+x-1]==2)  // 이미 놓은 돌 있는지 확인
            {
                printf("already laid\n") ;
                goto reput_b ;  // 다시 반복
            }
            else
            {
                board[(y-1)*n+x-1] = 1 ;  // 돌 놓기
                prt_board(board, n) ;  // 결과 출력
                turn = 1 ;  // 순서 전환
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

    /* 저장공간 해제 */
    free(board) ;
    return 0 ;
}

int check(int* board, int n, int line, int x, int y)
{
    int blockage = 0 ;  // 0 - 안막힘, 1 - 막힘
    int stack=0, i ;
    line = line%2==0?line/2:(line-1)/2 ;

    for(x=0;x<2;x++)
    {
        for(y=-1;y<2;y=y+2)
        {
            for(i=1;i<line+1;i++)
            {
                if(*(board+n*y+x+i))
            }
        }
    }
    /*for(i=1;i<line+1;i++)
    {
        if(*(board+n*y+x+i)==*(board+n*y+x))
        {
            stack++ ;
        }
        else break ;
    }
    for(i=1;i<line+1;i++)
    {
        if(*(board+n*y+x-i)==*(board+n*y+x))
        {
            stack++ ;
        }
        else break ;
    }*/
}

/* 바둑판 출력 함수 */
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
    for(i=0;i<n;i++)  // y좌표
    {
        if(n>9) printf("    ") ;
        else printf("     ") ;
        for(k=0;k<n*4-1;k++) printf("-") ;
        printf("\n %d |", i+1) ;
        for(j=0;j<n;j++)  // x좌표
        {
            printf(" %d |", *(board+i*n+j)) ;  // 포인터
        }
        printf("\n") ;
    }
    printf("    ") ;
    for(i=0;i<n*4-1;i++) printf("-") ;
    printf("\n\n") ;
}
